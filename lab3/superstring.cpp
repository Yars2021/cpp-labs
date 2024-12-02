#include "superstring.hpp"
#include <stdexcept>

SuperString::SuperString() {
    this->size = 0;
    this->buffer = nullptr;

    std::cout << "SuperString()" << std::endl;
}

SuperString::SuperString(const char *str) {
    for (this->size = 0; str[this->size] != 0; this->size++);

    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < this->size; i++) {
        this->buffer[i] = str[i];
    }

    std::cout << "SuperString(const char *str)" << std::endl;
}

SuperString::SuperString(const SuperString &str) {
    this->size = str.size;
    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < str.size; i++) {
        this->buffer[i] = str.buffer[i];
    }

    std::cout << "SuperString(const SuperString &str)" << std::endl;
}

SuperString::SuperString(const std::string &str) {
    this->size = str.size();
    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < str.size(); i++) {
        this->buffer[i] = str[i];
    }

    std::cout << "SuperString(const std::string &str)" << std::endl;
}

SuperString::SuperString(SuperString &&str) {
    this->size = str.size;
    std::swap(this->buffer, str.buffer);

    std::cout << "SuperString(SuperString &&str)" << std::endl;
}

SuperString::~SuperString() {
    this->size = 0;
    delete(this->buffer);

    std::cout << "~SuperString()" << std::endl;
}

unsigned int SuperString::length() {
    return this->size;
}

const char & SuperString::operator[](int index) {
    if ((index > 0 && index >= this->size) || (index < 0 && -index >= this->size)) {
        throw std::invalid_argument("SuperString index out of bounds");
    }
    if (index >= 0) {
        return this->buffer[index];
    } else {
        return this->buffer[this->size + index];
    }
}

bool SuperString::operator==(const SuperString &other) {
    if (this->size != other.size) return false;

    for (unsigned int i = 0; i < this->size; i++) {
        if (this->buffer[i] != other.buffer[i]) return false;
    }

    return true;
}

bool SuperString::operator!=(const SuperString &other) {
    return !(*this == other);
}

bool SuperString::operator>(const SuperString &other) {
    if (*this == other) return false;

    unsigned int i = 0;

    for (; i < this->size && i < other.size && this->buffer[i] == other.buffer[i]; i++);

    if (this->size > other.size) return true;
    if (this->size < other.size) return false;

    return this->buffer[i] > other.buffer[i];
}

bool SuperString::operator<(const SuperString &other) {
    return (*this != other) && !(*this > other);
}

bool SuperString::operator>=(const SuperString &other) {
    return !(*this < other);
}

bool SuperString::operator<=(const SuperString &other) {
    return !(*this > other);
}

void SuperString::operator+=(const SuperString &other) {
    char *buffer = new char[this->size + other.size];

    for (unsigned int i = 0; i < this->size; i++) {
        buffer[i] = this->buffer[i];
    }

    for (unsigned int i = 0; i < other.size; i++) {
        buffer[this->size + i] = other.buffer[i];
    }

    this->size += other.size;
    delete this->buffer;
    this->buffer = buffer;
}
