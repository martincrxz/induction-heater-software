//
// Created by fedemgp on 30/10/20.
//

#include <messages.h>
#include <logger/logger.h>
#include <QtCore/QDateTime>
#include "chart_file_writer.h"

ChartFileWriter::~ChartFileWriter() {
    this->stop();
    this->queue.close();
}

ChartFileWriter::ChartFileWriter(std::string directory) {
    openFile(directory + "/corriente", this->current_file, "Corriente[A]");
    openFile(directory + "/frecuencia", this->frecuency_file, "Frecuencia[Hz]");
    openFile(directory + "/potencia", this->power_file, "Potencia[W]");
    openFile(directory + "/temperatura", this->temperature_file, "Temperatura[°C]");
    QThread::start();
}

void ChartFileWriter::openFile(std::string filename, std::fstream &stream, const char *seriesName) {
    QDateTime currentTime = QDateTime::currentDateTime();
    filename += "-" + currentTime.toString("yyyy-MM-dd-hh:mm:ss").toStdString() + ".csv";
    Logger::info(FILE_SAVED_MSG, filename.c_str());
    stream.open(filename, std::ios_base::out);
    // Escribo el header
    stream << "Tiempo[hh-mm-ss]," << seriesName << std::endl;
}

void ChartFileWriter::run() {
    try {
        while(keep_processing) {
            ChartPoint point;
            this->queue.pop(point);

            switch (point.type) {
                case PointType::CURRENT: {
                    writeData(point, current_file);
                    break;
                }
                case PointType::FRECUENCY: {
                    writeData(point, frecuency_file);
                    break;
                }
                case PointType::POWER: {
                    writeData(point, power_file);
                    break;
                }
                case PointType::TEMPERATURE: {
                    writeData(point, temperature_file);
                    break;
                }
                case PointType::EXIT: {
                    return;
                }
            }
        }
    } catch (std::exception &e) {
        Logger::critical(e.what());
    } catch (...) {
        Logger::critical(UNKNOWN_ERROR_MSG, "main");
    }
}

void ChartFileWriter::writeData(ChartPoint &point, std::fstream &file) {
    QDateTime x = QDateTime::fromMSecsSinceEpoch(point.time);
    file << x.toString("hh:mm:ss").toStdString() << "," << point.value << std::endl;
}

void ChartFileWriter::stop() {
    this->pushPoint(ChartPoint(0, 0, PointType::EXIT));
    this->keep_processing = false;
}

void ChartFileWriter::pushPoint(ChartPoint point) {
    this->queue.push(point);
}
