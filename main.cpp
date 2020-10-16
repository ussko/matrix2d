#include <iostream>

#include "matrix2d.h"

using std::cout;
int main()
{
    cout << "Matrix2d class demo\n\n";

    Matrix2d<int> m1{2, 4};
    Matrix2d<int> m2{4, 2};

    m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3; m1[0][3] = 4;
    m1[1][0] = 5; m1[1][1] = 6; m1[1][2] = 7; m1[1][3] = 8;
    m2[0][0] = 100; m2[0][1] = 200;
    m2[1][0] = 300; m2[1][1] = 400;
    m2[2][0] = 500; m2[2][1] = 600;
    m2[3][0] = 700; m2[3][1] = 800;

    cout << "To create a Matrix2d object specify row and column dimensions:\n";
    cout << ">Matrix2d<int> m1{2, 4}\n";
    cout << m1;
    cout << ">Matrix2d<int> m2{2, 4}\n";
    cout << m2 << '\n';

    cout << "To access matrix element specify row and column:\n";
    cout << ">m1[0][2]\n";
    cout << m1[0][2] << '\n';
    cout << ">m2.at(2, 1)\n";
    cout << m2.at(2, 1) << '\n';

    cout << ">m2[4][0]\n";
    try
    {
        m2[4][0] = 1;
    }
    catch (std::exception &e)
    {
        cout << e.what() << '\n';
    }
    cout << ">m1.at(1, 8)\n";
    try
    {
        m1.at(1, 8) = 1;
    }
    catch (std::exception &e)
    {
        cout << e.what() << "\n\n";
    }

    cout << "Matrix2d supports range-for:\n";
    cout << ">for (const auto &element : m2)\n";
    cout << ">    element\n";
    for (const auto &element : m2)
        cout << element << ' ';
    cout << "\n\n";

    cout << "Matrix2d supports addition:\n";
    cout << ">m1 + m2\n";
    cout << m1 + m2 << '\n';

    cout << "Matrix2d supports horizontal concatenation:\n";
    cout << ">m1 | m2\n";
    cout << (m1 | m2);
    cout << ">m2 | m1\n";
    cout << (m2 | m1) << '\n';

    Matrix2d<std::string> ms1{2, 2};
    Matrix2d<std::string> ms2{2, 1};
    ms1[0][0] = "one"; ms1[0][1] = "two";
    ms1[1][0] = "three"; ms1[1][1] = "four";
    ms2[0][0] = "and_";
    ms2[1][0] = "and_";

    cout << "Matrix2d can store elements of various types:\n";
    cout << ">Matrix2d<std::string> ms1{2, 2}\n";
    cout << ms1;
    cout << ">Matrix2d<std::string> ms2{2, 1};\n";
    cout << ms2;
    cout << ">ms2 + ms1\n";
    cout << ms2 + ms1 << '\n';

    return 0;
}
