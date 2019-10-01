//
// Created by Martín García on 24/08/2019.
//

#include "communicator.h"

Communicator::Communicator():   port(), receiver(port),
                                sender(port) {
//    receiver.start();
    sender.start();
}

Communicator::~Communicator() {
    port.close();
}
