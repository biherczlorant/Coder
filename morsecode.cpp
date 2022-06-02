//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#include "morsecode.h"

String MorseCode::encode(String text) {
    String result("");
    String eabc("abcdefghijklmnopqrstuvwxyz");
    for (size_t i = 0; i < text.size(); ++i) {
        if(text[i] == ' '){
            continue;
        }
        for (size_t j = 0; j < eabc.size(); ++j) {
            if(eabc[j] == tolower(text[i])){
                result = result + abc[j];
                result = result + ' ';
            }
        }
    }
    return result;
}

String MorseCode::decode(String codedtext) {
    String temp("");
    String result("");
    String eabc("abcdefghijklmnopqrstuvwxyz");
    for (size_t i = 0; i < codedtext.size(); ++i) {
        if(codedtext[i] != ' '){
            temp = temp + codedtext[i];
        }else{
            for (size_t j = 0; j < eabc.size(); ++j) {
                if(abc[j] == temp){
                    result = result + eabc[j];
                    temp = "";
                }
            }
        }
    }
    return result;
}

String MorseCode::getCoderDetails() {
    return {"26"};
}

String& MorseCode::getWhichCoder() {
    return whichcoder;
}

Coder *MorseCode::clone() {
    Coder* nw = new MorseCode();
    return nw;
}

