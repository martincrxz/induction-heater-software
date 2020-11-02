//
// Created by fedemgp on 30/10/20.
//

#ifndef TRABAJOPROFESIONAL_CHART_FILE_WRITER_H
#define TRABAJOPROFESIONAL_CHART_FILE_WRITER_H

#include <QtCore/QThread>
#include <vector>
#include <fstream>
#include <stream.h>
#include <string>

enum class PointType {EXIT, POWER, FRECUENCY, CURRENT, TEMPERATURE};

struct ChartPoint {
    double time;
    double value;
    PointType type;
    ChartPoint(): time(0), value(0), type(PointType::EXIT){};
    ChartPoint(double time, double value, PointType type): time(time), value(value), type(type) {};
};
class ChartFileWriter: public QThread {
    Q_OBJECT
public:
    ChartFileWriter(std::string directory);
    ~ChartFileWriter();
    void pushPoint(ChartPoint point);
    void stop();
private:
    void run() override;
    void openFile(std::string dir, std::fstream &file, const char *seriesName);
    /*
     * Archivos donde se guaradarán los distintos datos reicbidos
     */
    std::fstream current_file;
    std::fstream frecuency_file;
    std::fstream power_file;
    std::fstream temperature_file;
    std::atomic<bool> keep_processing{true};
    IO::Stream<ChartPoint> queue;

    void writeData(ChartPoint &point, std::fstream &fstream);
};


#endif //TRABAJOPROFESIONAL_CHART_FILE_WRITER_H
