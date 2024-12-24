#ifndef CPP_LABS_SCATTEREDMATRIX_HPP
#define CPP_LABS_SCATTEREDMATRIX_HPP


#include <iostream>
#include <unordered_map>


struct IndexHash {
    template <class T1, class T2> std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>{}(pair.first) ^ (std::hash<T2>{}(pair.second) << 1);
    }
};


template <typename T> class ScatteredMatrix {
    private:
        unsigned int rows, cols;
    public:
        std::unordered_map<std::pair<unsigned int, unsigned int>, T, IndexHash> values;

        ScatteredMatrix(unsigned int rows, unsigned int cols) {
            this->rows = rows;
            this->cols = cols;
        }

        unsigned int get_rows() {
            return this->rows;
        }

        unsigned int get_cols() {
            return this->cols;
        }

        void set(unsigned int row, unsigned int col, T value) {
            if (value != 0) {
                this->values[std::make_pair(row, col)] = value;
            } else {
                this->values.erase(std::make_pair(row, col));
            }
        }

        T get(unsigned int row, unsigned int col) {
            auto it = this->values.find({row, col});
            return (it == this->values.end()) ? 0 : it->second;
        }

        ScatteredMatrix<T> operator+(ScatteredMatrix<T> &other) {
            ScatteredMatrix<T> sum(this->rows, this->cols);

            for (auto &pos : this->values) {
                sum.set(pos.first.first, pos.first.second, pos.second + other.get(pos.first.first, pos.first.second));
            }

            return sum;
        }

        ScatteredMatrix<T> operator*(ScatteredMatrix<T>& other) {
            ScatteredMatrix<T> prod(this->get_rows(), other.get_cols());

            for (unsigned int i = 0; i < this->rows; i++) {
                for (unsigned int j = 0; j < other.get_cols(); j++) {
                    T res = 0;

                    for (unsigned int k = 0; k < other.get_rows(); k++) {
                        res += this->get(i, k) * other.get(k, j);
                    }

                    prod.set(i, j, res);
                }
            }

            return prod;
        }

        ScatteredMatrix<T> transpose() {
            ScatteredMatrix<T> transposed(this->cols, this->rows);

            for (auto &pos : this->values) {
                transposed.set(pos.first.second, pos.first.first, pos.second);
            }

            return transposed;
        }

        ScatteredMatrix<T> map(int a) {
            ScatteredMatrix<T> mapped(this->rows, this->cols);

            for (auto &pos : this->values) {
                mapped.set(pos.first.first, pos.first.second, func(pos.second));
            }

            return mapped;
        }

        void print(std::ostream& stream) {
            for (unsigned int i = 0; i < this->get_rows(); i++) {
                for (unsigned int j = 0; j < this->get_cols(); j++) {
                    stream << this->get(i, j) << " ";
                }
                stream << std::endl;
            }
        }
};

#endif //CPP_LABS_SCATTEREDMATRIX_HPP
