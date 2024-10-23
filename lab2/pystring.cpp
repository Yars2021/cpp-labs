#include "pystring.hpp"
#include <stdexcept>

PYString::PYString() {
    this->size = 0;
    this->buffer = nullptr;
}

PYString::PYString(const char *str) {
    for (this->size = 0; str[this->size] != 0; this->size++);

    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < this->size; i++) {
        this->buffer[i] = str[i];
    }
}

PYString::PYString(const PYString &str) {
    this->size = str.size;
    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < str.size; i++) {
        this->buffer[i] = str.buffer[i];
    }
}

PYString::PYString(const std::string &str) {
    this->size = str.size();
    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < str.size(); i++) {
        this->buffer[i] = str[i];
    }
}

PYString::PYString(PYString &&str) {
    this->size = str.size;
    std::swap(this->buffer, str.buffer);
}

PYString::~PYString() {
    this->size = 0;
    delete(this->buffer);
}

unsigned int PYString::length() {
    return this->size;
}

const char & PYString::operator[](int index) {
    if (index >= this->size || index <= -this->size) {
        throw std::invalid_argument("PYString index out of bounds");
    }
    if (index >= 0) {
        return this->buffer[index];
    } else {
        return this->buffer[this->size + index];
    }
}
