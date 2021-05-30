#include <iostream>
#include "src/lib/trojanmap.h"

int main() {
  TrojanMap x;
  x.CreateGraphFromCSVFile();
  //x.PrintMenu();
  while(x.MyMenu());
  return 0;
}