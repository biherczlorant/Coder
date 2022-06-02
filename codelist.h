//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#ifndef CODER_CODELIST_H
#define CODER_CODELIST_H


#include "coder.h"
#include "filehandler.h"


class CodeList {
    Coder** codelist;
    int size;
public:
    CodeList() : size(0) { codelist = new Coder *[1]; }
    /** @notice CodeList copy constructor
     *
     *
     *
     */
    CodeList(const CodeList &cl) {
        if(this->size != 0){
            delete[] codelist;
        }
        this->size = cl.size;
        this->codelist = new Coder*[cl.size];
        for (int i = 0; i < cl.size; ++i) {
            this->codelist[i] = cl.codelist[i]->clone();
        }
    }
    /** @notice CodeList operator[]
     *  @param idx index of an item
     *  @return a coder item
     */
    Coder *operator[](int idx) { return codelist[idx]; }
    /** @notice Gets the size of a CodeList
     * @return int size
     */
    int getSize() const {return size;}
    /** @notice Adds a coder to a CodeList
     *  @param coder Coder* which we add to the list
     */
    void add(Coder *coder);
    /** @notice Removes a coder from a CodeList
     * @param idx remove the coder with this index
     */
    void remove(int idx);
    /** @notice Saves a CodeList to a file
     * @param a FileHandler object
     */
    void saveToFile(FileHandler a, bool clear = true);
    ~CodeList();

};


#endif //CODER_CODELIST_H
