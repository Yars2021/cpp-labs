#ifndef PYSTRING_HPP
#define PYSTRING_HPP

#include <string>

class PYString {
    private:
        unsigned int size;
        char *buffer = nullptr;
    public:
        PYString();
        PYString(const char *);
        PYString(const PYString &);
        PYString(const std::string &);
        PYString(PYString &&);
        ~PYString();
        unsigned int length();
        const char & operator[](int);
};

#endif
