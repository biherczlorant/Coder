//
// Created by Bihercz Lóránt on 2022. 05. 02..
//


#include "filehandler.h"
#include "codelist.h"
#include "coder.h"
#include "xorcode.h"
#include "morsecode.h"

void FileHandler::writeToFile(Coder* coder) {
    String empty("");
    if(outputfilename == empty){
        throw "No output filename given.";
    }
    std::ofstream output;
    output.open(outputfilename.c_str(), std::ofstream::app);
    if(!output.is_open())
        throw "Something went wrong when opening output file.";
    output << coder->getWhichCoder().c_str() << '\n';
    output << coder->getCoderDetails().c_str() << '\n';
    output.close();

}

void FileHandler::readFromFile(CodeList& a) {
    String empty("");
    String b("");
    String m("MorseCode");
    String x("XORCode");
    if(inputfilename == empty){
        throw "No input filename given.";
    }
    std::ifstream input;
    input.open(inputfilename.c_str());
    if(!input.is_open())
        throw "Something went wrong when opening input file.";
    while(input >> b){
        if(b == x){
            input >> b;
            a.add(create<XORCode>(b));
        }else if(b == m){
            input >> b;
            a.add(create<MorseCode>(26));
        }
    }
    input.close();
}

void FileHandler::clearFile() {
    String empty("");
    if(outputfilename == empty){
        throw "No output filename given.";
    }
    std::ofstream output;
    output.open(outputfilename.c_str(), std::ofstream::trunc);
    output.close();
}


