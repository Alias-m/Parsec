#include "Serializer.hpp"

Element* Serializer::getElement(const std::string& file_name, const std::string key) const{
    return parsers.get(key)()->read(file_name);
}

std::string Serializer::serialize(const Elementable* component, const std::string& key, const std::string& file_name) const{
    Element* element = component->toElement();
    std::string c(serialize(element, key, file_name));
    delete element;
    return c;
}

std::string Serializer::serialize(Element* element, const std::string& key, const std::string& file_name) const{
    std::string parsed(creators.get(key)()->write(element, file_name));
    return parsed;
}

Serializer::Serializer() = default;

Serializer::~Serializer(){
    creators.clear();
    parsers.clear();
}

