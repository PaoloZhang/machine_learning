#if !defined(__TRAIN_FILE_READER__)
#define __TRAIN_FILE_READER__

#include <stdio.h>

class TrainFileReader {
private:
    /**
     * The file pointer to the train file.
     */
    FILE *fp;

public:
    TrainFileReader(char *file);

    virtual ~TrainFileReader() {
        if (fp != 0) {
            fclose(fp);
            fp = 0;
        }
    }

    /**
    * Reads a single word from a file, assuming space + tab + EOL to be word
    * boundaries.
    *
    * Parameters:
    *   word - A char array allocated to hold the maximum length string.
    *   return - false:fail to read a word.
    *            true: succeed to read a word.
    */
    bool ReadWord(char *word);

    void StartRead();
};

#endif