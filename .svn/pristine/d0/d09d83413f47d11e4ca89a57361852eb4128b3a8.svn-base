/*---------------------------------------------------------
 File: ping.c

 Global procedures:
      - getPingDistance

 Local procedures:
      - 
          
 --------------------------------------------------------*/

/*---------------------------------------------------------
INCLUDES
---------------------------------------------------------*/
#include <system.h>

#include "altera_avalon_pio_regs.h"

/*---------------------------------------------------------
DEFINITIONS
---------------------------------------------------------*/
/*---------------------------------------------------------
TYPES
---------------------------------------------------------*/
/*---------------------------------------------------------
GLOBAL VARIABLES
---------------------------------------------------------*/
/*---------------------------------------------------------
MACROS
---------------------------------------------------------*/
/*---------------------------------------------------------
PROCEDURES
---------------------------------------------------------*/


/*********************************************************
 * Title:               getPingDistance
 *
 * Description:
 *      Returns the distance found by the ping sensor
 *      in meters.
 *
 ********************************************************/
float getPingDistance()
{
unsigned int lengthClks;
float lengthUS;
float oneWayUS;
float oneWayM;

/*------------------------------------------
Read from hardware. Read the number of clock
cycles that Parallax Ping sensor's echo
pulse lasted.
------------------------------------------*/
lengthClks = IORD_ALTERA_AVALON_PIO_DATA( PIO_LENGTH_BASE );

/*------------------------------------------
Convert the number of clocks to microseconds
since we know it is a 25Mhz clock
------------------------------------------*/
lengthUS = lengthClks / 25.0;

/*------------------------------------------
lengthUS is a round-trip time for sound
to travel to target and return. Divide by two
to get one way time.
------------------------------------------*/
oneWayUS = lengthUS / 2;

/*------------------------------------------
Use speed of sound, 344.4 m/s, and convert from
microseconds to seconds to get meters
------------------------------------------*/
oneWayM = oneWayUS * 344.4 / 1000000.0;

return oneWayM;
}





