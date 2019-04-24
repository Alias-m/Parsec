#include "Stream.hpp"
#include "streams/Element.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>
/*
ElementInt* ElementCreator::create(long long int value){
	auto e = new ElementInt();
	e->set(value);
	return e;
}*/
ElementInt* ElementCreator::create(int value){
	auto e = new ElementInt();
	e->set(value);
	return e;
}
ElementString* ElementCreator::create(const char* value){
	auto e = new ElementString();
	e->set(value);
	return e;
}
ElementString* ElementCreator::create(std::string value){
	auto e = new ElementString();
	e->set(std::move(value));
	return e;
}
ElementBoolean* ElementCreator::create(bool value){
	auto e = new ElementBoolean();
	e->set(value);
	return e;
}
ElementArray* ElementCreator::array(){
	auto e = new ElementArray();
	return e;
}
ElementObject* ElementCreator::object(){
	auto e = new ElementObject();
	return e;
}
ElementDouble* ElementCreator::create(double value){
	auto e = new ElementDouble();
	e->set(value);
	return e;
}
