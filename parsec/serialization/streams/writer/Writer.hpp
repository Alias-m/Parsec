#ifndef PARSEC_WRITER_HPP
#define PARSEC_WRITER_HPP

template <typename T>
class Writer {
public:
    virtual void write(T array) = 0;
};
#endif //PARSEC_WRITER_HPP
