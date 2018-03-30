#include <iostream>
#include "p2.h"

int main()

{

    SparseMatrix m1(6,5), m2(6,5), m3(5,6);

    cout << m1; // should be all zeroes

    m1.set(0, 0, 15);    m1.set(0, 3, 22);

    m1.set(0, 4, -15);    m1.set(1, 1, 11);

    m1.set(1, 2, 3);    m1.set(2, 3, -6);

    m1.set(4, 0, 91);    m1.set(5, 3, 28);

    m1.set(6, 7, 8); // error

    cout << m1;

    cout << m1.get(1, 2) << endl; // 3

    cout << m1.get(4, 4) << endl; // 0

    cout << m1.get(7, 8) << endl; // error

    m2.set(2, 1, 13);    m2.set(0, 3, 10);

    SparseMatrix m4 = m1.Add(m2);

    cout << m1 << m2 << m4;

    m4.Transpose(); // now the size is 5x6

    m3 = m1.Multiply(m4); // now the size is 6x6

    cout << m3;

    m3 = m1.Multiply(m2); // error

    system("pause");

    return 0;

}


