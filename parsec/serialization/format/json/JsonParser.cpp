#include "JsonParser.hpp"
#include "../../streams/Element.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>


JsonParser::JsonParser()
{
    elements['{'] = []() -> Element*{return new ElementObject();};
    elements['['] = []() -> Element*{return new ElementArray();};
    elements['\"'] = []() -> Element*{return new ElementString();};
    elements['t'] = []() -> Element*{return new ElementBoolean();};
    elements['f'] = []() -> Element*{return new ElementBoolean();};
}

void jump(std::string& text) {
    unsigned int i = 0;
    for(i = 0;text[i] == '\t' || text[i] == ' ' || text[i] == ',' || text[i] == '\n'; i++);
    text = text.substr(i);
}
void _jump(std::string& text) {
    unsigned int i = 0;
    for(i = 0;text[i] == '\t' || text[i] == ' ' || text[i] == '\n'; i++);
    text = text.substr(i);
}

JsonParser::~JsonParser() = default;

Element* JsonParser::parse(std::string& text) {
    __text = text;
    return parse();
}

Element* JsonParser::parse() {
    int i;
    Element* e = nullptr;
    jump(__text);
    char first = __text[0];
    auto it = elements.find(first);
    if(it == elements.end()){
        for(i = 0; __text[i] < 0x3A && __text[i] > 0x2F ; i++);
        if(__text[i] == '.')
            e = new ElementDouble();
        else
            e = new ElementInt();
    }
    else
        e = it->second();

    e->read(this);
    return e;
}

const std::string JsonParser::encoding() {
    return "json";
}

void JsonParser::read(ElementInt* e) {
    int total = 0;
    unsigned int i;
    for(i = 0; __text[i] < 0x3A && __text[i] > 0x2F ; i++)
        total = total*10 + (__text[i] - 0x30);
    int val = total;
    __text = __text.substr(i);
    e->set(val);
}

void JsonParser::read(ElementString* e) {
    const unsigned int checker = 1;
    unsigned int cpt = 0;
    std::string value;
    unsigned int i;
    for(i = 1; __text[i] != '"' || (cpt&checker)  ; i++)
    {
        if(__text[i] == '\\')
        {
            cpt++;
            if(!(cpt&checker))
                value += (__text[i]);
        }
        else if(__text[i] == '"' && !(cpt&checker))
            break;
        else
        {
            if(cpt&checker)
                value += __text[i - 1];
            value += (__text[i]);
            cpt = 0;
        }
    }
    i++;
    e->set(value);
    __text = __text.substr(i);
}

void JsonParser::read(ElementDouble* e) {
    double total = 0;
    int div = 0;
    unsigned int i;
    for(i = 0; (__text[i] < 0x3A && __text[i] > 0x2F) || __text[i] == '.' ; i++)
    {
        if(__text[i] == '.')
            div = 1;
        else
        {
            total = total*10 + (__text[i] - 0x30);
            div *= 10;
        }
    }
    e->set(total/div);
    __text = __text.substr(i);
}

void JsonParser::read(ElementBoolean* e) {
    unsigned int i;
    for(i = 0; __text[i] < 0x7B && __text[i] > 0x60 ; i++);
    e->set(__text.substr(0, i) == "true");
    __text = __text.substr(i);
}
void JsonParser::read(ElementArray* e) {
    std::string key;
    __text = __text.substr(1);
    jump(__text);
    char end = __text[0];
    while(end != ']')
    {
        Element* child = parse();
        jump(__text);
        end = __text[0];
        e->add(child);
    }
    __text = __text.substr(1);

}
void JsonParser::read(ElementObject* e) {
    const unsigned int checker = 1;
    __text = __text.substr(1);
    int start;
    unsigned int cpt, i;
    while(__text[0] != '}')
    {
        Element* child = nullptr;
        std::string key;
        for(start = -1, cpt = 0, i = 0; ; i++)
        {
            if(start == -1)
            {
                if(__text[i] == '"')
                    start = i;
            }
            else
            {
                if(__text[i] == '\\')
                {
                    cpt++;
                    if(!(cpt&checker))
                        key += (__text[i]);
                }
                else if(__text[i] == '"' && !(cpt&checker))
                    break;
                else
                {
                    key += (__text[i]);
                    cpt = 0;
                }
            }
        }
        __text = __text.substr(i + 2);
        child = parse();
        for(i = 0; __text[i] == '\t' || __text[i] == ' ' || __text[i] == ','; i++);
        __text = __text.substr(i);
        e->put(key, child);
        _jump(__text);

    }
    __text = __text.substr(1);
    jump(__text);
}