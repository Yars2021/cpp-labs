#include <chrono>
#include <iostream>

#include <vector>
#include "ScatteredMatrix.hpp"

using namespace std;

int get_current_ms() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

int main(int argc, char **argv) {
    cout << "VECTORS\n\nCreation:" << endl;

    int prev_time = get_current_ms(), current_time = 0;

    cout << "1. Vectors of size 100000: ";
    current_time = get_current_ms();
    vector<int> test_vec_1(100000), test_vec_2(100000);

    for (int i = 0; i < 10000; i++) {
        test_vec_1[i * 10] = 3 * i;
        test_vec_2[i * 10] = -2 * i;
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "2. Custom Vectors of size 100000: ";
    current_time = get_current_ms();
    ScatteredMatrix<int> sc_test_vec_1(1, 1000), sc_test_vec_2(1, 1000);

    for (int i = 0; i < 10000; i++) {
        sc_test_vec_1.set(0, i * 10, 3 * i);
        sc_test_vec_2.set(0, i * 10, -2 * i);
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "\nAddition:" << endl;

    cout << "1. Vectors of size 100000: ";
    current_time = get_current_ms();

    for (int i = 0; i < 1000; i++) {
        test_vec_1[i] += test_vec_2[i];
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "2. Custom Vectors of size 100000: ";
    current_time = get_current_ms();

    ScatteredMatrix<int> sc_test_vec_1_new = sc_test_vec_1 + sc_test_vec_2;

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "\nMultiplication:" << endl;

    cout << "1. Vectors of size 100000: ";
    current_time = get_current_ms();

    int test_result = 0;

    for (int i = 0; i < 1000; i++) {
        test_result += test_vec_1[i] * test_vec_2[i];
    }

    cout << "Scalar mul = " << test_result << endl;

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "2. Custom Vectors of size 100000: ";
    current_time = get_current_ms();

    ScatteredMatrix<int> sc_test_vec_2_t = sc_test_vec_2.transpose(), sc_test_mul_result = sc_test_vec_1_new * sc_test_vec_2_t;
    cout << "Scalar mul = ";
    sc_test_mul_result.print(cout);

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;


    cout << "\n\nMATRICES\n\nCreation:" << endl;

    cout << "1. Vectors of sizes 100 x 1000 and 1000 x 100: ";
    current_time = get_current_ms();
    vector<vector<int>> test_m_1, test_m_2;

    for (int i = 0; i < 100; i++) {
        vector<int> buffer(1000);

        if (i % 10 == 0) {
            for (int j = 0; j < 1000; j++) {
                buffer.push_back(i ^ j);
            }
        }

        test_m_1.push_back(buffer);
    }

    for (int i = 0; i < 1000; i++) {
        vector<int> buffer(100);

        if (i % 10 == 0) {
            for (int j = 0; j < 100; j++) {
                buffer.push_back(i * j);
            }
        }

        test_m_2.push_back(buffer);
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "2. Custom Matrices of sizes 100 x 1000 and 1000 x 100: ";
    current_time = get_current_ms();
    ScatteredMatrix<int> sc_test_m_1(100, 1000), sc_test_m_2(1000, 100);

    for (int i = 0; i < 100; i++) {
        if (i % 10 == 0) {
            for (int j = 0; j < 1000; j++) {
                sc_test_m_1.set(i, j, i ^ j);
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        if (i % 10 == 0) {
            for (int j = 0; j < 100; j++) {
                sc_test_m_2.set(i, j, i * j);
            }
        }
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "\nAddition of A and B.T:" << endl;

    cout << "1. Vectors of sizes 100 x 1000 and 1000 x 100: ";
    current_time = get_current_ms();

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 1000; j++) {
            test_m_1[i][j] += test_m_2[j][i];
        }
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "2. Custom Matrices of sizes 100 x 1000 and 1000 x 100: ";
    current_time = get_current_ms();

    ScatteredMatrix<int> sc_test_m_2_T = sc_test_m_2.transpose(), sc_test_m_1_new = sc_test_m_1 + sc_test_m_2_T;

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "\nMultiplication of A and B:" << endl;

    cout << "1. Vectors of sizes 100 x 1000 and 1000 x 100: ";
    current_time = get_current_ms();

    vector<vector<int>> mul_res;

    for (int i = 0; i < 100; i++) {
        vector<int> buffer(100);
        mul_res.push_back(buffer);
    }

    for (unsigned int i = 0; i < 100; i++) {
        for (unsigned int j = 0; j < 100; j++) {
            int res = 0;

            for (unsigned int k = 0; k < 1000; k++) {
                res += test_m_1[i][k] * test_m_2[k][j];
            }

            mul_res[i][j] = res;
        }
    }

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    cout << "2. Custom Matrices of sizes 100 x 1000 and 1000 x 100: ";
    current_time = get_current_ms();

    ScatteredMatrix<int> sc_mul_res = sc_test_m_1_new * sc_test_m_2;

    cout << current_time - prev_time << "ms" << endl;
    prev_time = current_time;

    return 0;
}