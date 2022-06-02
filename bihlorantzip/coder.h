//
// Created by Bihercz Lóránt on 2022. 05. 02..
//
#ifndef CODER_CODER_H
#define CODER_CODER_H

#include <iostream>
#include "string5.h"

/// Pure virtual (interface) class
class Coder{
public:
    /** @notice Clones a Coder object
     * @return Coder* copied object
     */
    virtual Coder* clone() = 0;
    /** @notice Encodes a given string
     * @return Encoded String
     */
    virtual String encode(String text) = 0;
    /** @notice Decodes a given string
     * @return Decoded String
     */
    virtual String decode(String codedtext) = 0;
    /** @notice Returns a coders details
     * @return Coders details
     */
    virtual String getCoderDetails() = 0;
    /** @notice Returns which coder is it
     * @return Which coder type is this
     */
    virtual String& getWhichCoder() = 0;
    virtual ~Coder(){};
};
#endif //CODER_CODER_H
