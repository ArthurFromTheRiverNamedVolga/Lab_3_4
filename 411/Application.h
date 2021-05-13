#ifndef APP_H
#define APP_H

#include "Base.h"

class Application : public Base {
    Base* tempParent;
    Base* tempChild;
public:
    Application(Base* parent = nullptr);
    void BuildTree();
    int Execute();
    void Request();
    void ChopString(string& s);
    void SetConnections();
    void DoConnections();
    void Signal(string&);
    void SignalKeeper(string);
};

#endif