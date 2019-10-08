#include "../include/DataRecord.h"

std::ostream &print(std::ostream &out, const char *str, size_t sz) {
  for (size_t i = 0; i < sz; i++)
  {
    out << str[i];
  }
  out << ',';
  return out;
}

DataRecord::DataRecord(const char *string) {
  std::stringstream ss(string);
  std::vector<std::string> columnValues;

  // std::cout << string << std::endl;

  while (ss.good()) {
    std::string substr;
    getline(ss, substr, ',');
    columnValues.push_back(substr);
  }

  this->uid = std::stoi (columnValues[0]);
  this->uhe = std::stoi (columnValues[1]);
  this->cenario = std::stoi (columnValues[2]);
  this->estagio = columnValues[3];
  this->geracao = std::stof (columnValues[4]);
  
  // std::cout << this->uid << std::endl;
}

DataRecord::DataRecord(const char *string, uint64_t uid) {
  std::stringstream ss(string);
  std::vector<std::string> columnValues;

  while (ss.good()) {
    std::string substr;
    getline(ss, substr, ',');
    columnValues.push_back(substr);
  }

  // std::cout << columnValues[0] << ',' << columnValues[1] << ',' << columnValues[2] << ',' << columnValues[3] << ',' << std::endl;

  this->uhe = std::stoi (columnValues[0]);
  this->cenario = std::stoi (columnValues[1]);
  this->estagio = columnValues[2];
  this->geracao = std::stof (columnValues[3]);

  this->uid = uid;
  

  // std::cout << this->uid << std::endl;
}

std::ostream &operator<<(std::ostream &out, const DataRecord &r) {
  out << r.uid << ',';
  out << r.uhe << ',';
  out << r.cenario << ',';
  out << r.estagio << ',';
  out << r.geracao;
  return out << '\n';
}

bool DataRecord::operator<(const DataRecord &r) const {
  return this->uid < r.uid;
}

size_t DataRecord::csvcpy(char *dst, const char *src, size_t start, size_t sz) {
  size_t end = start;
  size_t idx = -1;
  for (; end < start + sz; end++)
  {
    // std::cout << end << "/" << src[end] << std::endl;
    if (src[end] == ',')
    {
      idx = end - start;
      memcpy(dst, src + start, idx);
      break;
    }
  }
  if (idx == -1)
    memcpy(dst, src + start, end - start);
  else
    memset(dst + idx, 0x00, sz - idx);
  return end;
}

bool DataRecord::uidCmp(uint32_t uid) const {
  return uid == this->uid;
}

bool DataRecord::geracaoInRange (float begin, float end) const {
  return ((this->geracao >= begin) && (this->geracao <= end));
}