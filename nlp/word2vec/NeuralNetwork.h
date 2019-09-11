# if !defined(__NETWORK_H__)
#define __NETWORK_H__

#include "params.h"

class NeuralNetwork{

private:

    //This is the hidden layer weights (which is also the word vectors!)
    real *syn0;
    //This is the output layer weights *if using heirarchical softmax*
    real *syn1;
    //This is the output layer weights *if using negative sampling*
    real *syn1neg;

    int negative;

    bool hs;

    //size of the vocab space.
    int mVocabSize;

    int mNeuronSize;

    const static int mBlockSize = 128;

public:
    //hs:Hierarchical Softmax
    NeuralNetwork(int vocabSize,int neuronSize, int negative, bool hs) {
      mVocabSize = vocabSize;
      mNeuronSize = neuronSize;
      this->negative = negative;
      this->hs = hs;
    }
    bool Init();
};

#endif