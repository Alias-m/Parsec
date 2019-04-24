//
// Created by default on 4/4/2561.
//

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../utils/Factory.hpp"
#include "Unpacker.hpp"
#include "Stream.hpp"
#include "streams/package/Elementable.hpp"
#include <cstdlib>
#include <utility>
#include <functional>
#include <fstream>
/**
 *  @class Serializer
 *  A basic serializer.
 *  The class Serializer implements all of the
 *  serialization and deserialization methods.
 *  @see ContentCreator
 *  @see ContentParser
 *  @see Element
 *  @see ElementObject
 *  @see Elementable
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class Serializer
{
	//TEst
public:

    /**
     *  Initialize the Serializer with default readers:
     *  - json creator
     *  - json parser
     *  They can be used as encoding
     *  @see JsonCreator
     *  @see JsonParser
     */
    Serializer();

    /**
     * Default destructor that clears the factories
     */
     virtual ~Serializer();

    /**
     *  Serialize a Elementable object
     *  @see Elementable
     *  @see ContentCreator
     *
     * 	@param component the component to be serialized
     * 	@param encoding the key to choose the creator
     * 	@return the serialized string
     */
    virtual std::string serialize(const Elementable* component, const std::string& encoding, const std::string& file_name) const;

    /**
     *  Serialize an Element object
     *  @see Element
     *  @see ContentCreator
     *
     * 	@param element the element to be serialized
     * 	@param encoding the key to choose the creator
     * 	@return the serialized string
     */
    virtual std::string serialize(Element* element, const std::string& encoding, const std::string& file_name) const;


    template<typename K, typename = std::enable_if<std::is_base_of<Elementable, K>::value>>
    std::string serialize(const std::vector<K*> components, const std::string &key, const std::string &file_name) const {/*
        auto * element = new ElementArray();
        for(auto it : components) {
            element->add(it->toElement());
        }
        std::string c (serialize(element, key, file_name));
        delete element;
        return c;*/
        return "";
    }

    template<class T, class = std::enable_if<std::is_base_of<Elementable, T>::value>>
    T* deserialize(const std::string &element, const std::string &key, const std::string &file_name) const {

        //ElementObject* o = dynamic_cast<ElementObject*>(getElement(file_name, key));
        auto * t = new T();
        //t->__init__(o, this, key);
        //delete o;
        return t;
    }

    template<typename T, typename K, class = std::enable_if<std::is_base_of<Elementable, K>::value>>
    std::vector<K*> deserialize(const std::string &element, const std::string &key, Unpacker<T, K> &unpacker,
                                const std::string &file_name) const {

        std::vector<K*> elements;/*
        Element* elem = getElement(file_name, key);
        auto a = dynamic_cast<ElementArray*>(elem);
        for(auto v : a->values){
            auto o = dynamic_cast<ElementObject*>(v);
            auto e = unpacker.parse(o);
            if(e) {
                e->__init__(o, this, key);
                elements.push_back(e);
            }
        }
        delete a;*/
        return elements;
    }
    /**
     *  Deserialize a given string to obtain an ElementObject
     *  @see ContentParser
     *  @see ElementObject
     *
     * 	@param str the string to be deserialized
     * 	@param encoding the key to choose the parser
    * 	@return The Element representation of the string
    */
    Element* getElement(const std::string& file_name, std::string encoding) const;

    /**
     *  Add a custom creator to the list
     *  @see ContentCreator
    */
    template<typename T, typename = std::enable_if<std::is_base_of<ContentCreator, T>::value>>
    void addSerializer() {
        creators.put(T::encoding(), []() -> ContentCreator*{return new T();});
    }

    /**
     *  Add a custom parser to the list
     *  @see ContentParser
    */
    template<typename T, typename = std::enable_if<std::is_base_of<ContentParser, T>::value>>
    void addDeserializer() {
        parsers.put(T::encoding(), []() -> ContentParser*{return new T();});
    }

    std::string read_file(const std::string &name) const {
        std::ifstream file(name);
        std::string serialized;
        while (file.is_open()) {
            std::string line;
            while (std::getline(file, line))
                serialized += line + "\n";
            file.close();
        }
        return serialized;
    }

    Element* read_file(const std::string &name, const std::string &format) const {
        return getElement(name, format);
    }

    void write_file(const std::string &name, const std::string &object) const{
        if(!object.empty()) {
            std::ofstream file(name);
            if(file.is_open()){
                file << object;
                file.close();
            }
        }
    }

    void write_file(const std::string &name, const Elementable* object, const std::string &format) const{
        write_file(name, serialize(object, format, name));
    }

    template<typename K, typename = std::enable_if<std::is_base_of<Elementable, K>::value>>
    void write_file(std::string name, const std::vector<K*> objects, const std::string format) const{
        write_file(name, serialize<K>(objects, format, name));
    }

    void write_file(const std::string &name, Element* object, const std::string &format) const{
        write_file(name, serialize(object, format, name));
    }

    template<class T, class = std::enable_if<std::is_base_of<Elementable, T>::value>>
    T* read_file(std::string name, const std::string format) const {
        return deserialize<T>(read_file(name), format, name);
    }

    template<typename T, typename K, typename = std::enable_if<std::is_base_of<Elementable, K>::value>>
    std::vector<K*> read_file(std::string name, const std::string format, Unpacker<T, K>& unpacker) const {
        return deserialize<T, K>(read_file(name), format, unpacker, name);
    }
protected:

    /**
     * The factory of different creators
     * @see Factory
     * @see ContentCreator
     */
    Factory<std::function<ContentCreator*()>> creators;

    /**
     * The factory of different parsers
     * @see Factory
     * @see ContentParser
     */
    Factory<std::function<ContentParser*()>> parsers;
};


#endif //BLOCK_CHAIN_SERIALIZER_H
