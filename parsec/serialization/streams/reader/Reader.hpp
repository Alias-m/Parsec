//
// Created by mathieu on 4/24/19.
//

#ifndef PARSEC_READER_HPP
#define PARSEC_READER_HPP

template <typename T>
class Reader {
public:
    virtual void read(T array) = 0;
};
#endif //PARSEC_READER_HPP
