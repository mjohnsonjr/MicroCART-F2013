/*
 * File: controls.c
 * Global procedures:
 * 		setThrottle();
 * 		setAileron();
 * 		setRudder();
 * 		setElevator();
 * 		setGear();
 *  Created on: Jun 26, 2013
 *      Author: root
 */

/*---------------------------------------------------------
INCLUDES
---------------------------------------------------------*/
#include <system.h>
#include "altera_avalon_pio_regs.h"
#include "controls.h"

void initControls(){
	setThrottle(0);
	setAileron(50);
	setRudder(50);
	setElevator(50);
	setGear(1);

}
void setThrottle(int throttleSet){
	throttleSet = throttleSet*200;
	IOWR_ALTERA_AVALON_PIO_DATA( PIO_THRO_BASE,throttleSet );
}
void setAileron(int aileronSet){
	aileronSet = aileronSet*200;
	IOWR_ALTERA_AVALON_PIO_DATA( PIO_AILE_BASE,aileronSet );
}
void setRudder(int rudderSet){
	rudderSet = rudderSet*200;
	IOWR_ALTERA_AVALON_PIO_DATA( PIO_RUDD_BASE,rudderSet );
}
void setElevator(int elevatorSet){
	elevatorSet = elevatorSet*200;
	IOWR_ALTERA_AVALON_PIO_DATA( PIO_ELEV_BASE,elevatorSet );
}
void setGear(int gearSet){
	if(gearSet ==1){
		gearSet = 20000;
	}else{
		gearSet = 0;
	}
	IOWR_ALTERA_AVALON_PIO_DATA( PIO_GEAR_BASE,gearSet );
}

