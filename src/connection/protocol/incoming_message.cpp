#include "incoming_message.h"
#include <QDateTime>

IncomingMessage::IncomingMessage(message_id id): MicroMessage(id){
    timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

QByteArray IncomingMessage::serialize() {
	return QByteArray(0);
}

std::uint64_t IncomingMessage::getTimestamp() {
    return this->timestamp;
}
