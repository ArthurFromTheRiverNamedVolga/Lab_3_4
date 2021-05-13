#include "Application.h"
#include "Derived2.h"
#include "Derived3.h"

#include <cstring>
#include <iostream>

typedef void (Base::* SIGNAL)(string&);
typedef void (Base::* SIGNAL_KEEPER)(string);

using namespace std;

Application::Application(Base* parent) : Base(parent) {
    type = 1;
}

void Application::Signal(string&) {}

void Application::SignalKeeper(string) {}

void Application::BuildTree() {
    string parentName, childName;
    int type, condition;
    cin >> parentName;
    SetName(parentName);
    SetCondition(1);
    tempParent = this;
    while (true) {
        cin >> parentName;
        if (parentName == "endtree") return;
        cin >> childName >> type >> condition;
        tempParent = FindObj(parentName);
        if (tempParent == nullptr) { tempParent = this; }
        switch (type) {
        case 2:
            tempChild = new Derived2(tempParent, childName, condition);
            break;
        case 3:
            tempChild = new Derived3(tempParent, childName, condition);
            break;
        }
    }
}

void Application::Request() {
    while (true) {
        string request;
        cin >> request;
        if (request == "//") return;
        if (request.size() > 2 && request[0] == '/' && request[1] == '/') {
            request = request.substr(2, request.size() - 2);
            Base* f = FindObj(request);
            if (f)
                cout << "\n//" << request << " Object name: " << request;
            else
                cout << "\n//" << request << " Object not found";
        }
        else {
            ChopString(request);
            Base* f = FindObj(request);
            if (f)
                cout << "\n/" << GetName() << request << " Object name: " << f->GetName();
            else
                cout << "\n/" << GetName() << request << " Object not found";
        }
    }
}

void Application::ChopString(string& s) {
    s.erase(s.begin());
    while (s.size() > 0 && s[0] != '/')
        s.erase(s.begin());
}

void Application::SetConnections() {
    int num;
    string from, to;
    while (true) {
        cin >> num;
        if (num == 0) return;
        cin >> from >> to;
        tempParent = FindObj(from);
        tempChild = FindObj(to);
        tempParent->CreateConnection(tempChild, num);
        cout << '\n' << num << " " << from << " " << to;
    }
}

void Application::DoConnections() {
    string from, message;
    while (true) {
        cin >> from;
        if (from == "endsignals") return;
        tempParent = FindObj(from);
        cin >> message;
        switch (tempParent->GetType()) {
        case 1:
            tempParent->GetSignal((SIGNAL)(&Application::Signal), message);
            break;
        case 2:
            tempParent->GetSignal((SIGNAL)(&Derived2::Signal), message);
            break;
        case 3:
            tempParent->GetSignal((SIGNAL)(&Derived3::Signal), message);
            break;
        }
    }
}

int Application::Execute() {
    cout << "Object tree\n";
    cout << GetName();
    PrintTree();
    cout << "\nSet connects";
    SetConnections();
    cout << "\nEmit Signals";
    DoConnections();
    return 0;
}
