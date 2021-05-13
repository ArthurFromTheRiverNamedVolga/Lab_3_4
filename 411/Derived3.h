#ifndef DERIVED3_H
#define DERIVED3_H

#include "Base.h"

class Derived3 : public Base {
public:
	Derived3(Base* parent, std::string name, int condition);
	void Signal(string&);
	void SignalKeeper(string);
};

#endif