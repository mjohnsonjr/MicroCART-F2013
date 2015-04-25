/*
 * USBController.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: Michael Johnson
 */

#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <pthread.h>
#include "USBController.h"

namespace{

	/* Borrowed from MCTUtilities.cpp (2012). */
    int get_USB_port(std::string dev_id){
		FILE *fp;
		char line[80];
		char num[3];
		int ret = -1;
		std::string comm = "lsusb -d " + dev_id;
		fp = popen(comm.c_str(), "r");
        if(fgets(line, sizeof line, fp)) {
			num[0] = line[15];
			num[1] = line[16];
			num[2] = line[17];
			ret = atoi(num);
        }

		pclose(fp);
		return ret;
	}

	/* Thread setup function for USBController */
	void* controller_threadcall(void* i_controller){
		USBController* controller = (USBController*) i_controller;

		while(controller->is_started()){
			controller->update();
		}
		pthread_exit(NULL);
	}
}

USBController::USBController(CommandInterpreter& i_interpreter) : interpreter(i_interpreter){

	this->usb_id = "1781:0e56";
	this->fd = -1;
    this->tear[THROTTLE] = 0;
    this->tear[ROLL] = 50;
    this->tear[PITCH] = 50;
    this->tear[YAW] = 50;
    this->axes = 2;
    this->buttons = 2;
    this->thread = NULL;
    this->running = false;

}

USBController::~USBController() {

}

/**
 * Sets up the USB controller.
 * @return True on succes, false otherwise.
 */
bool USBController::setup()
{
    if( get_USB_port(this->usb_id) == -1 ){
        return false;
    }

    std::string rcFilename = "/dev/input/js0";

    if ((this->fd = open(rcFilename.c_str(), O_RDONLY)) < 0){
        return false;
    }

    /* Eclipse is stupid, it still builds. */
    ioctl(this->fd, JSIOCGAXES, &axes);
    ioctl(this->fd, JSIOCGBUTTONS, &buttons);


    fcntl(this->fd, F_SETFL, O_NONBLOCK);

    this->tear[ROLL] = 50;
    this->tear[THROTTLE] = 0;
    this->tear[YAW] = 50;
    this->tear[PITCH] = 50;

    return true;
}

/**
 * Starts a thread to poll the controller for updates.
 */
bool USBController::start(){
    this->running = true;

    /* Create running thread for controller */
	if(pthread_create(&this->thread, NULL, controller_threadcall, (void*)this) == 0){
        return true;
	}

    this->running = false;
	return false;
}

bool USBController::stop(){
	this->running = false;

	pthread_join(this->thread, NULL);
	this->interpreter.getQuadCommand().setTargetPitch(0.0);
	this->interpreter.getQuadCommand().setTargetRoll(0.0);
	this->interpreter.getQuadCommand().setTargetDirection(0.0);
    this->interpreter.getQuadCommand().setManualControl(false);

	return true;
}

void USBController::update(){
    int i;
    js_event js;
        //Check if a new event from the USB controller has occured
        if(read(this->fd, &js, sizeof(struct js_event)) > 0) {
            switch(js.type & ~JS_EVENT_INIT) {
            case JS_EVENT_BUTTON:
                this->button[js.number] = js.value;
                break;

            case JS_EVENT_AXIS:
                this->axis[js.number] = js.value;
                break;
            }
            double tempNum;
            if (this->axes) {
                for (i = 0; i < 5; i++) {// read from only axis 0,1,2,4
                    tempNum = (double) this->axis[i];
                    // Unknown why but sometimes these values are lost after creation so I am just redefining them each time

                    switch(i) {
                    case 0:
                        this->tear[ROLL] = (50.0 +  50.0 * ( (tempNum/DIGITAL_FACTOR) / ROLL_STEPS ) );
                        break;

                    case 1:
                        this->tear[PITCH] = (50 - 50.0 * ( (tempNum/DIGITAL_FACTOR) / PITCH_STEPS ) );
                        break;

                    case 2:
                        this->tear[THROTTLE] = (50 - 50.0 * ( (tempNum/DIGITAL_FACTOR) / THROTTLE_STEPS ) );
                        break;

                    case 4:
                        this->tear[YAW]= (50.0 + 50.0 * ( (tempNum/DIGITAL_FACTOR) / YAW_STEPS ) );
                        break;

                    default:
                        break;
                    }
                }
            }
        }
        // make sure they do not leave the range of 0 to 100
        if(this->tear[THROTTLE] < 0)
            this->tear[THROTTLE] = 0;
        if(this->tear[PITCH] < 0)
            this->tear[PITCH] = 0;
        if(this->tear[ROLL] < 0)
            this->tear[ROLL] = 0;
        if(this->tear[YAW] < 0)
            this->tear[YAW] = 0;
        if(this->tear[THROTTLE] > 100)
            this->tear[THROTTLE] = 100;
        if(this->tear[PITCH] > 100)
            this->tear[PITCH] = 100;
        if(this->tear[ROLL] > 100)
            this->tear[ROLL] = 100;
        if(this->tear[YAW] > 100)
            this->tear[YAW] = 100;

        /* Set values in command */
        this->interpreter.getQuadCommand().setAutoThrottle(false);
        this->interpreter.getQuadCommand().setManualControl(true);
        this->interpreter.getQuadCommand().setManualThrottle(this->tear[THROTTLE]);
        this->interpreter.getQuadCommand().setTargetPitch(this->tear[PITCH]);
        this->interpreter.getQuadCommand().setTargetRoll(this->tear[ROLL]);
        this->interpreter.getQuadCommand().setTargetDirection(this->tear[YAW]);

        //TODO: DELETE
        //std::cerr << this->tear[THROTTLE] << " " << this->tear[PITCH] << " " << this->tear[ROLL] << " " << this->tear[YAW] << "\n";
}

