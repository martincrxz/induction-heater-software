//
// Created by Martín García on 04/09/2019.
//

#include "sender.h"

Sender::~Sender() {
    keep_processing = false;
    this->wait();
}

void Sender::run(){

}