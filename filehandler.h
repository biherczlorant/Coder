//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#ifndef CODER_FILEHANDLER_H
#define CODER_FILEHANDLER_H

#include <iostream>
#include <fstream>

#include "string5.h"
#include "coder.h"
#include "create.hpp"



class CodeList;

class FileHandler{
    String inputfilename;
    String outputfilename;
public:
    FileHandler(String i = "", String o = ""):inputfilename(i), outputfilename(o){}
    /** @notice Sets input file for the FileHandler object
     * @param filename name of the input file
     */
    void setInput(String filename){inputfilename = filename;}
    /** @notice Sets output file for the FileHandler object
     * @param filename name of the output file
     */
    void setOutput(String filename){outputfilename = filename;}
    /** @notice Gets input file for the FileHandler object
     * @return String input filename
     */
    String getInput(){return inputfilename;}
    /** @notice Gets output file for the FileHandler object
     * @return String output filename
     */
    String getOutput(){return outputfilename;}
    /** @notice Writes a Coder object to a file
     * @param coder Coder object which we write to a file
     */
    void writeToFile(Coder* coder);
    /** @notice Reads from input file to a CodeList object
     * @param a CodeList which we read to
     */
    void readFromFile(CodeList& a);
    /** @notice Clears file
     */
    void clearFile();

};
#endif //CODER_FILEHANDLER_H
