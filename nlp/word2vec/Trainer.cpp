#include "Trainer.h"
#include "params.h"


void Trainer::Train(Params *params) {


  mStartingAlplha = params->getAlpha();
  pt = (pthread_t *)malloc(params->getThreadNum() * sizeof(pthread_t));
  mVocabs = new VocabWords(params->extractVocabParams());
  mVocabs->Build();


}