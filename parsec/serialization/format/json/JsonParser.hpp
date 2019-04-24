#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include "../../Stream.hpp"
#include <functional>
#include <map>
#include "../../streams/Element.hpp"

class JsonParser: public TextParser, PARSEC_READER(ElementInt),
									 PARSEC_READER(ElementString),
									 PARSEC_READER(ElementDouble),
				  					 PARSEC_READER(ElementBoolean),
				  					 PARSEC_READER(ElementArray),
				  					 PARSEC_READER(ElementObject)
{
public:
    Element* parse(std::string& text) override;
    Element* parse();
	static const std::string encoding();
    JsonParser();
    ~JsonParser() override;


	void read(ElementInt* e) override;
	void read(ElementString* e) override;
	void read(ElementDouble* e) override;
	void read(ElementBoolean* e) override;
	void read(ElementArray* e) override;
	void read(ElementObject* e) override;

private:
	std::map<const char, std::function<Element*()>> elements;
	std::string __text;
};
#endif //JSON_PARSER_H
