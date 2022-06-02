//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#ifndef CODER_XORCODE_H
#define CODER_XORCODE_H

#include "coder.h"
#include <iostream>
class XORCode: public Coder{
    String key;
    String whichcoder = "XORCode";
public:
    XORCode(String k = ""):key(k){
        for (size_t i = 0; i < k.size(); ++i) {
            if(k[i] != '1' && k[i] != '0')
                throw "Non-binary character in key.";
        }
    }
    String encode(String text);
    String decode(String codedtext);
    String getCoderDetails();
    String& getWhichCoder();
    Coder* clone();
};

#endif //CODER_XORCODE_H
