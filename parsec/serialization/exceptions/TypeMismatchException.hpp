#include <utility>

//
// Created by mathieu on 4/25/19.
//

#ifndef PARSEC_TYPE_MISMATCH_EXCEPTION_HPP
#define PARSEC_TYPE_MISMATCH_EXCEPTION_HPP

#include <exception>
#include "../../utils/String.hpp"

class TypeMismatchException: public std::exception
{
public:
    explicit TypeMismatchException(const std::string &type): __type(std::string("ObjectMismatchException at key = ") + type) {
    }

    explicit TypeMismatchException(int type): __type(std::string("ArrayMismatchException at index = ") + to_string(type)) {
    }

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override
    {
        return __type.c_str();
    }
private:
    std::string __type;
};

#endif //PARSEC_TYPE_MISMATCH_EXCEPTION_HPP
