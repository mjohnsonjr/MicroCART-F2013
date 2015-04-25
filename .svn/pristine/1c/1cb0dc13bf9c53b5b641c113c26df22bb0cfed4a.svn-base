/*---------------------------------------------------------
 File: imu.c

 Global procedures:
      - IMU_reg_display
      - readUsefulIMU

 Local procedures:
      - alt_avalon_spi_command_hexcmd
      - conv14to16
      - read_IMU

 --------------------------------------------------------*/

/*---------------------------------------------------------
INCLUDES
---------------------------------------------------------*/
#include <system.h>
#include <stdio.h>

#include <alt_types.h>
#include <altera_avalon_spi_regs.h>
#include <altera_avalon_spi.h>
#include <sys/alt_timestamp.h>


#include "labet.h"
#include "imu.h"

/*---------------------------------------------------------
DEFINITIONS
---------------------------------------------------------*/
/*---------------------------------------------------------
TYPES
---------------------------------------------------------*/
/*---------------------------------------------------------
GLOBAL VARIABLES
---------------------------------------------------------*/
struct heli_sensor_state_t currentHeliState;

char reg_defaults[][6] = {
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "NA  ",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0800",
                "0800",
                "0800",
                "0000",
                "0006",
                "0001",
                "0402",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "0000",
                "4105"

        };

char reg_str[][13] = {
            "FLASH_CNT  R"   ,
            "SUPPLY_OUT R"   ,
            "XGYRO_OUT  R"   ,
            "YGYRO_OUT  R"   ,
            "ZGYRO_OUT  R"   ,
            "XACCL_OUT  R"   ,
            "YACCL_OUT  R"   ,
            "ZACCL_OUT  R"   ,
            "XMAGN_OUT  R"   ,
             "YMAGN_OUT R"   ,
             "ZMAGN_OUT R"   ,
             "TEMP_OUT  R"   ,
             "AUX_ADC   R"   ,
             "XGYRO_OFF RW" ,
             "YGYRO_OFF RW" ,
             "ZGYRO_OFF RW" ,
             "XACCL_OFF RW" ,
             "YACCL_OFF RW" ,
             "ZACCL_OFF RW" ,
             "XMAGN_HIF RW" ,
             "YMAGN_HIF RW" ,
             "ZMAGN_HIF RW" ,
             "XMAGN_SIF RW" ,
             "YMAGN_SIF RW" ,
             "ZMAGN_SIF RW" ,
             "GPIO_CTRL RW" ,
             "MSC_CTRL  RW" ,//26 - 0X1A
             "SMPL_PRD  RW" ,
             "SENS_AVG  RW" ,
             "SLP_CNT   W" ,//29 - 0X1D
             "DIAG_STAT R" ,
             "GLOB_CMD  W" ,//31 - 0X1F
             "ALM_MAG1  RW" ,
             "ALM_MAG2  RW" ,
             "ALM_SMPL1 RW" ,
             "ALM_SMPL2 RW" ,
             "ALM_CTRL  RW" ,
             "AUX_DAC   RW" ,
             "PRODUCT_ID R"

    };

/*---------------------------------------------------------
MACROS
---------------------------------------------------------*/
/*---------------------------------------------------------
PROCEDURES
---------------------------------------------------------*/
static int alt_avalon_spi_command_hexcmd(alt_u32 base, alt_u32 slave,
                           alt_u32 write_length, const alt_u16 * write_data,
                           alt_u32 read_length, alt_u16 * read_data,
                           alt_u32 flags);
static alt_16 conv14to16( alt_u16 data14bit );
static alt_16 read_IMU( alt_u16 reg );


/*********************************************************
 * Title:               IMU_reg_display
 *
 * Description:
 *      Reads and displays the values of all registers
 *      on the IMU
 *
 ********************************************************/
void IMU_reg_display()
{
    int i;
    alt_16 read_data;
    alt_u16 reg;
    printf("\r\n\r\n============IMU - ADIS16400========================"
            "\r\nRegisters");

    for(i=0;i<31;i++)
        {
        reg = (i*2) << 8;
        read_data = read_IMU( reg );
        printf( "\r\n%d.%s\tValue: %x\tDefault: %s", i, reg_str[i], read_data, reg_defaults[i] );
        }
}

