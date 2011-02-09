#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// Revision 9-feb-2011

#include <iostream>
#include <string>
#include <stdexcept>

class WinxedxxObject {
public:
    virtual int get_integer()
    {
        throw std::runtime_error("get_integer not implemented");
    }
    virtual std::string get_string()
    {
        throw std::runtime_error("get_string not implemented");
    };
    virtual void print() {}
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
    void print() { std::cout << i; }
private:
    int i;
};

class WinxedxxString : public WinxedxxObject
{
public:
    WinxedxxString(std::string value)
    {
        str = value;
    }
    std::string get_string() { return str; };
    void print() { std::cout << str; }
private:
    std::string str;
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
    WinxedxxObjectPtr & operator = (const std::string &s)
    {
        object = new WinxedxxString(s);
        return *this;
    }
    void print()
    {
        object->print();
    }
private:
    WinxedxxObject *object;
};

static WinxedxxObjectPtr winxedxxnull = WinxedxxObjectPtr();

int wxx_print(int i) { std::cout << i; return 0; }
int wxx_print(const char *s) { std::cout << s; return 0; }
int wxx_print(const std::string &s) { std::cout << s; return 0; }
int wxx_print(double n) { std::cout << n; return 0; }
int wxx_print(WinxedxxObjectPtr &obj) { obj.print(); return 0; }

#endif

// End of winxedxx.h
