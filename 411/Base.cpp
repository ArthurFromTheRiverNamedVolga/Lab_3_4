#include "Base.h"
#include <iostream>
#include "Application.h"
#include "Derived2.h"
#include "Derived3.h"

using namespace std;

typedef void (Base::* SIGNAL)(string&);
typedef void (Base::* SIGNAL_KEEPER)(string);

Base::Base(Base* parent, string name) {
    SetParent(parent);
    SetName(name);
}

Base::Base(Base* parent, string name, int condition) {
    SetParent(parent);
    SetName(name);
    SetCondition(condition);
}

void Base::SetCondition(int condition) {
    this->condition = condition;
}

int Base::GetCondition() {
    return condition;
}

void Base::SetName(string name) {
    this->name = name;
}

string Base::GetName() {
    return name;
}

void Base::SetParent(Base* parent) {
    this->parent = parent;
    if (parent)
        parent->children.push_back(this);
}

Base* Base::GetParent() {
    return parent;
}

void Base::PrintNames() {
    if (children.empty()) return;
    cout << '\n' << name;
    childrenIterator = children.begin();
    while (childrenIterator != children.end()) {
        cout << "  " << (*childrenIterator)->GetName();
        childrenIterator++;
    }
    childrenIterator--;
    (*childrenIterator)->PrintNames();
}

void Base::PrintReady() {
    if (children.empty()) return;
    childrenIterator = children.begin();
    while (childrenIterator != children.end()) {
        if ((*childrenIterator)->GetCondition() > 0)
            cout << "\nThe object " << (*childrenIterator)->GetName() << " is ready";
        else
            cout << "\nThe object " << (*childrenIterator)->GetName() << " is not ready";
        if (!(*childrenIterator)->children.empty()) (*childrenIterator)->PrintReady();
        childrenIterator++;
    }
}

void Base::PrintTree(string offset) {
    if (children.empty()) return;
    childrenIterator = children.begin();
    offset += "    ";
    while (childrenIterator != children.end()) {
        cout << '\n' << offset << (*childrenIterator)->GetName();
        if (!(*childrenIterator)->children.empty()) (*childrenIterator)->PrintTree(offset);
        childrenIterator++;
    }
}

Base* Base::FindObj(string name) {
    if (name[0] == '/' || name.size() == 0) {
        if (GetParent() != nullptr)
            return FindRoot()->FindObj(name);
        else
            return FindObjRouteRoot(name);
    }
    else {
        if (GetParent() != nullptr)
            return FindRoot()->FindObj(name);
        else
            return FindObjRoot(name);
    }
}

Base* Base::FindObjRoot(string name) {
    if (name == this->name) return this;
    if (children.empty()) return nullptr;
    childrenIterator = children.begin();
    while (childrenIterator != children.end()) {
        Base* tempObj = nullptr;
        if ((*childrenIterator)->GetName() == name) return *childrenIterator;
        if (!(*childrenIterator)->children.empty()) tempObj = (*childrenIterator)->FindObjRoot(name);
        if (tempObj) return tempObj;
        childrenIterator++;
    }
    return nullptr;
}

Base* Base::FindRoot() {
    if (GetParent() == nullptr) return this;
    return GetParent()->FindRoot();
}


Base* Base::FindObjRouteRoot(string route) {
    if (route == "") return this;
    string t_route = route, s_route = "";
    t_route.erase(t_route.begin());
    while (t_route.size() > 0 && t_route[0] != '/') {
        s_route += t_route[0];
        t_route.erase(t_route.begin());
    }
    childrenIterator = children.begin();
    while (childrenIterator != children.end()) {
        if ((*childrenIterator)->GetName() == s_route) return (*childrenIterator)->FindObjRouteRoot(t_route);
        childrenIterator++;
    }
    return nullptr;
}

void Base::CreateConnection(Base* to, int num) {
    Connection con;
    con.to = to;
    con.num = num;
    switch (type) {
    case 1:
        con.signal = (SIGNAL)(&Application::Signal);
        break;
    case 2:
        con.signal = (SIGNAL)(&Derived2::Signal);
        break;
    case 3:
        con.signal = (SIGNAL)(&Derived3::Signal);
        break;
    }
    switch (to->type) {
    case 1:
        con.signal_keeper = (SIGNAL_KEEPER)(&Application::Signal);
        break;
    case 2:
        con.signal_keeper = (SIGNAL_KEEPER)(&Derived2::Signal);
        break;
    case 3:
        con.signal_keeper = (SIGNAL_KEEPER)(&Derived3::Signal);
        break;
    }
    connections.push_back(con);
}

void Base::DeleteConnection(Base* to, SIGNAL signal, SIGNAL_KEEPER signal_keeper) {
    for (int i = 0; i < connections.size(); ++i) {
        if (connections[i].to == to && signal == connections[i].signal && signal_keeper == connections[i].signal_keeper) {
            connections.erase(connections.begin() + i);
            return;
        }
    }
}

void Base::GetSignal(SIGNAL signal, string& s) {
    (this->*signal)(s);
    for (auto i : connections) {
        if (i.signal == signal) {
            cout << "\nSignal to " << i.to->GetName() << " Text: " << GetName() << " -> " << s;
            (i.to->*i.signal_keeper)(s);
        }
    }
}

void Base::Signal(string&) {}

void Base::SignalKeeper(string) {}

int Base::GetType() {
    return type;
}
