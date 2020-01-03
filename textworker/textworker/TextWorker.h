//
// Created by perepelicin on 30.06.19.
//

#ifndef INC_1STLECTION_TEXTWORKER_H
#define INC_1STLECTION_TEXTWORKER_H

//Считать слова из входного потока
//посчитать количество каждого из слов и вывести их
//в каждом из слов посчитать количество вхождений символов не являющихся цифрами.

#include <cstdlib>
#include <iostream>
#include <cstring>

class TextWorker
{
    char** words;
    int* quantities;
    const size_t maxLength;
    size_t wordsQuantity;
public:
    TextWorker() : maxLength{10}, wordsQuantity{0}
    {
        using namespace std;

        auto* word = new char[maxLength];
        while(true)
        {
            cin >> word;
            if(!strcmp(word,"stop"))
            {
                break;
            }
            auto find = Find(word);
            if(find == -1)
            {
                if(wordsQuantity == 0)
                {
                    words = new char*[1];
                    words[0] = new char[strlen(word)+1];
                    strcpy(words[0], word);
                    quantities = new int [1];
                    quantities[0] = 1;
                    ++wordsQuantity;
                }
                else
                {
                    ++wordsQuantity;
                    CopyAndPaste();
                    words[wordsQuantity-1] = new char[strlen(word)+1];
                    strcpy(words[wordsQuantity-1], word);
                    AddQuantity();
                }

            }
            else
            {
                ++quantities[find];
            }
        }


        delete [] word;
    }

    ~TextWorker()
    {
        if(wordsQuantity == 0)
        {
            return;
        }
        for(int index = 0; index < wordsQuantity; index++)
        {
            delete[] words[index];
        }
        delete [] words;
        delete [] quantities;
    }

    void Output()
    {
        for(int index = 0; index < wordsQuantity; index++)
        {
            std::cout << words[index] << ' ' << quantities[index] << std::endl;
        }
    }
private:
    int Find(const char *word)
    {
        for(int index = 0; index < wordsQuantity; index++)
        {
            if(!strcmp(words[index], word))
            {
                return index;
            }
        }
        return -1;
    }
    void CopyAndPaste()
    {
        char** toCopy = new char*[wordsQuantity-1];
        for(size_t index = 0; index < wordsQuantity - 1; index++)
        {
            toCopy[index] = new char[strlen(words[index]+1)];
            strcpy(toCopy[index], words[index]);
            delete [] words[index];
        }
        delete [] words;
        words = new char*[wordsQuantity];
        for(size_t index = 0; index < wordsQuantity - 1; index++)
        {
            words[index]= new char[strlen(toCopy[index]+1)];
            strcpy(words[index], toCopy[index]);
        }
    }

    void Copy(char* to, const char* from)
    {
        auto length = StringLength(from) + 1;
        to = new char[length];
        for(size_t index = 0; index < length; index++)
        {
            *(to+index) = from[index];
        }
    }

    size_t StringLength(const char *string)
    {
        size_t counter = 0;
        for( ;string[counter] != 0; counter++);
        return counter;
    }

    void AddQuantity()
    {
        CopyLength();
        quantities[wordsQuantity-1] = 1;
    }
    void CopyLength()
    {
        int* toCopy = new int[wordsQuantity-1];

        for(int index = 0; index < wordsQuantity; index++)
        {
            toCopy[index] = quantities[index];
        }
        delete [] quantities;
        quantities = new int[wordsQuantity];
        for(int index = 0; index < wordsQuantity; index++)
        {
            quantities[index] = toCopy[index];
        }
        delete [] toCopy;
    }
};


#endif //INC_1STLECTION_TEXTWORKER_H
