#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define KEY_ERROR       (-1)
#define FILE_PATH_ERROR (-2)

#define OPERATION_SIMPLE    0
#define OPERATION_COMPLEX   1

using namespace std;

struct Operation_t {
    int type;
    char simple_op;
    string payload;
};

char check_key(char *arg) {
    if (!arg || arg[0] != '-') return 0;

    return arg[1];
}

int main(int argc, char **argv)
{
    vector<Operation_t> operations;
    string type1 = "", type2 = "", value1 = "", value2 = "";

    if (argc < 2) {
        cout << "No arguments found, using standard input (-f for file input)\n";
        cout << "Input type1:\n>";
        getline(cin, type1);
        cout << "Input type2:\n>";
        getline(cin, type2);

        cout << "Input value1:\n>";
        getline(cin, value1);
        cout << "Input value2:\n>";
        getline(cin, value2);
    } else {
        switch (check_key(argv[1])) {
            case 'f': {
                Operation_t op_str;
                int type;
                char c_type, op;
                string comment, expression;

                ifstream fin(argv[2]);

                if (!fin) {
                    cout << "Invalid input file path";
                    return FILE_PATH_ERROR;
                }

                getline(fin, type1);
                getline(fin, type2);

                getline(fin, value1);
                getline(fin, value2);

                while (fin >> c_type) {
                    if (c_type == 's') {
                        fin >> op_str.payload >> op_str.simple_op;
                        op_str.type = OPERATION_SIMPLE;
                    } else {
                        getline(fin, op_str.payload);
                        op_str.type = OPERATION_COMPLEX;
                        op_str.simple_op = ' ';
                    }

                    operations.push_back(op_str);
                }

                break;
            }
            case 'h': {
                cout << "-h: show help.\n-f: use file for input.\n\ninput file format:\ntype1\ntype2\nvalue1\nvalue2\nexpression1\nexpression2\n...\n\nexpression:\n\t- simple (s comment +)\n\t-complex: (c (arg1 + arg2) / arg1)\n";
                break;
            }
            default: {
                cout << "Invalid key. Use -h for help menu.\n";
                return KEY_ERROR;
            }
        }
    }

    ofstream fout("./output.cpp");

    fout << "#include <iostream>\n\nusing namespace std;\n\nvoid test_func(" << type1 << " arg1, " << type2 << " arg2) {\n";

    if (operations.empty()) {
        fout << "\n\tcout << \"Sum: \" << arg1 + arg2;\n\tcout << \"Sub: \" << arg1 - arg2;\n\tcout << \"Mul: \" << arg1 * arg2;\n}\n";
    } else {
        for (Operation_t op : operations) {
            switch (op.type) {
                case OPERATION_SIMPLE: {
                    fout << "\tcout << \"" << op.payload << "\" << arg1 " << op.simple_op << " arg2 << \"\\n\";\n";
                    break;
                }
                case OPERATION_COMPLEX: {
                    fout << "\tcout << \"Result of" << op.payload << ":\" << " << op.payload << " << \"\\n\";\n";
                    break;
                }
            }
        }

        fout << "}\n";
    }

    fout << "\nint main() {\n\t" << type1 << " arg1 = " << value1 << ", " << type2 << " arg2 = " << value2 << ";\n\ttest_func(arg1, arg2);\n\treturn 0;\n}\n";

    return 0;
}
