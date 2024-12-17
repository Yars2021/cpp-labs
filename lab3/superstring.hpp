#ifndef SUPERSTRING_HPP
#define SUPERSTRING_HPP

#include <iostream>
#include <string>

class SuperString {
    private:
        unsigned int size;
        char *buffer = nullptr;
    public:
        SuperString();
        SuperString(int, int);
        SuperString(const char *);
        SuperString(const SuperString &);
        SuperString(const std::string &);
        SuperString(SuperString &&);
        ~SuperString();
        unsigned int length();
        SuperString & operator=(const SuperString &);
        const char & operator[](int);
        bool operator==(const SuperString &);
        bool operator!=(const SuperString &);
        bool operator>(const SuperString &);
        bool operator<(const SuperString &);
        bool operator>=(const SuperString &);
        bool operator<=(const SuperString &);
        void operator+=(const SuperString &);
        void print(std::ostream &);
};

#endif
