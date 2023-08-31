#ifndef SPREAD_SHEET
#define SPREAD_SHEET

#include "spreadSheetCell.h"
#include <vector>

class SpreadSheet {
private:
  size_t m_row{0};
  size_t m_column{0};
  SpreadSheetCell*** m_cells {nullptr};
    
public:
  SpreadSheet() = default;
  SpreadSheet (size_t height, size_t width);
  ~SpreadSheet();
  void removeRow(size_t rowNumber);
  void removeColumn(size_t columnNumber);
  void addRow(size_t newRows);
  void addColumn(size_t newRows);
  SpreadSheetCell& getCell(size_t row, size_t column);
  void setCell(size_t row, size_t column, const std::string& value);
  void printCells();
};

#endif
