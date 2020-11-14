//
// Created by fedemgp on 14/11/20.
//

#include "csv_writter.h"

CsvWritter::CsvWritter(const char *filepath): file(filepath, std::ios_base::out | std::ios_base::trunc) {
    file << "Potencia (%),Temperatura(°C)" << std::endl;
}

CsvWritter::~CsvWritter() {}

void CsvWritter::writeData(float power, float temp) {
    file << power * 100 << "," << temp << std::endl;
}
