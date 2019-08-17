#if !defined(__PARAMS_h__)
#define __PARAMS_h__
#include <string>
using std::string;


#define MAX_FILE_PATH 100
typedef float real;

class Params
{
    private:     
        char output_file[MAX_FILE_PATH];
        char save_vocab_file[MAX_FILE_PATH];
        char read_vocab_file[MAX_FILE_PATH];
        char mTrainFile[MAX_FILE_PATH];
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
            mTrainFile[0] = 0;
            output_file[0] = 0;
            save_vocab_file[0] = 0;
            read_vocab_file[0] = 0;
        }
    public:
        const static int MAX_STRING_LENGTH = 1024;
        
        //The max word length of a word.
        const static int MAX_WORD_LENGTH = 100;
        
        Params(int argc, char *argv[]);
        char* toString()
        {
    
            static char buffer[MAX_STRING_LENGTH] = {0};
            //sprintf(buffer,"test:%s\n","hi");
            
            sprintf(buffer,"output file: %s\n"
                    "save_vocab_file:%s\n"
                    "read_vocab_file:%s\n"
                    "train_file:%s\n"
                    "debug_mode:%d\n"
                    "binary_mode:%d\n"
                    "cbow:%d\n"
                    "window:%d\n"
                    "hs:%d\n"
                    "negative:%d\n"
                    "num_threads:%d\n"
                    "iter:%d\n"
                    "min_count:%d\n"
                    "classes:%d\n"
                    "alpha:%f\n"
                    "starting alpha:%f\n"
                    "sample:%f\n"
                    "layer1_size:%f\n",

                    output_file,
                    save_vocab_file,
                    read_vocab_file,
                    mTrainFile,
                    debug_mode,
                    binary,
                    cbow,
                    window,
                    hs,
                    negative,
                    num_threads,
                    iter,
                    min_count,
                    classes,
                    alpha,
                    starting_alpha,
                    sample,
                    layer1_size);
                    
        return buffer;
       };

        char* getTrainFile()
        {
           return mTrainFile;
        }
       
};
#endif