/*********************************************************
 * Title:               readUsefulIMU
 *
 * Description:
 *      Reads gyro, accel, and mag data from the IMU
 *
 ********************************************************/
void readUsefulIMU()
{
	//alt_timestamp_type timeStart = alt_timestamp_start();
		//If the timestamp is not available print this out
		//if (timeStart < 0) {
		//printf("No timestamp device available\n");
	//}
    currentHeliState.gyroX = read_IMU( XGYRO_OUT );
    //alt_timestamp_type time1 = alt_timestamp();
    currentHeliState.gyroY = read_IMU( YGYRO_OUT );
    //alt_timestamp_type time2 = alt_timestamp();
    currentHeliState.gyroZ = read_IMU( ZGYRO_OUT );
    //alt_timestamp_type time3 = alt_timestamp();
    currentHeliState.accelX = read_IMU( XACCL_OUT );
    //alt_timestamp_type time4 = alt_timestamp();
    currentHeliState.accelY = read_IMU( YACCL_OUT );
    //alt_timestamp_type time5 = alt_timestamp();
    currentHeliState.accelZ = read_IMU( ZACCL_OUT );
    //alt_timestamp_type time6 = alt_timestamp();
    //currentHeliState.magX = read_IMU( XMAGN_OUT );
    //alt_timestamp_type time7 = alt_timestamp();
    //currentHeliState.magY = read_IMU( YMAGN_OUT );
    //alt_timestamp_type time8 = alt_timestamp();
    //currentHeliState.magZ = read_IMU( ZMAGN_OUT );
    //alt_timestamp_type time9 = alt_timestamp();

    //float print1 = (((float) (time1 - timeStart) * 20)/ 1000000);
    //float print2 = (((float) (time2 - timeStart) * 20)/ 1000000);
    //float print3 = (((float) (time3 - timeStart) * 20)/ 1000000);
    //float print4 = (((float) (time4 - timeStart) * 20)/ 1000000);
    //float print5 = (((float) (time5 - timeStart) * 20)/ 1000000);
    //float print6 = (((float) (time6 - timeStart) * 20)/ 1000000);
    //float print7 = (((float) (time7 - timeStart) * 20)/ 1000000);
    //float print8 = (((float) (time8 - timeStart) * 20)/ 1000000);
    //float print9 = (((float) (time9 - timeStart) * 20)/ 1000000);

    //printf("1: %f 2: %f 3: %f 4: %f 5: %f 6: %f 7: %f 8: %f\n", print1, print2, print3, print4, print5, print6, print7, print8, print9);
    //printf("9: %f", print9);
    currentHeliState.gyroX = conv14to16( currentHeliState.gyroX );
    currentHeliState.gyroY = conv14to16( currentHeliState.gyroY );
    currentHeliState.gyroZ = conv14to16( currentHeliState.gyroZ );
    currentHeliState.accelX = conv14to16( currentHeliState.accelX );
    currentHeliState.accelY = conv14to16( currentHeliState.accelY );
    currentHeliState.accelZ = conv14to16( currentHeliState.accelZ );
    //currentHeliState.magX = conv14to16( currentHeliState.magX );
    //currentHeliState.magY = conv14to16( currentHeliState.magY );
    //currentHeliState.magZ = conv14to16( currentHeliState.magZ );
}

/*********************************************************
 * Title:               alt_avalon_spi_command_hexcmd
 *
 * Description:
 *      This code is a slight variation of the auto-gen
 *      code created in the BSP project. The original
 *      function is "alt_avalon_spi_command" in
 *      altera_avalon_spi.c. Sudhanshu made modifications
 *      to change data from 8 bits to 16 bits to match
 *      our IMU; everything else is the same.
 *
 ********************************************************/
