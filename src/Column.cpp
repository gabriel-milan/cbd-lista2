#include "../include/Column.h"


Column::Column(std::string columnName, std::string columnType, int columnSz) {
  this->columnName = columnName;
  this->columnType = columnType;
  this->columnSize = columnSz;
}

Column::~Column() {
}

std::ostream& operator<<(std::ostream &out, const Column& c) {
  if (c.columnSize == -1) return out << c.columnName << '\xff' << c.columnType;
  return out << c.columnName << '\xff' << c.columnType << '(' << c.columnSize << ')';
}
