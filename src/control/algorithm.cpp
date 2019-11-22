//
// Created by Martín García on 11/11/2019.
//
#include <iostream>

#include "algorithm.h"

void Algorithm::dataAvailable(int data) {
	this->queue.push(data);
}

void Algorithm::run() {
	 try {
        while (keep_processing) {
            int msg;
            queue.pop(msg, true);
            if (msg < 0) {
                keep_processing = false;
            } else {
            	this->process(msg);
            }
        }
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unknown error in Algorithm::run" << std::endl;
    }
}

void Algorithm::stop() {
	this->queue.push(-1);
}
