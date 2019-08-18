#include "TrainFileReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "params.h"

TrainFileReader::TrainFileReader(char *file) 
{   
    fp = 0;
    if (file != 0)
    {
        fp = fopen(file, "rb");
        if (fp != 0)
        {
            fseek(fp, 0, SEEK_SET);
        }
    }
}

    bool TrainFileReader::ReadWord(char* word)
    {
        if (fp != 0)
        {
            if (feof(fp)) return false;
            // index is the index into 'word'.
            int index = 0;
            char ch;
  
            // Read until the end of the word or the end of the file.
            while (!feof(fp)) 
            {
                // Get the next character.
                ch = fgetc(fp);
                // ASCII Character 13 is a carriage return 'CR' whereas character 10 is 
                // newline or line feed 'LF'.
                if (ch == 13) continue;
    
                 // Check for word boundaries...
                if ((ch == ' ') || (ch == '\t') || (ch == '\n')) 
                {
                // If the word has at least one character, we're done.
                    if (index > 0) 
                    {
                        // Put the newline back before returning so that we find it next time.
                        if (ch == '\n') 
                        {
                            ungetc(ch, fp);
                        }
                        
                        break;
                    }
                    // If the word is empty and the character is newline, treat this as the
                    // end of a "sentence" and mark it with the token </s>.
                    if (ch == '\n') 
                    {
                        strcpy(word, (char *)"</s>");
                            return true;
                        // If the word is empty and the character is tab or space, just continue
                        // on to the next character.     
                    }   
                    else continue;
                }
    
                // If the character wasn't space, tab, CR, or newline, add it to the word.
                word[index] = ch;
                index++;
    
                // If the word's too long, truncate it, but keep going till we find the end
                // of it.
                if (index >= Params::MAX_STRING_LENGTH - 1) 
                {
                    index--;
                }
            }
            // Terminate the string with null.
            word[index] = 0;
            return true;
        }
        return false;
    }

void TrainFileReader::StartRead()
{
    if (fp == 0) return;

    char word[Params::MAX_WORD_LENGTH];
    fseek(fp, 0, SEEK_SET);
    int wordCount = 0;
    while(1)
    {
        if (feof(fp)) break;
        ReadWord(word);
        wordCount++;
        if (wordCount % 10000 == 0)
        {
            printf("%s.",word);
        }
    }
    printf("wordcount: %d\n",wordCount);
}