static int alt_avalon_spi_command_hexcmd(alt_u32 base, alt_u32 slave,
                           alt_u32 write_length, const alt_u16 * write_data,
                           alt_u32 read_length, alt_u16 * read_data,
                           alt_u32 flags)
{
  const alt_u16 * write_end = write_data + write_length;
  alt_u16 * read_end = read_data + read_length;

  alt_u32 write_zeros = read_length;
  alt_u32 read_ignore = write_length;
  alt_u32 status;

  /* We must not send more than two bytes to the target before it has
   * returned any as otherwise it will overflow. */
  /* Unfortunately the hardware does not seem to work with credits > 1,
   * leave it at 1 for now. */
  alt_32 credits = 1;

  /* Warning: this function is not currently safe if called in a multi-threaded
   * environment, something above must perform locking to make it safe if more
   * than one thread intends to use it.
   */

  IOWR_ALTERA_AVALON_SPI_SLAVE_SEL(base, 1 << slave);

  /* Set the SSO bit (force chipselect) only if the toggle flag is not set */
  if ((flags & ALT_AVALON_SPI_COMMAND_TOGGLE_SS_N) == 0) {
    IOWR_ALTERA_AVALON_SPI_CONTROL(base, ALTERA_AVALON_SPI_CONTROL_SSO_MSK);
  }

  /*
   * Discard any stale data present in the RXDATA register, in case
   * previous communication was interrupted and stale data was left
   * behind.
   */
  IORD_ALTERA_AVALON_SPI_RXDATA(base);

  /* Keep clocking until all the data has been processed. */
  for ( ; ; )
  {

    do
    {
      status = IORD_ALTERA_AVALON_SPI_STATUS(base);
    }
    while (((status & ALTERA_AVALON_SPI_STATUS_TRDY_MSK) == 0 || credits == 0) &&
            (status & ALTERA_AVALON_SPI_STATUS_RRDY_MSK) == 0);

    if ((status & ALTERA_AVALON_SPI_STATUS_TRDY_MSK) != 0 && credits > 0)
    {
      credits--;

      if (write_data < write_end)
        IOWR_ALTERA_AVALON_SPI_TXDATA(base, *write_data++);
      else if (write_zeros > 0)
      {
        write_zeros--;
        IOWR_ALTERA_AVALON_SPI_TXDATA(base, 0);
      }
      else
        credits = -1024;
    };

    if ((status & ALTERA_AVALON_SPI_STATUS_RRDY_MSK) != 0)
    {
      alt_u32 rxdata = IORD_ALTERA_AVALON_SPI_RXDATA(base);

      if (read_ignore > 0)
        read_ignore--;
      else
        *read_data++ = (alt_u16)rxdata;
      credits++;

      if (read_ignore == 0 && read_data == read_end)
        break;
    }

  }

  /* Wait until the interface has finished transmitting */
  do
  {
    status = IORD_ALTERA_AVALON_SPI_STATUS(base);
  }
  while ((status & ALTERA_AVALON_SPI_STATUS_TMT_MSK) == 0);

  /* Clear SSO (release chipselect) unless the caller is going to
   * keep using this chip
   */
  if ((flags & ALT_AVALON_SPI_COMMAND_MERGE) == 0)
    IOWR_ALTERA_AVALON_SPI_CONTROL(base, 0);

  return read_length;
}

/*********************************************************
 * Title:               conv14to16
 *
 * Description:
 *      Converts 14-bit data to 16-bit data. 2's complement.
 *
 ********************************************************/
static alt_16 conv14to16( alt_u16 data14bit )
{
alt_16 data16bit = (alt_16)data14bit;
data16bit = data16bit << 2; // Shift the top two bits out
data16bit = data16bit >> 2; // Shift two bits back in, they will replicate the sign bit
return data16bit;
}

/*********************************************************
 * Title:               read_IMU
 *
 * Description:
 *      Reads the indicated register from the IMU
 *
 ********************************************************/
static alt_16 read_IMU( alt_u16 reg )
{
alt_u16 read_data;
alt_u32 slave = 0x00000000;
alt_u32 write_length = 1;
alt_u32 read_length = 1;
alt_u32 flags;

alt_avalon_spi_command_hexcmd( SPI_0_BASE, slave, write_length, &reg, read_length, &read_data, flags );

return (alt_16)read_data;
}


