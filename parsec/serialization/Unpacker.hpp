#ifndef PARSEC_UNPACKER_H
#define PARSEC_UNPACKER_H
#include <functional>
#include "streams/package/Elementable.hpp"

template <typename K, typename T, typename = std::enable_if<std::is_base_of<Elementable, T>::value>>
class Unpacker
{
    public:
        T* parse(ElementObject* e) {
            K type = e->val<TemplateElement<K>>(keyword.c_str())->get();
            return types.find(type) != types.end() ? types[type]() : nullptr;
        }

        template<class Z, class = std::enable_if<std::is_base_of<T, Z>::value>>
        void register_type(K id) {
            types[id] = []() -> T*{return new Z;};
        };

        void register_keyword(std::string key) {
            keyword = key;
        }
    private:
        std::map<K, std::function<T*()> > types;
        std::string keyword;
};
#endif // PARSEC_UNPACKER_H
