/**
 * Created by Federico Manuel Gomez Peter
 * on 08/02/2020
 */
#include "file_control.h"

FileControl::FileControl(float kp, float ki, float kd, 
	control_steps &controlDirectives, SerialPort *sp):
		ClassicPID(kp, ki, kd, 0.0f, sp),
		steps(controlDirectives) {

}

void FileControl::reset(float newTargetTemp) {
	this->targetTemp = newTargetTemp;
	this->errorValues.clear();
	this->iteration = 0;
}

FileControl::~FileControl() {

}

unsigned char FileControl::process(std::shared_ptr<TemperatureReading> data) {
    return ClassicPID::process(data);
}
