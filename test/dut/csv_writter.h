//
// Created by fedemgp on 14/11/20.
//

#ifndef TRABAJOPROFESIONAL_CSV_WRITTER_H
#define TRABAJOPROFESIONAL_CSV_WRITTER_H
#include "fstream"

class CsvWritter {
public:
    explicit CsvWritter(const char *filepath);
    ~CsvWritter();
    void writeData(float power, float temp);

private:
    std::fstream file;
};


#endif //TRABAJOPROFESIONAL_CSV_WRITTER_H
