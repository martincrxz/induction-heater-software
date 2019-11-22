//
// Created by Martín García on 11/11/2019.
//

#ifndef TRABAJOPROFESIONAL_ALGORITHM_H
#define TRABAJOPROFESIONAL_ALGORITHM_H

#include <QtCore/QThread>
#include <memory>

#include <stream.h>

class Algorithm : public QThread{
    Q_OBJECT

private:
	IO::Stream<int> queue;
    bool keep_processing{true};
    /**
     * @brief Lanza el hilo de ejecución que toma elementos de a uno y
     * los procesa de forma polimorfica (dependiendo de cada tipo de control)
     */
    void run() override;
    virtual int process(int data) = 0;

public slots:
	void dataAvailable(int data);

public:
	Algorithm() = default;
	virtual ~Algorithm() = default;
	/**
     * @brief Se encarga de terminar la ejecución ordenada
     * del hilo
     */
    void stop();
};


#endif //TRABAJOPROFESIONAL_ALGORITHM_H
