#include "NeuralNetwork.h"

bool NeuralNetwork::Init() {
  unsigned long long next_random = 1;

  // Allocate the hidden layer of the network, which is what becomes the word vectors.
  // The variable for this layer is 'syn0'.s
  int ret = posix_memalign((void **)&syn0, mBlockSize, (long long)mVocabSize * mNeuronSize * sizeof(real));

  if (ret != 0) return false;

  // Randomly initialize the weights for the hidden layer (word vector layer).
  // TODO - What's the equation here?
  for (long long a = 0; a < mVocabSize; a++) for (long long b = 0; b < mNeuronSize; b++) {
      next_random = next_random * (unsigned long long)25214903917 + 11;
      syn0[a * mNeuronSize + b] = (((next_random & 0xFFFF) / (real)65536) - 0.5) / mNeuronSize;
    }

  // If we're using hierarchical softmax for training...
  if (hs) {
    ret = posix_memalign((void **)&syn1, mBlockSize, (long long)mVocabSize * mNeuronSize * sizeof(real));

    if (ret != 0) {return false;}

    for (long long a = 0; a < mVocabSize; a++) for (long long b = 0; b < mNeuronSize; b++)
        syn1[a * mNeuronSize + b] = 0;
  }

  // If we're using negative sampling for training...
  if (negative>0) {
    // Allocate the output layer of the network.
    // The variable for this layer is 'syn1neg'.
    // This layer has the same size as the hidden layer, but is the transpose.
    ret = posix_memalign((void **) &syn1neg, mBlockSize, (long long) mVocabSize * mNeuronSize * sizeof(real));

    if (ret != 0) {
      printf("Memory allocation failed\n");
      return false;
    }

    // Set all of the weights in the output layer to 0.
    for (long long a = 0; a < mVocabSize; a++)
      for (long long b = 0; b < mNeuronSize; b++)
        syn1neg[a * mNeuronSize + b] = 0;
  }

  // Create a binary tree for Huffman coding.
  // TODO - As best I can tell, this is only used for hierarchical softmax training...
  //CreateBinaryTree();

}