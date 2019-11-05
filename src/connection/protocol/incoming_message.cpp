#include "incoming_message.h"

IncomingMessage::IncomingMessage(message_id id): MicroMessage(id){}

QByteArray IncomingMessage::serialize() {
	return QByteArray(0);
}