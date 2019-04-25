#include <iostream>
#include "../parsec/serialization/Serializer.hpp"
#include "../parsec/serialization/Unpacker.hpp"
#include "../parsec/serialization/format/json/JsonCreator.hpp"
#include "../parsec/serialization/format/json/JsonParser.hpp"
#include "../parsec/serialization/streams/Element.hpp"
#include "../parsec/File/FileWriter.hpp"
#include "../parsec/File/FileReader.hpp"
#include "JsonExample.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Serializer s;
    s.addSerializer<JsonCreator>();
    s.addDeserializer<JsonParser>();
    std::string format("json");
    std::string file("./input/20190301_000000.json");
    Element* e = s.getElement("./input/20190301_000000.json", format);
    auto result = FileReader::read_file<JsonExample, PARSEC_ARRAY>(file, format, &s);
    std::cout << s.serialize(result, "json", "") << std::endl;
    delete e;
    return 0;
}