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

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.8.1/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/Mac/code/machine_learning/nlp/word2vec/CMakeFiles /Users/Mac/code/machine_learning/nlp/word2vec/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/Mac/code/machine_learning/nlp/word2vec/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(RM) $(OBJS) $(TARGET)


#objects:word2vec.o params.o

#word2vec:$(objects)#word2vec.cpp,params.cpp
	#$(gxx) word2vec.cpp params.cpp -o word2vec $(CXXFLAGS)
#	$(gxx)  -o word2vec $(objects) $(CXXFLAGS)