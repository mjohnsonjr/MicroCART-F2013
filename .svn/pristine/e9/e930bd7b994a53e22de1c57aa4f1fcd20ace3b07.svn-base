#include "Module.h"
#include "MCTStructures.h"

#include <string>

Module::Module()
{
    modName="";
}

Module::Module(std::string name)
{
    modName = name;
    //set all module variables to beginning values
    modOrientation.pitch = 0;
    modOrientation.roll = 0;
    modOrientation.throttle = 0;
    modPosition.altitude = 0;
    modPosition.latitude = 0;
    modPosition.longitude = 0;
    modPosition.GPSalt = 0;
    modPosition.GPSlat = 0;
    modPosition.GPSlong = 0;
    modDirection = 0;
}

/* Module Notes

  Tracking position modules should set GPS variable of modPosition to -1000 to indicate that they are not used in the module


*/
