#ifndef PARSEC_STREAM_H
#define PARSEC_STREAM_H
#include <string>
#include <iostream>
#include <fstream>
#include "streams/reader/Reader.hpp"
#include "streams/writer/Writer.hpp"

#define PARSEC_READER(__type__) public Reader<__type__*> // NOLINT misc-macro-parentheses
#define PARSEC_WRITER(__type__) public Writer<__type__*> // NOLINT misc-macro-parentheses

class Element;

class ContentParser
{
	public:
		ContentParser() = default;
		virtual Element* read(const std::string& file_name) = 0;
		virtual Element* parse(std::string& text) = 0;
		virtual ~ContentParser() = default;

};

class BinaryParser: public ContentParser {
public:
	Element* read(const std::string& filename) override {
		std::string name(filename);
		return parse(name);
	}
};

class TextParser: public ContentParser {
public:
	Element* read(const std::string& filename) override {
		std::ifstream file(filename);
		std::string serialized;
		while (file.is_open()) {
			std::string line;
			while (std::getline(file, line))
				serialized += line + "\n";
			file.close();
		}
		return parse(serialized);
	}
};

class ContentCreator
{
	public:
	virtual std::string write(Element* e, const std::string& file_name) = 0;

	virtual std::string parse(Element* e) = 0;

	ContentCreator() = default;
	virtual ~ContentCreator() = default;

	template <typename T>
	std::string write(T t) {
		std::cout << "Writing element value to file" << std::endl;
		return "";
	}
};

class BinaryCreator: public ContentCreator {
public:
	std::string write(Element* e, const std::string& filename) override {
		parse(e);
		return filename;
	}
};

class TextCreator: public ContentCreator {
public:
	std::string write(Element* e, const std::string& filename) override {
		std::string serialized(parse(e));
		std::ofstream file(filename);
		if(file.is_open()){
			file << serialized;
			file.close();
		}
		return serialized;
	}
};

#endif //PARSEC_STREAM_H
