#include <utility>

//
// Created by mathieu on 4/25/19.
//

#ifndef PARSEC_NOT_SUPPORTED_ELEMENT_EXCEPTION_HPP
#define PARSEC_NOT_SUPPORTED_ELEMENT_EXCEPTION_HPP

#include <exception>
#include "../../utils/String.hpp"

class NotSupportedElementException: public std::exception
{
public:
    explicit NotSupportedElementException(const std::string &type): __type(std::string("The existing element is not supported by the ") + type +".") {
    }

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override
    {
        return __type.c_str();
    }
private:
    std::string __type;
};

#endif //PARSEC_NOT_SUPPORTED_ELEMENT_EXCEPTION_HPP
