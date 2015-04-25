#include "USBRemoteMod.h"
#include <cstdio>
#include <iostream>


int main(int argc, char *argv[])
{
   double data[4]; //throttle, pitch, roll, yaw values from 0-100 except roll and yaw
   bool startMod = false; 
   bool getModData = false;
   
   USBRemote *usbr = new USBRemote();
   startMod = usbr->start();
   
   sleep(1);
   
   printf("start %d\n", startMod);
   //printf("get data %d\n %f, %f, %f, %f\n", getModData, data[0], data[1], data[2], data[3]);
   while(1)
   {
   	getModData = usbr->getModValues(data, 4);
   	std::cout << "Get Data " << getModData << ", " << data[0] << ", " << data[1] << ", " << data[2] << ", " << data[3] << "\n";
   }
}
