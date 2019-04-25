//
// Created by mathieu on 4/25/19.
//

#ifndef SERIALIZER_FILE_READER_HPP
#define SERIALIZER_FILE_READER_HPP

#include "../serialization/streams/package/Elementable.hpp"
#include "../serialization/Serializer.hpp"

class FileReader {
public:
    template<class T, typename C, class = std::enable_if<std::is_base_of<Elementable, T>::value>>
    static T* read_file(std::string name, const std::string format, Serializer* s) {
        return s->deserialize<T, C>(read_file(name, s), format, name);
    }

    static Element* read_file(const std::string &name, const std::string &format, Serializer* s) {
        return s->getElement(name, format);
    }

    template<typename T, typename K, typename = std::enable_if<std::is_base_of<Elementable, K>::value>>
    static std::vector<K*> read_file(std::string name, const std::string format, Serializer* s, Unpacker<T, K>& unpacker) {
        return s->deserialize<T, K>(read_file(name, s), format, unpacker, name);
    }

    static std::string read_file(const std::string &name, Serializer* s) {
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

};
#endif //SERIALIZER_FILE_READER_HPP
