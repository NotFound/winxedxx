#ifndef INCLUDE_WINXEDXX_H
#define INCLUDE_WINXEDXX_H

// winxedxx.h
// (C) 2011 Julián Albo "NotFound"

#include <iostream>
#include <string>
#include <stdexcept>

namespace WinxedXX
{

class WxxObject {
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

class WxxNull : public WxxObject
{
public:
    int get_integer() { return 0; };
};

class WxxInteger : public WxxObject
{
public:
    WxxInteger(int value)
    {
        i = value;
    }
    int get_integer() { return i; };
    void print() { std::cout << i; }
private:
    int i;
};

class WxxString : public WxxObject
{
public:
    WxxString(std::string value)
    {
        str = value;
    }
    std::string get_string() { return str; };
    void print() { std::cout << str; }
private:
    std::string str;
};

//*************************************************************

class WxxObjectPtr
{
public:
    WxxObjectPtr() : object(new WxxNull())
    { }
    operator int() const { return object->get_integer(); };
    WxxObjectPtr & operator = (int i)
    {
        object = new WxxInteger(i);
        return *this;
    }
    WxxObjectPtr & operator = (const std::string &s)
    {
        object = new WxxString(s);
        return *this;
    }
    std::string get_string()
    {
        return object->get_string();
    }
    void print()
    {
        object->print();
    }
private:
    WxxObject *object;
};

static WxxObjectPtr winxedxxnull = WxxObjectPtr();

int wxx_print(int i) { std::cout << i; return 0; }
int wxx_print(const char *s) { std::cout << s; return 0; }
int wxx_print(const std::string &s) { std::cout << s; return 0; }
int wxx_print(double n) { std::cout << n; return 0; }
int wxx_print(WxxObjectPtr &obj) { obj.print(); return 0; }

} // namespace WinxedXX

#endif

// End of winxedxx.h
