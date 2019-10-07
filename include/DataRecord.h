#ifndef DATA_RECORD_H
#define DATA_RECORD_H

#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

class DataRecord {

  private:
    size_t csvcpy(char *dst, const char *src, size_t start, size_t sz);

  public:
    uint32_t uid;
    int uhe, cenario;
    char estagio [13];
    float geracao;

    DataRecord (const char data[]);

    bool uidCmp(uint32_t uid) const;
    bool geracaoInRange (float begin, float end);

    friend std::ostream &operator<<(std::ostream &out, const DataRecord &r);
    bool operator<(const DataRecord &r) const;

};

#endif