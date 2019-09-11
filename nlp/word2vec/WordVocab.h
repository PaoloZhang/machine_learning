#if !defined(__WORDVOCAB_H__)
#define __WORDVOCAB_H__

#include <stdlib.h>
#include "TrainFileReader.h"
#include "params.h"
/*
 a chunk size for allocating the vocabulary table. The vocabulary table will
 be expanded as necessary, and is allocated, e.g., 1,000 words at a time.
*/
#define vocab_chunk_size 1000

struct vocab_word {
    long long cn;
    int *point;
    char *word, *code, codelen;
};

class VocabWords {
private:
    vocab_word *mVocabs;
    //vocab size: The unique vocab, don't count the same one.
    long long vocab_size;
    //The original train file size by bytes.
    long mTrainFileSize;

    /*
    * The size of the hash table for the vocabulary.
    * The vocabulary won't be allowed to grow beyond 70% of this number.
    * For instance, if the hash table has 30M entries, then the maximum
    * vocab size is 21M. This is to minimize the occurrence (and performance
    * impact) of hash collisions.
    */
    const int vocab_hash_size = 30000000;  // Maximum 30 * 0.7 = 21M words in the vocabulary

    int *vocab_hash;

    // allocated the zie.
    int mAllocSize;
    //train word size.
    long long train_words;

    int mUnigramSize = 1e8;

    int *mUnigramTable;

    VocabParams *mParams;

    int GetWordHash(char *word);

    void ClearHashTable() {
      for (int a = 0; a < vocab_hash_size; a++) {
        vocab_hash[a] = -1;
      }
    }

    int SearchVocab(char *word);

    void ReduceVocab(int minReduce);

    void SortVocab(int minReduce);

    static int VocabCompare(const void *a, const void *b);

    static void SaveVocab(const char* vocabFile,const vocab_word *vocabs, long long vocabSize,const char* trainFile, long fileSize);

    bool ReadVocab(const char* fileName);
public:
    VocabWords(VocabParams *params):mTrainFileSize(0) {
      // Init allocate the vocabulary table.
      mParams = params;
      mAllocSize = vocab_chunk_size;
      mVocabs = (struct vocab_word *) calloc(mAllocSize, sizeof(struct vocab_word));
      vocab_hash = (int *) calloc(vocab_hash_size, sizeof(int));
      ClearHashTable();
      vocab_size = 0;
      train_words = 0;
      mUnigramTable = 0;

    }

    virtual ~VocabWords() {
      if (mUnigramTable != 0) {
        free(mUnigramTable);
        mUnigramTable = 0;
      }

    }

    int AddWord(char *word);

    /*
    Build the vocabs from the train file.
    */
    void Build();

    void InitUnigramTable();

   // bool ReadWordIndex(TrainFileReader* fileReader, int& index);

    void* trainModel(void *d);

};


#endif