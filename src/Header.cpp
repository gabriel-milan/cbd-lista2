#include "../include/Header.h"

#include <iostream>

#include "../include/DataRecord.h"

Header::Header(std::string headerFilename) {
  this->headerFilename = headerFilename;
  std::string line;
  this->headerFile.open(this->headerFilename, std::ios_base::in);
  if (headerFile.good()) {
    std::getline(headerFile, line);
    std::list<std::string> columns = this->split(line, ";");
    for (std::list<std::string>::iterator it = columns.begin(); it != columns.end(); it++) {
      std::list<std::string> tokens = this->split(*it, "\xff");
      std::string columnName = tokens.front();
      tokens.pop_front();
      std::string columnTypeAndSz = tokens.front();
      tokens.pop_front();
      tokens = this->split(columnTypeAndSz, "(");
      std::string columnType = tokens.front();
      tokens.pop_front();
      int columnSz = -1;
      if (tokens.begin() != tokens.end()) {
        std::string columnSzStr = tokens.front();
        tokens.pop_front();
        columnSz = std::atoi(columnSzStr.substr(0, -1).c_str());
      }
      this->schema.addColumn(Column(columnName, columnType, columnSz));
    }
    std::getline(headerFile, line);
    this->recordsNumber = std::atoi(line.c_str());
    std::getline(headerFile, line);
    this->recordSize = std::atoi(line.c_str());
  } else {
    this->schema.addColumn(Column("uid",      "UINT32_T"));
    this->schema.addColumn(Column("uhe",      "INT"));
    this->schema.addColumn(Column("cenario",  "INT"));
    this->schema.addColumn(Column("estagio",  "CHAR",   13));
    this->schema.addColumn(Column("geracao",  "FLOAT"));
    this->recordsNumber = 0;
    this->recordSize = sizeof(DataRecord);
  }
  this->headerFile.close();
}

Header::~Header() {
}

void Header::addRecord() {
  this->recordsNumber++;
}

void Header::delRecord() {
  this->recordsNumber--;
}

void Header::write() {
  this->headerFile.open(this->headerFilename, std::ios_base::out);

  this->headerFile << this->schema << std::endl;
  this->headerFile << this->recordsNumber << std::endl;
  this->headerFile << this->recordSize << std::endl;
}

std::list<std::string> Header::split(std::string s, std::string delim) {
  std::list<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delim)) != std::string::npos) {
    tokens.push_back(s.substr(0, pos));
    s.erase(0, pos + delim.length());
  }
  tokens.push_back(s);
  return tokens;
}
