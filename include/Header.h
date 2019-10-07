#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <fstream>
#include <list>

#include "Schema.h"

class Header {

  private:
    Schema schema;
    uint64_t recordsNumber;
    uint32_t recordSize;

    std::string headerFilename;
    std::fstream headerFile;

    std::list<std::string> split(std::string str, std::string delim);

  public:
    Header(std::string headerFilename);
    ~Header();

    void addRecord();
    void delRecord();
    void write();

};

#endif