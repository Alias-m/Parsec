//
// Created by mathieu on 4/25/19.
//

#ifndef SERIALIZER_FILE_WRITER_HPP
#define SERIALIZER_FILE_WRITER_HPP

#include "../serialization/streams/package/Elementable.hpp"
#include "../serialization/Serializer.hpp"

class FileWriter {
public:
    static void write_file(const std::string &name, const std::string &object) {
        if(!object.empty()) {
            std::ofstream file(name);
            if(file.is_open()){
                file << object;
                file.close();
            }
        }
    }

    static void write_file(const std::string &name, const Elementable* object, const std::string &format, Serializer* s) {
        write_file(name, s->serialize(object, format, name));
    }

    template<typename K, typename = std::enable_if<std::is_base_of<Elementable, K>::value>>
    static void write_file(std::string name, const std::vector<K*> objects, const std::string format, Serializer* s) {
        write_file(name, s->serialize<K>(objects, format, name));
    }

    static void write_file(const std::string &name, Element* object, const std::string &format, Serializer* s) {
        write_file(name, s->serialize(object, format, name));
    }
};
#endif //SERIALIZER_FILE_WRITER_HPP
