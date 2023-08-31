#ifndef SPREAD_SHEET_CELL
#define SPREAD_SHEET_CELL

#include <string>

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

#endif
