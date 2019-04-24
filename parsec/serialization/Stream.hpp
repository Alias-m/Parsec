#ifndef PARSEC_PARSING_FRAMEWORK_H
#define PARSEC_PARSING_FRAMEWORK_H
#include <string>
#include <iostream>
#include <fstream>
#include "streams/reader/Reader.hpp"
#include "streams/writer/Writer.hpp"

#define PARSEC_READER(type) public Reader<type*> // NOLINT misc-macro-parentheses
#define PARSEC_WRITER(type) public Writer<type*> // NOLINT misc-macro-parentheses

class Element;
class ElementInt;
class ElementString;
class ElementBoolean;
class ElementArray;
class ElementObject;
class ElementDouble;

/**
 *  @class ContentParser "block_chain/utils/serialization/Parser.h"
 *  An abstract parser.
 *  A parser is a particular reader that only works in the string to Element way.
 *  @see ContentReader
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ContentParser
{
	public:
		ContentParser() = default;
		/**
		 *  The entry point of the parser: it reads the text and generates the first element
		 *  according to rules. Calls the corresponding methods for recursive parsing.
		 *  (opposite works as well)
		 *  @see parseContent
		 *  @see Element
		 *
		 * 	@param text a given text
		 */
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

/**
 *  @class ContentCreator "block_chain/utils/serialization/Parser.h"
 *  An abstract creator.
 *  A creator is a particular reader that only works in the Element to string way.
 *  @see ContentReader
 *  @see Element
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
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


/**
 *  @class ElementCreator "block_chain/utils/serialization/Parser.h"
 *  The Element creator class is a static factory that can generates Elements for
 *  different primitive types.
 *  @see ElementInt
 *  @see ElementDouble
 *  @see ElementString
 *  @see ElementBoolean
 *  @see ElementArray
 *  @see ElementObject
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class ElementCreator
{
	public:

		/**
		 *  Generates an Element representing a int
		 *  @see ElementInt
		 *
		 *  @param value the int value
		 *  @return the generated Element representation
		 */
		static ElementInt* create(int value);

		/**
		 *  Generates an Element representing a long long int
		 *  @see ElementInt
		 *
		 *  @param value the int value
		 *  @return the generated Element representation
		 */
		//static ElementInt* create(long long int value);

		/**
		 *  Generates an Element representing a double
		 *  @see ElementDouble
		 *
		 *  @param value the double value
		 *  @return the generated Element representation
		 */
		static ElementDouble* create(double value);

		/**
		 *  Generates an Element representing a string
		 *  @see ElementString
		 *
		 *  @param value the const char* value
		 *  @return the generated Element representation
		 */
		static ElementString* create(const char* value);

		/**
		 *  Generates an Element representing a string
		 *  @see ElementString
		 *
		 *  @param value the string value
		 *  @return the generated Element representation
		 */
		static ElementString* create(std::string value);

		/**
		 *  Generates an Element representing a boolean
		 *  @see ElementBoolean
		 *
		 *  @param value the boolean value
		 *  @return the generated Element representation
		 */
		static ElementBoolean* create(bool value);

		/**
		 *  Generates an Element representing an array
		 *  @see ElementArray
		 *
		 *  @return the generated Element representation
		 */
		static ElementArray* array();

		/**
		 *  Generates an Element representing an object
		 *  @see ElementObject
		 *
		 *  @return the generated Element representation
		 */
		static ElementObject* object();
};
#endif //BLOCK_CHAIN_PARSING_FRAMEWORK_H
