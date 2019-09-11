#if !defined(__TRAIN_FILE_READER__)
#define __TRAIN_FILE_READER__

#include <stdio.h>

class TrainFileReader {
private:
    /**
     * The file pointer to the train file.
     */
    FILE *fp;
    /**
     * the file length (bytes).
     */
    long mFileSize;

public:
    TrainFileReader(const char *file);

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
    static bool ReadWord(char *word,FILE *fp);

    bool ReadWord(char *word) {
      return ReadWord(word,fp);
    }

    // Seek to the position of the file.
    void Seek(int pos);

    void StartRead();

    long getFileSize() {return mFileSize;}
};

#endif