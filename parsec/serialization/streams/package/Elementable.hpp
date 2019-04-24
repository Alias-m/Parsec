#ifndef PARSEC_ELEMENTABLE_HPP
#define PARSEC_ELEMENTABLE_HPP
#include "../Element.hpp"

class Serializer;

/**
 *  @class Elementable "serialization/Elementable.h"
 *  The main abstract class for serialization.
 *  All possible classes that can be serialized
 *  need to implement this interface.
 *  @see Serializer
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Elementable
{
    public:

        /**
         *  A default virtual destructor
         */
        virtual ~Elementable() = default;

        /**
         *  A default constructor for initialization
         */
        Elementable() = default;

        /**
         *  The method used by the serializer to transform
         *  an object into an Element representation.
         *  @see Element
         *
         *  @return The Element representation of the object
         */
        virtual Element* toElement() const = 0;
};

#endif // PARSEC_ELEMENTABLE_HPP
