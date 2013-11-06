#pragma once

#include <string>

class GenericData {
public:

	GenericData(const std::string & _name = "", void * _data = NULL) {
		name = _name;
		data = _data;
	}

	std::string name;
	void * data;
};