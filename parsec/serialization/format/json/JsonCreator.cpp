#include "JsonCreator.hpp"
#include <sstream>
#include <iterator>
#include <iomanip>
#include <cmath>
#include "../../../utils/String.hpp"


const std::string JsonCreator::encoding() {
    return "json";
}

JsonCreator::JsonCreator(): __text("") {

}

JsonCreator::~JsonCreator() = default;

std::string JsonCreator::parse(Element* e){
    if(e)
        e->write(this);
    return __text;
}

void JsonCreator::write(ElementInt *e) {
    __text.append(to_string(e->get()));
}

void JsonCreator::write(ElementString *e) {
    std::string value(e->get());
    value = replaceAll(value, "\\", "\\\\");
    value = replaceAll(value, "\n", "\\\\n");
    __text.append("\"").append(value).append("\"");
}

void JsonCreator::write(ElementDouble *e) {
    __text.append(to_string(e->get()));
}

void JsonCreator::write(ElementBoolean *e) {
    __text.append(e->get() ? "true" : "false");
}

void JsonCreator::write(ElementArray *e) {
    __text.append("[");
    auto values = e->get();
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            __text.append(",");
        (*it)->write(this);
    }
    __text.append("]");
}

void JsonCreator::write(ElementObject *e) {
    __text.append("{");
    auto values = e->get();
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(it != values.begin())
            __text.append(",");
        __text.append("\"").append((it->first)).append("\":");
        it->second->write(this);
    }
    __text.append("}");
}