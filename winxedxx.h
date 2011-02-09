#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// Revision 9-feb-2011

#include <iostream>
#include <string>

class WinxedxxObject {
public:
    virtual int get_integer()
    {
        throw "get_integer not implemented";
    }
};

class WinxedxxNull : public WinxedxxObject
{
public:
    int get_integer() { return 0; };
};

class WinxedxxInteger : public WinxedxxObject
{
public:
    WinxedxxInteger(int value)
    {
        i = value;
    }
    int get_integer() { return i; };
private:
    int i;
};

//*************************************************************

class WinxedxxObjectPtr
{
public:
    WinxedxxObjectPtr() : object(new WinxedxxNull())
    { }
    operator int() const { return object->get_integer(); };
    WinxedxxObjectPtr & operator = (int i)
    {
        object = new WinxedxxInteger(i);
        return *this;
    }
private:
    WinxedxxObject *object;
};

static WinxedxxObjectPtr winxedxxnull = WinxedxxObjectPtr();

int wxx_print(int i) { std::cout << i; return 0; }
int wxx_print(const char *s) { std::cout << s; return 0; }
int wxx_print(const std::string &s) { std::cout << s; return 0; }

#endif

// End of winxedxx.h
