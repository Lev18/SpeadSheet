#include <string>
#include <iostream>
#include <sstream>

class SpreadSheetCell {
public:
 SpreadSheetCell();
 SpreadSheetCell(const std::string& val);
 void setStringValue(const std::string& val);
 int getIntValue() const;
 double getDoubleValue() const;
 std::string getStringValue() const;
 
private:
  std::string m_value;
};

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

SpreadSheetCell::SpreadSheetCell() : m_value("  ") {
}

void SpreadSheetCell::setStringValue(const std::string& val) {
  m_value = val;
}

int SpreadSheetCell::getIntValue() const {
  std::stringstream ss;
  ss << m_value;
  int value ;
  ss >> value;
  return value;
}

std::string SpreadSheetCell::getStringValue() const {
  return m_value;
}

double SpreadSheetCell::getDoubleValue() const {
  std::stringstream ss;
  ss << m_value;
  double value ;
  ss >> value;
  return value;
}


SpreadSheet::SpreadSheet(size_t row, size_t col )
    : m_row(row), m_column(col) {

    m_cells = new SpreadSheetCell**[m_row];
    for (size_t row = 0; row < m_row; ++row) {
        m_cells[row] = new SpreadSheetCell*[m_column];
        for (size_t col = 0; col < m_column; ++col) {
          m_cells[row][col] = new SpreadSheetCell();
    }
  }
}

SpreadSheet::~SpreadSheet() {
  if(this->m_cells != nullptr){
    for (size_t r = 0; r < m_row; ++r) {
      for (size_t c = 0; c < m_column; ++c) {
        delete m_cells[r][c]; 
      }
      delete[] m_cells[r];
    }
    delete[] m_cells;
  }
}

void SpreadSheet::addRow(size_t newRows) {

  int row = m_row; 
  row += newRows;
  
  SpreadSheet tmp(row, m_column);
  for (size_t r = 0; r < m_row; ++r) {
    for (size_t c = 0; c < m_column; ++c) {
      tmp.m_cells[r][c]->setStringValue( m_cells[r][c]->getStringValue());
    }
  }
  m_row = row;
  this->m_cells = tmp.m_cells;
  tmp.m_cells = nullptr;
}

void SpreadSheet::addColumn(size_t newCols){
 int col = m_column;
  col += newCols;
  SpreadSheet tmp(m_row, col);
  for (size_t r = 0; r < m_row; ++r) {
    for (size_t c = 0; c < m_column; ++c) {
      tmp.m_cells[r][c]->setStringValue( m_cells[r][c]->getStringValue());
    }
  }
  m_column = col;
  this->m_cells = tmp.m_cells;
  tmp.m_cells = nullptr;
}

void SpreadSheet::removeRow(size_t rowNumber) {

  if(rowNumber < 0 || rowNumber >= m_row) {
    throw std::runtime_error("invalid argument: row out of range! ");
    std::exit(2);
  }

  for (size_t col = 0; col < m_column; ++col) {
    delete m_cells[rowNumber][col];
  }
  delete[] m_cells[rowNumber];

  m_cells[rowNumber] = nullptr;
  --m_row;
  SpreadSheetCell*** tmp = new SpreadSheetCell**[m_row];
  size_t i = 0, j = 0;
  while(i < m_row) {
    if(m_cells[j] == nullptr) {
      ++j;
    }
    tmp[i] = m_cells[j];
    ++i;
    ++j;
  }
  m_cells = tmp;
  tmp = nullptr;
}

void SpreadSheet::removeColumn(size_t rowNumber) {
  if(rowNumber < 0 || rowNumber >= m_row) {
    throw std::runtime_error("invalid argument: row out of range! ");
    std::exit(2);
  }
  int newCol = m_column - 1;
  SpreadSheetCell*** tmp = new SpreadSheetCell**[m_row];
  for (size_t col = 0; col < m_row; ++col) {
    delete m_cells[col][rowNumber];
    m_cells[col][rowNumber] = nullptr;
    tmp[col] = new SpreadSheetCell*[newCol];
  }
  --m_column;
 size_t k = 0;
  for (size_t i = 0; i < m_row; ++i) {
    for (size_t j = 0; j < m_column; ++j) {
      if(m_cells[i][j] == nullptr) {
        ++k;
      }
      tmp[i][j] = m_cells[i][k];
      ++k;
   }
   k = 0;
  }
  m_cells = tmp;
  tmp = nullptr;
}

void SpreadSheet::printCells() {
  for (size_t row = 0; row < m_row; ++row) {
    for (size_t col = 0; col < m_column; ++col) {
      std::cout << m_cells[row][col]->getStringValue() << "  ";
    }
    std::cout << std::endl;
  }
}

void SpreadSheet::setCell(size_t row, size_t column, const std::string& value) {
  m_cells[row][column]->setStringValue(value);
}

SpreadSheetCell& SpreadSheet::getCell(size_t row, size_t column) {
  if(row > m_row || column > m_column) {
    throw std::invalid_argument("Out of Sheet");
  }
  return *(m_cells[row][column]);
}

int main() {
  SpreadSheet st1(1,1);
  st1.addRow(1);
  st1.addColumn(1);
  st1.getCell(0,0).setStringValue("hell");
  st1.getCell(0,1).setStringValue("hell2");
  st1.getCell(1,0).setStringValue("hell3");
  st1.getCell(1,1).setStringValue("hell");
  st1.printCells();
//  std::cout << st1.getCell(0,0).getStringValue();

  return 0;
}