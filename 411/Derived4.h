#ifndef DERIVED4_H
#define DERIVED4_H

#include "Base.h"

class Derived4 : public Base {
public:
	Derived4(Base* parent, std::string name, int condition);
};

#endif