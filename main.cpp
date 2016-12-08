#include <iostream>
#include <cstdlib>
#include "board.h"

int main(int argc, char** argv)
{
  if(argc < 4)
  {
    std::cout << "Error, needs three arguments ";
    std::cout << "( width, height, number of mines )" << std::endl;
    return -1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  int minenum = atoi(argv[3]);

  Board b(x,y,minenum);
  b.start();
}
