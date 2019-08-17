CC  = gcc
CPP = g++
RM = rm -rf

DBG_ENABLE = 1

SRC_PATH := .

Target := w2c

SRCS += $(wildcard $(SRC_PATH)/*.cpp)
#SRCS := word2vec.cpp params.cpp params.h TrainFileReader.h TrainFileReader.cpp

OBJS  := $(SRCS:.cpp=.o)
#OBJS := word2vec.o params.o TrainFileReader.o



#LIBS :=

INCLUDE_PATH := .

LIBRARY_PATH := lib

#CFLAGS = -lm -pthread -march=native -Wall -funroll-loops -Wno-unused-result
CFLAGS =  -pthread  -Wall -Wno-unused-result

ifeq (1, $(DBG_ENABLE))
CFLAGS += -ggdb -D_DEBUG   -g -DDEBUG=1
endif

CFLAGS += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

LDFLAGS += $(foreach lib, $(LIBRARY_PATH),-L$(lib))

word2vec.o : word2vec.cpp
	$(CPP) -c $(CFLAGS) word2vec.cpp -o word2vec.o

params.o : params.cpp params.h
	$(CPP) -c $(CFLAGS) params.cpp -o params.o

TrainFileReader.o : TrainFileReader.cpp TrainFileReader.h
	$(CPP) -c $(CFLAGS) TrainFileReader.cpp -o TrainFileReader.o

all: build

build: params.o word2vec.o TrainFileReader.o

	#$(CPP) -c $(CFLAGS) $(SRCS)
	$(CPP) $(CFLAGS) -o w2c  params.o word2vec.o TrainFileReader.o
	#$(LDFLAGS)
	#$(RM)  $(OBJS)
clean:
	$(RM) $(OBJS) $(TARGET)


#objects:word2vec.o params.o

#word2vec:$(objects)#word2vec.cpp,params.cpp
	#$(gxx) word2vec.cpp params.cpp -o word2vec $(CXXFLAGS)
#	$(gxx)  -o word2vec $(objects) $(CXXFLAGS)