#include <iostream>
#include "your header file"

using namespace std;

 

int main()

{

  int x1[] = {0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0};

  MyGraph G1(4, x1);

  if (G1.OneStroke() == 0) cout << "G1 can't do one-stroke" << endl;

  int x2[] = {0,1,1,1,1, 1,0,1,0,0, 1,1,0,0,0, 1,0,0,0,1, 1,0,0,1,0};

  MyGraph G2(5, x2);

  if (G2.OneStroke() == 0) cout << "G2 can't do one-stroke" << endl;

  int x3[] = {0,0,1,1,0,0,1, 0,0,0,0,1,1,1, 1,0,0,1,0,0,0, 1,0,1,0,1,0,0,

                    0,1,0,1,0,1,0, 0,1,0,0,1,0,0, 1,1,0,0,0,0,0};

  MyGraph G3(7, x3);

  if (G3.OneStroke() == 0) cout << "G3 can't do one-stroke" << endl;

  int x4[] = {0,0,1,1,0,0, 0,0,0,0,1,1, 1,0,0,1,0,0, 1,0,1,0,1,0,

                    0,1,0,1,0,1, 0,1,0,0,1,0};

  MyGraph G4(6, x4);

  if (G4.OneStroke() == 0) cout << "G4 can't do one-stroke" << endl;

  system("pause");

  return 0;

}