#include <iostream>

#include "p3.h"

using namespace std;

 

int main()

{

  GeneralTree tr("15 ( 3 ( 18 16 11 ( 4 ) ) 22 7 100 ( 6 200 99 ) )"); // tokens seperated by blanks

  tr.preorder_rec(); // 15 3 18 16 11 4 22 7 100 6 200 99

  tr.preorder_nonrec(); // 15 3 18 16 11 4 22 7 100 6 200 99

  tr.postorder_rec(); // 18 16 4 11 3 22 7 6 200 99 100 15

  tr.postorder_nonrec(); // 18 16 4 11 3 22 7 6 200 99 100 15

  tr.levelorder(); // 15 3 22 7 100 18 16 11 6 200 99 4

  system("pause");

  return 0;

}
