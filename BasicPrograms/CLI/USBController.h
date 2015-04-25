/*
 * USBController.h
 *
 *  Created on: Mar 26, 2014
 *      Author: Michael Johnson
 */

#ifndef USBCONTROLLER_H_
#define USBCONTROLLER_H_

#define DIGITAL_FACTOR 337
#define ROLL_STEPS 75
#define PITCH_STEPS 60
#define THROTTLE_STEPS 63
#define YAW_STEPS 76

/* Data access in tear variable. */
#define THROTTLE 0
#define PITCH 1
#define ROLL 2
#define YAW 3


#include <string>
#include "CommandInterpreter.h"


class USBController {
public:
	USBController(CommandInterpreter&);
	virtual ~USBController();
	void update();
	bool setup();
	bool start();
	bool stop();

	inline bool is_started(){
		return this->running;
	}
	inline float* getData(){
		return this->tear;
	}

private:
    std::string usb_id;
    int fd;
    int axis[5];
    char button[2];
    unsigned char axes;
    unsigned char buttons;

    float tear[4];

    pthread_t thread;
    volatile bool running;

    CommandInterpreter& interpreter;
};

#endif /* USBCONTROLLER_H_ */
