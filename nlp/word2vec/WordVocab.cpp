#include <math.h>
#include "WordVocab.h"
#include "params.h"
#include "TrainFileReader.h"

/**
 * ======== AddWord ========
 * Adds a new word to the vocabulary (one that hasn't been seen yet).
 */
int VocabWords::AddWord(char *word) {
// Measure word length.
    unsigned int length = strlen(word) + 1;

    // Limit string length (default limit is 100 characters).
    if (length > Params::MAX_WORD_LENGTH) {
        length = Params::MAX_WORD_LENGTH;
    }
    // Allocate and store the word string.
    mVocabs[vocab_size].word = (char *) calloc(length, sizeof(char));
    //TODO: should be strncpy.
    strcpy(mVocabs[vocab_size].word, word);

    // Initialize the word frequency to 0.
    mVocabs[vocab_size].cn = 1;

    // Increment the vocabulary size.
    vocab_size++;

    // Reallocate memory if needed
    if (vocab_size + 2 >= vocab_chunk_size) {
        mAllocSize += vocab_chunk_size;
        mVocabs = (struct vocab_word *) realloc(mVocabs, mAllocSize * sizeof(struct vocab_word));
    }

    // Add the word to the 'vocab_hash' table so that we can map quickly from the
    // string to its vocab_word structure.

    // Hash the word to an integer between 0 and 30E6.
    int hash = GetWordHash(word);

    // If the spot is already taken in the hash table, find the next empty spot.
    while (vocab_hash[hash] != -1)
        hash = (hash + 1) % vocab_hash_size;

    // Map the hash code to the index of the word in the 'vocab' array.
    vocab_hash[hash] = vocab_size - 1;

    // Return the index of the word in the 'vocab' array.
    return vocab_size - 1;
}


/**
* ======== GetWordHash ========
* Returns hash value of a word. The hash is an integer between 0 and
* vocab_hash_size (default is 30E6).
*
* For example, the word 'hat':
* hash = ((((h * 257) + a) * 257) + t) % 30E6
*/
int VocabWords::GetWordHash(char *word) {
    unsigned long long a, hash = 0;
    for (a = 0; a < strlen(word); a++) {
        hash = hash * 257 + word[a];
    }
    hash = hash % vocab_hash_size;
    return hash;
}

void VocabWords::BuildFromTrainFile(char *fileName, int minReduce) {
    char wordBuffer[Params::MAX_WORD_LENGTH];
    // The special token </s> is used to mark the end of a sentence. In training,
    // the context window does not go beyond the ends of a sentence.
    // 
    // Add </s> explicitly here so that it occurs at position 0 in the vocab. 
    AddWord((char *) "</s>");
    TrainFileReader *fileReader = new TrainFileReader(fileName);
    while (fileReader->ReadWord(wordBuffer)) {
        train_words++;
        if (train_words % 100000 == 0) {
            printf("%s,%lldK%c", wordBuffer, train_words / 1000, 13);
            fflush(stdout);
        }
        int hashCode = SearchVocab(wordBuffer);
        if (hashCode == -1) {
            //printf("%s\n",wordBuffer);
            AddWord(wordBuffer);
        } else {
            mVocabs[hashCode].cn++;
        }
        if (vocab_size > vocab_hash_size * 0.7) {
            ReduceVocab(minReduce);
        }


    }
    // Sort the vocabulary in descending order by number of word occurrences.
    // Remove (and free the associated memory) for all the words that occur
    // fewer than 'min_count' times.
    SortVocab(minReduce);

    // Report the final vocabulary size, and the total number of words
    // (excluding those filtered from the vocabulary) in the training set.
    if (mDebugMode > 0) {
        printf("Vocab size: %lld\n", vocab_size);
        printf("Words in train file: %lld\n", train_words);
    }
    delete fileReader;
}

/**
 * ======== SearchVocab ========
 * Lookup the index in the 'vocab' table of the given 'word'.
 * Returns -1 if the word is not found.
 * This function uses a hash table for fast lookup.
 */
int VocabWords::SearchVocab(char *word) {
    // Compute the hash value for 'word'.
    unsigned int hash = GetWordHash(word);

    // Lookup the index in the hash table, handling collisions as needed.
    // See 'AddWordToVocab' to see how collisions are handled.
    while (1) {
        // If the word isn't in the hash table, it's not in the vocab.
        if (vocab_hash[hash] == -1) return -1;

        // If the input word matches the word stored at the index, we're good,
        // return the index.
        if (!strcmp(word, mVocabs[vocab_hash[hash]].word)) return vocab_hash[hash];

        // Otherwise, we need to scan through the hash table until we find it.
        hash = (hash + 1) % vocab_hash_size;
    }

    // This will never be reached.
    return -1;
}

