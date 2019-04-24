//
// Created by mathieu on 4/24/19.
//

#ifndef PARSEC_INITIALIZER_HPP
#define PARSEC_INITIALIZER_HPP

#include "../Element.hpp"
#include "../../Serializer.hpp"

template<typename T, typename = std::enable_if<std::is_base_of<Element, T>::value>>
class Initializer {
public:
    virtual void fromElement(T*, const Serializer* s, const std::string& encoding) = 0;
};
#endif //PARSEC_INITIALIZER_HPP
