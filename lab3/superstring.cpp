#include "superstring.hpp"
#include <ctime>
#include <cstdlib>
#include <stdexcept>


SuperString::SuperString() {
    this->size = 0;
    this->buffer = nullptr;
}

SuperString::SuperString(int min_len, int max_len) {
    this->size = rand() % (max_len - min_len) + min_len;
    this->buffer = new char[this->size];

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = (rand() % ('Z' - 'A') + 'A');
    }
}

SuperString::SuperString(const char *str) {
    for (this->size = 0; str[this->size] != 0; this->size++);

    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < this->size; i++) {
        this->buffer[i] = str[i];
    }
}

SuperString::SuperString(const SuperString &str) {
    this->size = str.size;
    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < str.size; i++) {
        this->buffer[i] = str.buffer[i];
    }
}

SuperString::SuperString(const std::string &str) {
    this->size = str.size();
    this->buffer = new char[this->size];

    for (unsigned int i = 0; i < str.size(); i++) {
        this->buffer[i] = str[i];
    }
}

SuperString::SuperString(SuperString &&str) {
    this->size = str.size;
    std::swap(this->buffer, str.buffer);
}

SuperString::~SuperString() {
    this->size = 0;
    delete(this->buffer);
}

unsigned int SuperString::length() {
    return this->size;
}

SuperString & SuperString::operator=(const SuperString &operand) {
    if (this->size > 0) delete(this->buffer);

    this->size = operand.size;
    this->buffer = new char[this->size];

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = operand.buffer[i];
    }

    return *this;
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

void SuperString::print(std::ostream &out_stream) {
    for (int i = 0; i < this->size; i++) {
        out_stream << this->buffer[i];
    }

    out_stream << '\n';
}
