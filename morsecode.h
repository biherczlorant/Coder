//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#ifndef CODER_MORSECODE_H
#define CODER_MORSECODE_H

#include "coder.h"
#include <fstream>

class MorseCode: public Coder{
    int size;
    String whichcoder = "MorseCode";
    String* abc;
public:
    MorseCode(int s = 26):size(s){
        abc = new String[size];
        std::ifstream file;
        file.open("morseabc.txt");
        if(!file.is_open())
            throw "Something went wrong when importing morseabc.";
        for (int i = 0; i < size; ++i) {
            file >> abc[i];
        }
        file.close();
    }
    String encode(String text);
    String decode(String codedtext);
    String getCoderDetails();
    String& getWhichCoder();
    Coder* clone();
    ~MorseCode(){delete[] abc;}
};

#endif //CODER_MORSECODE_H