void VocabWords::ReduceVocab(int minReduce) {
    //minReduce is 0, do nothing.
    if (minReduce == 0) return;
    int b = 0;
    unsigned int hash;
    for (int a = 0; a < vocab_size; a++) {
        if (mVocabs[a].cn > minReduce) {
            mVocabs[b].cn = mVocabs[a].cn;
            mVocabs[b].word = mVocabs[a].word;
            b++;
        } else {
            free(mVocabs[a].word);
            mVocabs[a].word = 0;
        }
    }
    for (int a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;
    vocab_size = b;

    for (int a = 0; a < vocab_size; a++) {
        // Hash will be re-computed, as it is not actual
        hash = GetWordHash(mVocabs[a].word);
        while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
        vocab_hash[hash] = a;
    }
    fflush(stdout);
}


/**
 * ======== SortVocab ========
 * Sorts the vocabulary by frequency using word counts, and removes words that
 * occur fewer than 'min_count' times in the training text.
 *
 * Removing words from the vocabulary requires recomputing the hash table.
 */
void VocabWords::SortVocab(int minReduced) {
    int a, size;
    unsigned int hash;

    /*
     * Sort the vocabulary by number of occurrences, in descending order.
     *
     * Keep </s> at the first position by sorting starting from index 1.
     *
     * Sorting the vocabulary this way causes the words with the fewest
     * occurrences to be at the end of the vocabulary table. This will allow us
     * to free the memory associated with the words that get filtered out.
     */
    qsort(&mVocabs[1], vocab_size - 1, sizeof(struct vocab_word), VocabWords::VocabCompare);

    // Clear the vocabulary hash table.
    for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;

    // Store the initial vocab size to use in the for loop condition.
    size = vocab_size;

    // Recompute the number of training words.
    train_words = 0;

    // For every word currently in the vocab...
    for (a = 0; a < size; a++) {
        // If it occurs fewer than 'min_count' times, remove it from the vocabulary.
        if ((mVocabs[a].cn < minReduced) && (a != 0)) {
            // Decrease the size of the new vocabulary.
            vocab_size--;

            // Free the memory associated with the word string.
            free(mVocabs[a].word);
        } else {
            // Hash will be re-computed, as after the sorting it is not actual
            hash = GetWordHash(mVocabs[a].word);
            while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
            vocab_hash[hash] = a;
            train_words += mVocabs[a].cn;
        }
    }

    // Reallocate the vocab array, chopping off all of the low-frequency words at
    // the end of the table.
    mVocabs = (struct vocab_word *) realloc(mVocabs, (vocab_size + 1) * sizeof(struct vocab_word));

    // Allocate memory for the binary tree construction
    /*
    for (a = 0; a < vocab_size; a++) {
        vocab[a].code = (char *)calloc(MAX_CODE_LENGTH, sizeof(char));
        vocab[a].point = (int *)calloc(MAX_CODE_LENGTH, sizeof(int));
    }
     */
}

// Used later for sorting by word counts
int VocabWords::VocabCompare(const void *a, const void *b) {
    return ((struct vocab_word *) b)->cn - ((struct vocab_word *) a)->cn;
}

/**
 * ======== InitUnigramTable ========
 * This table is used to implement negative sampling.
 * Each word is given a weight equal to it's frequency (word count) raised to
 * the 3/4 power. The probability for a selecting a word is just its weight
 * divided by the sum of weights for all words.
 *
 * Note that the vocabulary has been sorted by word count, descending, such
 * that we will go through the vocabulary from most frequent to least.
 * Please Refer to http://mccormickml.com/2017/01/11/word2vec-tutorial-part-2-negative-sampling/ Chapter:"Selecting
 * Negative Samples"
 */
void VocabWords::InitUnigramTable() {
    double train_words_pow = 0;

    double d1, power = 0.75;

    // Allocate the table. It's bigger than the vocabulary, because words will
    // appear in it multiple times based on their frequency.
    // Every vocab word appears at least once in the table.
    // The size of the table relative to the size of the vocab dictates the
    // resolution of the sampling. A larger unigram table means the negative
    // samples will be selected with a probability that more closely matches the
    // probability calculated by the equation.
    mUnigramTable = (int *)malloc(mUnigramSize * sizeof(int));

    // Calculate the denominator, which is the sum of weights for all words.
    for (int i = 0; i < vocab_size; i++) {
        train_words_pow += pow(mVocabs[i].cn, power);
    }

    // 'i' is the vocabulary index of the current word, whereas 'a' will be
    // the index into the unigram table.
    int i = 0;

    // Calculate the probability that we choose word 'i'. This is a fraction
    // betwee 0 and 1.
    d1 = pow(mVocabs[i].cn, power) / train_words_pow;

    // Loop over all positions in the table.
    for (int a = 0; a < mUnigramSize; a++) {

        // Store word 'i' in this position. Word 'i' will appear multiple times
        // in the table, based on its frequency in the training data.
        mUnigramTable[a] = i;

        // If the fraction of the table we have filled is greater than the
        // probability of choosing this word, then move to the next word.
        if (a / (double) mUnigramSize > d1) {
            // Move to the next word.
            i++;

            // Calculate the probability for the new word, and accumulate it with
            // the probabilities of all previous words, so that we can compare d1 to
            // the percentage of the table that we have filled.
            d1 += pow(mVocabs[i].cn, power) / train_words_pow;
        }
        // Don't go past the end of the vocab.
        // The total weights for all words should sum up to 1, so there shouldn't
        // be any extra space at the end of the table. Maybe it's possible to be
        // off by 1, though? Or maybe this is just precautionary.
        if (i >= vocab_size) i = vocab_size - 1;
    }
}