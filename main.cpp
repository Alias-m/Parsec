#include <iostream>
#include "parsec/serialization/Serializer.hpp"
#include "parsec/serialization/Unpacker.hpp"
#include "parsec/serialization/format/json/JsonCreator.hpp"
#include "parsec/serialization/format/json/JsonParser.hpp"
#include "parsec/serialization/streams/Element.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Serializer s;
    s.addSerializer<JsonCreator>();
    s.addDeserializer<JsonParser>();
    std::string format("json");
    Element* e = s.getElement("./input/20190301_000000.json", format);
    std::cout << "***" << std::endl;
    std::cout << s.serialize(e, "json", "") << std::endl;
    delete e;
    return 0;
}