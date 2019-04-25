//
// Created by default on 4/4/2561.
//

#ifndef PARSEC_SERIALIZER_H
#define PARSEC_SERIALIZER_H

#include "../utils/Factory.hpp"
#include "Unpacker.hpp"
#include "Stream.hpp"
#include "streams/package/Elementable.hpp"
#include <cstdlib>
#include <utility>
#include <functional>
#include <fstream>
#define PARSEC_CAST(__type__, __element__) dynamic_cast<__type__*>(__element__);
#define PARSEC_TO_ARRAY(__element__) PARSEC_CAST(PARSEC_ARRAY, __element__)
#define PARSEC_TO_OBJECT(__element__) PARSEC_CAST(PARSEC_OBJECT, __element__)

class Serializer
{
public:
    Serializer();

    virtual ~Serializer();

    virtual std::string serialize(const Elementable* component, const std::string& encoding, const std::string& file_name) const;

    virtual std::string serialize(Element* element, const std::string& encoding, const std::string& file_name) const;


    template<typename K, typename = std::enable_if<std::is_base_of<Elementable, K>::value>>
    std::string serialize(const std::vector<K*> components, const std::string &key, const std::string &file_name) const {
        auto * element = new PARSEC_ARRAY();
        for(auto it : components)
            PARSEC_ADD_ELEMENT(element, it->toElement())
        std::string c (serialize(element, key, file_name));
        delete element;
        return c;
    }

    template<class T, typename C, class = std::enable_if<std::is_base_of<Elementable, T>::value>>
    T* deserialize(const std::string &element, const std::string &key, const std::string &file_name) const {
        auto o = PARSEC_CAST(C, getElement(file_name, key));
        auto * t = new T();
        if(o == nullptr)
            throw ElementMismatchException();
        t->fromElement(o, this, key);
        delete o;
        return t;
    }

    template<typename T, typename K, class = std::enable_if<std::is_base_of<Elementable, K>::value>>
    std::vector<K*> deserialize(const std::string &element, const std::string &key, Unpacker<T, K> &unpacker,
                                const std::string &file_name) const {

        std::vector<K*> elements;
        Element* elem = getElement(file_name, key);
        auto a = PARSEC_TO_ARRAY(elem);
        auto values = a->get();
        for(auto v : values){
            auto o = PARSEC_TO_OBJECT(v);
            auto e = unpacker.parse(o);
            if(e) {
                if(o == nullptr)
                    throw ElementMismatchException();
                e->fromElement(o, this, key);
                elements.push_back(e);
            }
        }
        delete a;
        return elements;
    }

    Element* getElement(const std::string& file_name, std::string encoding) const;

    template<typename T, typename = std::enable_if<std::is_base_of<ContentCreator, T>::value>>
    void addSerializer() {
        creators.put(T::encoding(), []() -> ContentCreator*{return new T();});
    }

    template<typename T, typename = std::enable_if<std::is_base_of<ContentParser, T>::value>>
    void addDeserializer() {
        parsers.put(T::encoding(), []() -> ContentParser*{return new T();});
    }

protected:

    Factory<std::function<ContentCreator*()>> creators;

    Factory<std::function<ContentParser*()>> parsers;
};

#endif
