#ifndef PARSEC_ELEMENT_HPP
#define PARSEC_ELEMENT_HPP

#include "../Stream.hpp"
#include "reader/Reader.hpp"
#include "writer/Writer.hpp"
#include "../../utils/Factory.hpp"
#include <map>
#include <typeinfo>
#include <vector>
#include <utility>

#define CONSTRUCTOR(label, primitive) label() {}  \
                                      explicit label(const primitive& value): TemplateElement<primitive>(value) {}
#define READER inline void read(ContentParser* parser) override { dynamic_cast<Reader<decltype(this)>*>(parser)->read(this); }
#define WRITER inline void write(ContentCreator* creator) override {  dynamic_cast<Writer<decltype(this)>*>(creator)->write(this); }
#define PARSEC_ELEMENT READER WRITER
#define PARSEC_PRIMITIVE(label, primitive) class label : public TemplateElement<primitive> { public: CONSTRUCTOR(label, primitive) PARSEC_ELEMENT };  // NOLINT misc-macro-parentheses
#define PARSEC_ATTRIBUTES(type) public: inline void set(type value) { __value = value; } \
                                        inline type get() {return __value;} \
                                protected: type __value;                                                                // NOLINT misc-macro-parentheses

class Element {
public:
    virtual void read(ContentParser* parser) = 0;
    virtual void write(ContentCreator* creator) = 0;
    virtual ~Element() = default;
};

template<typename T>
class TemplateElement: public Element {
public:
    TemplateElement() = default;
    TemplateElement(const T value): __value(value) {}
    PARSEC_ELEMENT
    PARSEC_ATTRIBUTES(T)
};

PARSEC_PRIMITIVE(ElementInt, int)
PARSEC_PRIMITIVE(ElementString, std::string)
PARSEC_PRIMITIVE(ElementDouble, double)
PARSEC_PRIMITIVE(ElementBoolean, bool)

class ElementArray : public TemplateElement<std::vector<Element*>> {
public:
    PARSEC_ELEMENT
    void add(Element* value) {
        __value.emplace_back(value);
    }
    ~ElementArray() override {
        for(auto it : __value)
            delete(it);
    }
    template<typename T, typename = std::enable_if<std::is_base_of<Element, T>::value>>
    T* val(unsigned int index) {
        return dynamic_cast<T*>(__value.at(index));
    }
};

class ElementObject : public TemplateElement<Factory<Element*>> {
public:
    PARSEC_ELEMENT
    void put(const std::string &key, Element* value) {
        __value.put(key, value);
    }

    ~ElementObject() override {
        for(auto &it : __value)
            delete(it.second);
    }

    template<typename T, typename = std::enable_if<std::is_base_of<Element, T>::value>>
    T* val(const std::string& key) {
        return dynamic_cast<T*>(__value.get(key));;
    }
};
#endif //PARSEC_ELEMENT_HPP
