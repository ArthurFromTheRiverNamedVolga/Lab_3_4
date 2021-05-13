#ifndef DERIVED2_H
#define DERIVED2_H

#include "Base.h"

class Derived2 : public Base {
public:
	Derived2(Base* parent, std::string name, int condition);
	void Signal(string&);
	void SignalKeeper(string);
};

#endif