#include "Derived2.h"

Derived2::Derived2(Base* parent, std::string name, int condition) : Base(parent, name, condition) {
    type = 2;
}

void Derived2::Signal(string&) {}

void Derived2::SignalKeeper(string) {}
