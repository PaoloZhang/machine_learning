#if !defined(__PARAMS_h__)
#define __PARAMS_h__

#include <string>

using std::string;

typedef float real;

const static int MAX_FILE_PATH = 100;

class VocabParams {
protected:
    char save_vocab_file[MAX_FILE_PATH];
    char read_vocab_file[MAX_FILE_PATH];
    char mTrainFile[MAX_FILE_PATH];
    int min_count = 5;
public:
    VocabParams() {
      mTrainFile[0] = 0;
      save_vocab_file[0] = 0;
      read_vocab_file[0] = 0;
    }

    const char *getTrainFile() {
      return mTrainFile;
    }

    const char* getSaveVocabFile(){
      return save_vocab_file;
    }

    const char* getReadVocabFile() {
      return read_vocab_file;
    }

    //The min frequency of the tokens;
    int getMinCount() {
      return min_count;
    }
};

class Params: VocabParams{

private:
    //Common Params
    int debug_mode = 2;

    //Vocab Params.


    char output_file[MAX_FILE_PATH];

    int binary = 0;
    int cbow = 1;
    int window = 5;
    int hs = 0;
    int negative = 5;
    int num_threads = 12;
    int iter = 5;

    int classes = 0;
    /*
     * TODO- Learning rate.
     */
    real alpha = 0.025;

    /*
    * ======== starting_alpha ========
    */
    //real starting_alpha;
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

    Params() {
      VocabParams();
      output_file[0] = 0;

    }
    struct ObjectCreator {
        ObjectCreator() {
          Params::getInstance();
        }
    };
    static ObjectCreator objectCreator;

    static int ArgPos(char *str, int argc, char **argv);


public:

    const static int MAX_STRING_LENGTH = 1024;

    //The max word length of a word.
    const static int MAX_WORD_LENGTH = 100;

    //The max Length of one sentence.(The number of the words.)
    const static int MAX_SENTENCE_LENGTH = 1000;

    void Parse(int argc, char *argv[]);


    const char *toString() {

      static char buffer[MAX_STRING_LENGTH] = {0};
      //sprintf(buffer,"test:%s\n","hi");

      sprintf(buffer, "output file: %s\n"
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
              sample,
              layer1_size);

      return buffer;
    };



    int getDebugMode() {
      return debug_mode;
    }

    // return the layer1 size: the neurons of the hidden layer.
    int getLayer1Size() {return layer1_size;}

    float getAlpha() {return alpha;}
    int getThreadNum(){return num_threads;}

    static Params* getInstance();

    VocabParams* extractVocabParams() {
      return this;
    }

};


#endif