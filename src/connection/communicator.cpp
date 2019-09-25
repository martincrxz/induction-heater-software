//
// Created by Martín García on 24/08/2019.
//

#include "communicator.h"

Communicator::Communicator():   port(), protocol(), receiver(port),
                                sender(port, protocol) {
//    receiver.start();
    sender.start();
}

Communicator::~Communicator() {
    port.close();
}
