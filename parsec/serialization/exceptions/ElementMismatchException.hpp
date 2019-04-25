#include <utility>

//
// Created by mathieu on 4/25/19.
//

#ifndef PARSEC_ELEMENT_MISMATCH_EXCEPTION_HPP
#define PARSEC_ELEMENT_MISMATCH_EXCEPTION_HPP

#include <exception>
#include "../../utils/String.hpp"

class ElementMismatchException: public std::exception
{
public:
    explicit ElementMismatchException(const std::string &type): __type(std::string("ElementMismatchException at key = ") + type + ". The element is not an object.") {
    }

    explicit ElementMismatchException(int type): __type(std::string("ElementMismatchException at index = ") + to_string(type) + ". The element is not an array.") {
    }

    explicit ElementMismatchException(): __type("ElementMismatchException at initialization. Parsec cannot initialize the object because the deserialized element doesn't match the fromElement method signature.") {
    }

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override
    {
        return __type.c_str();
    }
private:
    std::string __type;
};

#endif //PARSEC_ELEMENT_MISMATCH_EXCEPTION_HPP
