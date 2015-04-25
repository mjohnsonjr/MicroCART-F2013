#include "USBRemoteMod.h"
#include "MCTUtilities.h"

#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/joystick.h>

USBRemote::USBRemote() : Module("USB Remote")
{
    usb_id = "1781:0e56";
    thrtVal = 0;
    rollVal = 50;
    pitchVal = 50;
    yawVal = 50;
    axes = 2;
    buttons = 2;

}

USBRemote::~USBRemote()
{

}
/**
  * Returns the percentage of value range of the usb remote
  * @author MCT 2010 // JeffWick MCT2011
  * @data throttle, pitch, roll, yaw values from 0-100 except roll and yaw
  * @size number of data values, should be 4
 **/
bool USBRemote::getModValues(double* data, int size)
{
    int i;
    js_event js;
    if(size == 4) {
        //Check if a new event from the USB controller has occured
        //if(read(rc_fd, &js, sizeof(struct js_event)) == sizeof(struct js_event)) {
        if(read(rc_fd, &js, sizeof(struct js_event)) > 0) {
            switch(js.type & ~JS_EVENT_INIT) {
            case JS_EVENT_BUTTON:
                button[js.number] = js.value;
                break;

            case JS_EVENT_AXIS:
                axis[js.number] = js.value;
                break;
            }
            double tempNum;
            if (axes) {
                for (i = 0; i < 5; i++) {// read from only axis 0,1,2,4
                    tempNum = (double) axis[i];
                    // Unknown why but sometimes these values are lost after creation so I am just redefining them each time
                    DIGITAL_FACTOR = 337;
                    ROLL_STEPS = 75;
                    PITCH_STEPS = 60;
                    THROTTLE_STEPS = 63;
                    YAW_STEPS = 76;
                    switch(i) {
                    case 0:
                        rollVal = 50.0 +  50.0 * ( (tempNum/DIGITAL_FACTOR) / ROLL_STEPS ) ;
                        break;

                    case 1:
                        pitchVal = 50 - 50.0 * ( (tempNum/DIGITAL_FACTOR) / PITCH_STEPS );
                        break;

                    case 2:
                        thrtVal = 50 - 50.0 * ( (tempNum/DIGITAL_FACTOR) / THROTTLE_STEPS );
                        break;

                    case 4:
                        yawVal= 50.0 + 50.0 * ( (tempNum/DIGITAL_FACTOR) / YAW_STEPS );
                        break;

                    default:
                        break;
                    }
                }
            }
        }
        // make sure they do not leave the range of 0 to 100
        if(thrtVal < 0)
            thrtVal = 0;
        if(pitchVal < 0)
            pitchVal = 0;
        if(rollVal < 0)
            rollVal = 0;
        if(yawVal < 0)
            yawVal = 0;
        if(thrtVal > 100)
            thrtVal = 100;
        if(pitchVal > 100)
            pitchVal = 100;
        if(rollVal > 100)
            rollVal = 100;
        if(yawVal > 100)
            yawVal = 100;
        data[0] = thrtVal;
        data[1] = pitchVal;
        data[2] = rollVal;
        data[3] = yawVal;
        return true;
    } else {
        return false;
    }
}

//Verifies that the proper usb device is connected and gets the file reference for it
bool USBRemote::start()
{
    if( get_USB_port(usb_id) == -1 )
        return false;

    std::string rcFilename = "/dev/input/js0";

    if ((rc_fd = open(rcFilename.c_str(), O_RDONLY)) < 0) {
        return false;
    }

    ioctl(rc_fd, JSIOCGAXES, &axes);
    ioctl(rc_fd, JSIOCGBUTTONS, &buttons);

    fcntl(rc_fd, F_SETFL, O_NONBLOCK);

    rollVal=50;
    thrtVal=0;
    yawVal=50;
    pitchVal=50;

    return true;
}

//For this module update is never needed the values are updated when getModValues is called
bool USBRemote::update()
{
    return true;
}

//stops the Module
bool USBRemote::stop()
{
    close(rc_fd);
    return true;
}
