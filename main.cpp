#include "spreadSheet.h"
#include <iostream>

int main() {
   SpreadSheet st1(1,1);
  st1.addRow(1);
  st1.addColumn(1);
  st1.getCell(0,0).setStringValue("hell");
  st1.getCell(0,1).setStringValue("hell2");
  st1.getCell(1,0).setStringValue("hell3");
  st1.getCell(1,1).setStringValue("hell4");
  st1.printCells();
  return 0;
}