//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#include "xorcode.h"
#include <bitset>

String XORCode::encode(String text) {
    while(key.size() % 8 != 0){
        key = '0' + key;
    }
    while(text.size() % 8 != 0){
        text = '0' + text;
    }
    String result(text);
    for (size_t i = 0; i < text.size(); ++i) {
        if(text[i] != '0' && text[i] != '1')
            throw "Non-binary input for XORCode.";
        if(text[i] != key[i%key.size()])
            result[i] = '1';
        else
            result[i] = '0';

    }
    return result;
}

String XORCode::decode(String codedtext) {
    while(key.size() % 8 != 0){
        key = '0' + key;
    }
    while(codedtext.size() % 8 != 0){
        codedtext = '0' + codedtext;
    }
    String result(codedtext);
    for (size_t i = 0; i < codedtext.size(); ++i) {
        if(codedtext[i] != '0' && codedtext[i] != '1')
            throw "Non-binary input for XORCode.";
        if(codedtext[i] != key[i%key.size()])
            result[i] = '1';
        else
            result[i] = '0';

    }
    return result;
}

String XORCode::getCoderDetails() {
    return key;
}

String& XORCode::getWhichCoder() {
    return whichcoder;
}

Coder *XORCode::clone() {
    Coder* nw = new XORCode(key);
    return nw;
}


