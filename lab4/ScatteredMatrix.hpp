//
// Created by yars on 18.12.24.
//

#ifndef CPP_LABS_SCATTEREDMATRIX_HPP
#define CPP_LABS_SCATTEREDMATRIX_HPP


#include <iostream>
#include <unordered_map>


template <typename T> class ScatteredMatrix {
    private:
        unsigned int width;
        unsigned int height;
        T default_value;
        std::unordered_map<std::pair<unsigned int, unsigned int>, T> values;
    public:
        ScatteredMatrix(unsigned int width, unsigned int height, T &default_value);
        ScatteredMatrix(unsigned int width, unsigned int height, T &default_value, T *matrix);
        ScatteredMatrix(ScatteredMatrix<T> &matrix);
        ~ScatteredMatrix();
        unsigned int get_width();
        unsigned int get_height();
        T get_default_value();
        T get(unsigned int width, unsigned int height);
        void set(unsigned int width, unsigned int height, T &value);
        void transpose();
        void map(T map_func(T &value));
        ScatteredMatrix<T> & operator=(const ScatteredMatrix<T> &matrix);
        ScatteredMatrix<T> & operator+(const ScatteredMatrix<T> &matrix);
        ScatteredMatrix<T> & operator-(const ScatteredMatrix<T> &matrix);
        ScatteredMatrix<T> & operator*(const ScatteredMatrix<T> &matrix);
        bool operator==(const ScatteredMatrix<T> &matrix);
        bool operator!=(const ScatteredMatrix<T> &matrix);
        void print(std::ostream &out_stream);
};

template <typename T> ScatteredMatrix<T>::ScatteredMatrix(unsigned int width,  unsigned int height, T &default_value) {
    this->width = width;
    this->height = height;
    this->default_value = default_value;
}

template <typename T> ScatteredMatrix<T>::ScatteredMatrix(unsigned int width, unsigned int height, T &default_value, T *matrix) {
    this->width = width;
    this->height = height;
    this->default_value = default_value;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            this->values[{i, j}] = matrix[i][j];
        }
    }
}

template <typename T> ScatteredMatrix<T>::ScatteredMatrix(ScatteredMatrix<T> &matrix) {
    this->width = matrix.get_width();
    this->height = matrix.get_height();
    this->default_value = matrix.get_default_value();

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->values[{i, j}] = matrix.get(i, j);
        }
    }
}

template <typename T> ScatteredMatrix<T>::~ScatteredMatrix() {
    this->width = 0;
    this->height = 0;
}

template <typename T> unsigned int ScatteredMatrix<T>::get_width() {
    return this->width;
}

template <typename T> unsigned int ScatteredMatrix<T>::get_height() {
    return this->height;
}

template <typename T> T ScatteredMatrix<T>::get_default_value() {
    return this->default_value;
}

template <typename T> T ScatteredMatrix<T>::get(unsigned int width, unsigned int height) {
    if (width >= this->width || height >= this->height) return this->default_value;
    if (this->values.find({width, height}) == this->values.end()) return this->default_value;
    return this->values[{width, height}];
}

template <typename T> void ScatteredMatrix<T>::set(unsigned int width, unsigned int height, T &value) {
    if (width >= this->width || height >= this->height) return;
    this->values[{width, height}] = value;
}

template <typename T> void ScatteredMatrix<T>::transpose() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            
        }
    }
}

template <typename T> void ScatteredMatrix<T>::map(T map_func(T &value)) {

}

template <typename T> ScatteredMatrix<T> & ScatteredMatrix<T>::operator=(const ScatteredMatrix<T> &matrix) {

}

template <typename T> ScatteredMatrix<T> & ScatteredMatrix<T>::operator+(const ScatteredMatrix<T> &matrix) {

}

template <typename T> ScatteredMatrix<T> & ScatteredMatrix<T>::operator-(const ScatteredMatrix<T> &matrix) {

}

template <typename T> ScatteredMatrix<T> & ScatteredMatrix<T>::operator*(const ScatteredMatrix<T> &matrix) {

}

template <typename T> bool ScatteredMatrix<T>::operator==(const ScatteredMatrix<T> &matrix) {
    if (this->width != matrix.get_width() || this->height != matrix.get_height() || this->default_value != matrix.get_default_value()) return false;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (this->get(i, j) != matrix.get(i, j)) return false;
        }
    }

    return true;
}

template <typename T> bool ScatteredMatrix<T>::operator!=(const ScatteredMatrix<T> &matrix) {
    return false == (*this == matrix);
}

template <typename T> void ScatteredMatrix<T>::print(std::ostream &out_stream) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            out_stream << this->get(i, j) << ' ';
        }
        out_stream << '\n';
    }
    out_stream << '\n';
}

#endif //CPP_LABS_SCATTEREDMATRIX_HPP
