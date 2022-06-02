//
// Created by Bihercz Lóránt on 2022. 05. 02..
//

#ifndef CODER_CREATE_HPP
#define CODER_CREATE_HPP

#include "coder.h"

template<class Code, typename ...ARGS>
Coder* create(ARGS && ...args) {
    return new Code(std::forward<ARGS>(args)...);
}

#endif //CODER_CREATE_HPP
