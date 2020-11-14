//
// Created by fedemgp on 14/11/20.
//

#include "csv_writter.h"

CsvWritter::CsvWritter(const char *filepath): file(filepath, std::ios_base::out | std::ios_base::trunc) {
    file << "Potencia (W),Temperatura(°C)" << std::endl;
}

CsvWritter::~CsvWritter() {}

void CsvWritter::writeData(float power, float temp) {
    file << power << "," << temp << std::endl;
}
