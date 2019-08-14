#if !defined(__PARAMS_h__)
#define __PARAMS_h__

#define MAX_FILE_PATH 100
typedef int real;

class Params
{
    private:
        char output_file[MAX_FILE_PATH];
        char save_vocab_file[MAX_FILE_PATH];
        char read_vocab_file[MAX_FILE_PATH];
        char train_file[MAX_FILE_PATH]= {0};
        int debug_mode = 2;
        int binary = 0;
        int cbow = 1;
        int window = 5;
        int hs = 0;
        int negative = 5;
        int num_threads = 12;
        int iter = 5;
        int min_count = 5;
        int classes = 0;
        /*
         * TODO- Learning rate. 
         */
        real alpha = 0.025;
        
        /*
        * ======== starting_alpha ========
        */
        real starting_alpha;
        /* ======== sample ========
        * This parameter controls the subsampling of frequent words.
        * Smaller values of 'sample' mean words are less likely to be kept.
        * Set 'sample' to 0 to disable subsampling.
        * See the comments in the subsampling section for more details.
        */
        real sample = 1e-3;
         
        /*  
        * This is the number of features in the word vectors.
        * It is the number of neurons in the hidden layer of the model.
        */
        int layer1_size = 100;

        static int ArgPos(char *str, int argc, char **argv);
    protected:
        Params()
        {
            output_file[0] = 0;
            save_vocab_file[0] = 0;
            read_vocab_file[0] = 0;
        }
    public:
       Params(int argc, char *argv[]);
};
#endif