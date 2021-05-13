#include "Derived3.h"

Derived3::Derived3(Base* parent, std::string name, int condition) : Base(parent, name, condition) {
    type = 3;
}

void Derived3::Signal(string&) {}

void Derived3::SignalKeeper(string) {}
