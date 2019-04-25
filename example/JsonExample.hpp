//
// Created by mathieu on 4/24/19.
//

#ifndef SERIALIZER_JSON_EXAMPLE_HPP
#define SERIALIZER_JSON_EXAMPLE_HPP

#include "../parsec/serialization/streams/package/Elementable.hpp"
#include "../parsec/serialization/streams/package/Initializer.hpp"

class JsonExample : public Elementable, public Initializer<ElementObject>, public Initializer<ElementArray>, public Initializer<ElementInt> {
public:
    Element* toElement() const override {
        auto o =  new ElementObject;
        PARSEC_PUT_INT(o, "value", 42)
        return o;
    }

    void fromElement(ElementObject* o, const Serializer* s, const std::string& encoding) override {
        auto test = PARSEC_FIND_INT(o, "value")
        auto test2 = test->get();
    }

    void fromElement(ElementArray* o, const Serializer* s, const std::string& encoding) override {
        auto test = PARSEC_GET_OBJECT(o, 0)
    }

    void fromElement(ElementInt* o, const Serializer*, const std::string&) override {
        int value = o->get();
    }
};
#endif //SERIALIZER_JSON_EXAMPLE_HPP
