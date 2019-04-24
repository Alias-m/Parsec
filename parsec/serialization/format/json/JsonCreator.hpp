#ifndef JSON_CREATOR_H
#define JSON_CREATOR_H

#include "../../Stream.hpp"
#include "../../streams/Element.hpp"

#include <functional>
#include <map>

class JsonCreator: public TextCreator, PARSEC_WRITER(ElementInt),
                                       PARSEC_WRITER(ElementString),
                                       PARSEC_WRITER(ElementDouble),
                                       PARSEC_WRITER(ElementBoolean),
                                       PARSEC_WRITER(ElementArray),
                                       PARSEC_WRITER(ElementObject)
{
public:
    std::string parse(Element* e) override;

    void write(ElementInt* e) override;
    void write(ElementString *e) override;
    void write(ElementDouble *e) override;
    void write(ElementBoolean *e) override;
    void write(ElementArray *e) override;
    void write(ElementObject *e) override;

    static const std::string encoding();

    JsonCreator();

    ~JsonCreator() override;

private:
    std::string __text;
};
#endif //JSON_CREATOR_H
