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
        o->put("value", new ElementInt(42));
    }

    void fromElement(ElementObject* o, const Serializer* s, const std::string& encoding) override {
        auto test = o->val<ElementInt>("value")->get();
        auto test2 = o->get();
    }

    void fromElement(ElementArray* o, const Serializer* s, const std::string& encoding) override {
        auto test = o->val<ElementInt>(0)->get();
        auto test2 = o->get();
    }

    void fromElement(ElementInt* o, const Serializer*, const std::string&) override {
        int value = o->get();
    }
};
#endif //SERIALIZER_JSON_EXAMPLE_HPP
