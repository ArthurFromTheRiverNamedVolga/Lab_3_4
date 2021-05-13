#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>

using namespace std;

class Base {
public:
    typedef void (Base::* SIGNAL)(string&);
    typedef void (Base::* SIGNAL_KEEPER)(string);

private:
    struct Connection {
        string text;
        Base* to;
        SIGNAL signal;
        SIGNAL_KEEPER signal_keeper;
        int num;
    };

    string name;
    Base* parent;
    vector<Base*> children;
    vector<Base*>::iterator childrenIterator;
    int condition = 0;
    vector<Connection> connections;

protected:
    int type = 1;
public:

    Base(Base* parent, string name = "base");
    Base(Base* parent, string name, int condition);

    int GetType();

    void SetName(string name);
    string GetName();

    void SetParent(Base* parent);
    Base* GetParent();

    void SetCondition(int condition);
    int GetCondition();

    void PrintNames();
    void PrintReady();
    void PrintTree(string offset = "");

    Base* FindObj(string name);
    Base* FindObjRoot(string name);
    Base* FindRoot();
    Base* FindObjRouteRoot(string route);
    void CreateConnection(Base* to, int num);
    void DeleteConnection(Base* to, SIGNAL signal, SIGNAL_KEEPER signal_keeper);
    void GetSignal(SIGNAL signal, string& s);

    void Signal(string&);
    void SignalKeeper(string);
};

#endif