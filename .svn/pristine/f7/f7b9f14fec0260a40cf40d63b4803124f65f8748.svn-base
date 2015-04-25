#ifndef USBREMOTEMOD_H
#define USBREMOTEMOD_H

#include "Module.h"
#include <string>


class USBRemote : public Module
{
protected:
    std::string usb_id;
    int rc_fd;
    int axis[5];
    char button[2];
    unsigned char axes;
    unsigned char buttons;

    double thrtVal;
    double rollVal;
    double yawVal;
    double pitchVal;

    //Ranges for joystick movement of this USB device
    double DIGITAL_FACTOR;
    double ROLL_STEPS;
    double PITCH_STEPS;
    double THROTTLE_STEPS;
    double YAW_STEPS;


public:
    USBRemote();
    ~USBRemote();
    bool isContMod() {return true;}
    bool getModValues(double *data, int size);
    bool start();
    bool update();
    bool stop();
};

#endif // USBREMOTEMOD_H

