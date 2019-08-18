#if !defined(__WORDVOCAB_h__)
#define __WORDVOCAB_h__
#include <stdlib.h>
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
        vocab_word * mVocabs;
        //if the token frequency < mMinReduced, remove the token.
        int mDebugMode;
        /*
        * The size of the hash table for the vocabulary.
        * The vocabulary won't be allowed to grow beyond 70% of this number.
        * For instance, if the hash table has 30M entries, then the maximum
        * vocab size is 21M. This is to minimize the occurrence (and performance
        * impact) of hash collisions.
        */
        const int vocab_hash_size = 30000000;  // Maximum 30 * 0.7 = 21M words in the vocabulary

        int *vocab_hash; 
        //vocab size: The unique vocab, don't count the same one.
        int vocab_size;
        // allocated the zie.
        int mAllocSize;
        //train word size.
        int train_words;

        int GetWordHash(char *word);

        void ClearHashTable()
        {
            for (int a = 0; a < vocab_hash_size; a++) 
            {
                vocab_hash[a] = -1;
            } 
        }

        int SearchVocab(char *word);

        void ReduceVocab(int minReduce);
        void SortVocab(int minReduce);
        static int VocabCompare(const void *a, const void *b);

    public:
        VocabWords(int debugMode)
        {   
            // Init allocate the vocabulary table.
            mAllocSize = vocab_chunk_size;
            mVocabs = (struct vocab_word *)calloc(mAllocSize, sizeof(struct vocab_word));
            vocab_hash = (int *)calloc(vocab_hash_size, sizeof(int));
            ClearHashTable();
            vocab_size = 0;
            train_words = 0;
            mDebugMode = debugMode;
           
        }
        virtual ~VocabWords()
        {

        }
        int AddWord(char* word);

        /*
        Build the vocabs from the train file.
        */
        void BuildFromTrainFile(char* fileName, int minReduced);
        
};


#endif