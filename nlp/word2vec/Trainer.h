#if !defined(__TRAINER_H__)
#define __TRAINER_H__
#include <pthread.h>
#include "params.h"
#include "WordVocab.h"

class Trainer {
private:
  float mStartingAlplha;
  pthread_t *pt;
  VocabWords *mVocabs;
public:
  Trainer() {}

  void Train(Params *params);

};
#endif