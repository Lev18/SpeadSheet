#include "spreadSheetCell.h"
#include <sstream>

SpreadSheetCell::SpreadSheetCell() : m_value(" ") {
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
