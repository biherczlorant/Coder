//
// Created by Bihercz Lóránt on 2022. 05. 02..
//
#include "codelist.h"


void CodeList::add(Coder* coder) {
    Coder** tmp = new Coder*[size+1];
    for (int i = 0; i < size; ++i) {
        tmp[i] = codelist[i];
    }
    delete[] codelist;
    codelist = tmp;
    codelist[size++] = coder;
}

void CodeList::remove(int idx) {
    if(idx > size-1)
        throw "Index out of range";
    delete codelist[idx];
    size--;
    for (int i = idx; i < size; ++i) {
        codelist[i] = codelist[i+1];
    }
}

CodeList::~CodeList() {
    for (int i = 0; i < size; ++i) {
        delete codelist[i];
    }
    delete[] codelist;
}

void CodeList::saveToFile(FileHandler a, bool clear) {
    if(clear)
        a.clearFile();
    for (int i = 0; i < size; ++i) {
        a.writeToFile(this->operator[](i));
    }
}
