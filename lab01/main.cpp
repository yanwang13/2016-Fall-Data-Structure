 #include <iostream>
#include "SparseMatrix.h"

int main()

{

    SparseMatrix m1(6,6), m2(6,6), m3(5,6);

    m1.list_full(); // should be all zeroes

    m1.list_sparse(); // no term listed

    m1.set(0, 0, 15);    m1.set(0, 3, 22);

    m1.set(0, 5, -15);    m1.set(1, 1, 11);

    m1.set(1, 2, 3);    m1.set(2, 23, -6);

    m1.set(4, 0, 91);    m1.set(5, 25, 28);

    m1.set(6, 7, 8); // error

    m1.list_full();

    m1.list_sparse();

    cout << m1.get(1, 2) << endl; // 3

    cout << m1.get(4, 4) << endl; // 0

    cout << m1.get(7, 8) << endl; // error

    m2.set(1, 2, 13);    m2.set(0, 3, 10);

    SparseMatrix m4 = m1.Add(m2);

    m4.list_full();

    m4.list_sparse(); // there are 9 terms

    m4.set(0, 3, 0);    m2.set(4, 0, 0);

    m4.list_sparse(); // there are 7 terms

    m2 = m1.Add(m3); // error (size mismatch)

    system("pause");

    return 0;

}
