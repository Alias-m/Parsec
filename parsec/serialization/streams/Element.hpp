#ifndef PARSEC_ELEMENT_HPP
#define PARSEC_ELEMENT_HPP

#include "../Stream.hpp"
#include "reader/Reader.hpp"
#include "writer/Writer.hpp"
#include "../../utils/Factory.hpp"
#include "../exceptions/TypeMismatchException.hpp"
#include "../exceptions/ElementMismatchException.hpp"
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

#define PARSEC_INT ElementInt
#define PARSEC_STRING ElementString
#define PARSEC_DOUBLE ElementDouble
#define PARSEC_BOOLEAN ElementBoolean
#define PARSEC_OBJECT ElementObject
#define PARSEC_ARRAY ElementArray
#define PARSEC_PUT(__object__, __key__, __value__, __type__) __object__->put(__key__, new __type__(__value__));
#define PARSEC_PUT_INT(__object__, __key__, value) PARSEC_PUT(__object__, __key__, value, PARSEC_INT)
#define PARSEC_PUT_STRING(__object__, __key__, __value__) PARSEC_PUT(__object__, __key__, __value__, PARSEC_STRING)
#define PARSEC_PUT_DOUBLE(__object__, __key__, __value__) PARSEC_PUT(__object__, __key__, __value__, PARSEC_DOUBLE)
#define PARSEC_PUT_BOOLEAN(__object__, __key__, __value__) PARSEC_PUT(__object__, __key__, __value__, PARSEC_BOOLEAN)
#define PARSEC_PUT_ELEMENT(__object__, __key__, __value__) __object__->put(__key__, __value__);
#define PARSEC_ADD(__array__, __value__, __type__) __array__->add(new __type__(__value__));
#define PARSEC_ADD_INT(__array__, __value__) PARSEC_ADD(__array__, __value__, PARSEC_STRING)
#define PARSEC_ADD_STRING(__array__, __value__) PARSEC_ADD(__array__, __value__, PARSEC_INT)
#define PARSEC_ADD_DOUBLE(__array__, __value__) PARSEC_ADD(__array__, __value__, PARSEC_DOUBLE)
#define PARSEC_ADD_BOOLEAN(__array__, __value__) PARSEC_ADD(__array__, __value__, PARSEC_BOOLEAN)
#define PARSEC_ADD_ELEMENT(__array__, __value__) __array__->add(__value__);

#define PARSEC_AT(__object__, __key__, __type__) (__object__ == 0 ? throw ElementMismatchException(__key__) : __object__)->val<__type__>(__key__) == 0 ? throw TypeMismatchException(__key__) : __object__->val<__type__>(__key__)
#define PARSEC_FIND(__object__, __key__, __type__) PARSEC_AT(__object__, __key__, __type__);
#define PARSEC_GET(__object__, __key__, __type__) PARSEC_AT(__object__, __key__, __type__)->get();

#define PARSEC_FIND_INT(__object__, __key__) PARSEC_FIND(__object__, __key__, PARSEC_INT)
#define PARSEC_GET_INT(__object__, __key__) PARSEC_GET(__object__, __key__, PARSEC_INT)
#define PARSEC_FIND_STRING(__object__, __key__) PARSEC_FIND(__object__, __key__, PARSEC_STRING)
#define PARSEC_GET_STRING(__object__, __key__) PARSEC_GET(__object__, __key__, PARSEC_STRING)
#define PARSEC_FIND_DOUBLE(__object__, __key__) PARSEC_FIND(__object__, __key__, PARSEC_DOUBLE)
#define PARSEC_GET_DOUBLE(__object__, __key__) PARSEC_GET(__object__, __key__, PARSEC_DOUBLE)
#define PARSEC_FIND_BOOLEAN(__object__, __key__) PARSEC_FIND(__object__, __key__, PARSEC_BOOLEAN)
#define PARSEC_GET_BOOLEAN(__object__, __key__) PARSEC_GET(__object__, __key__, PARSEC_BOOLEAN)
#define PARSEC_FIND_OBJECT(__object__, __key__) PARSEC_FIND(__object__, __key__, PARSEC_OBJECT)
#define PARSEC_GET_OBJECT(__object__, __key__) PARSEC_GET(__object__, __key__, PARSEC_OBJECT)
#define PARSEC_FIND_ARRAY(__object__, __key__) PARSEC_FIND(__object__, __key__, PARSEC_ARRAY)
#define PARSEC_GET_ARRAY(__object__, __key__) PARSEC_GET(__object__, __key__, PARSEC_ARRAY)

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
    explicit TemplateElement(const T value): __value(value) {}
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
