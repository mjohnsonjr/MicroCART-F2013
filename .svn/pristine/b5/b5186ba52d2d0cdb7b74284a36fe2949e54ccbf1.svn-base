/*---------------------------------------------------------
 File: imu.h
 --------------------------------------------------------*/
#ifndef IMU_H_
#define IMU_H_

/*---------------------------------------------------------
INCLUDES
---------------------------------------------------------*/
#include <alt_types.h>

/*---------------------------------------------------------
DEFINITIONS
---------------------------------------------------------*/
/*-------------------------------------------
Determined experimentally from timeTest
-------------------------------------------*/
#define HELI_SENSOR_READS_PER_SEC ( 1300 )

/*-------------------------------------------
IMU register offsets, from the datasheet
-------------------------------------------*/
#define FLASH_CNT  0x0000 /* R       Flash memory write count */
#define SUPPLY_OUT 0x0200 /* R       Power supply measurement */
#define XGYRO_OUT  0x0400 /* R       X-axis gyroscope output */
#define YGYRO_OUT  0x0600 /* R       Y-axis gyroscope output */
#define ZGYRO_OUT  0x0800 /* R       Z-axis gyroscope output */
#define XACCL_OUT  0x0A00 /* R       X-axis accelerometer output */
#define YACCL_OUT  0x0C00 /* R       Y-axis accelerometer output */
#define ZACCL_OUT  0x0E00 /* R       Z-axis accelerometer output */
#define XMAGN_OUT  0x1000 /* R       X-axis magnetometer measurement */
#define YMAGN_OUT  0x1200 /* R       Y-axis magnetometer measurement */
#define ZMAGN_OUT  0x1400 /* R       Z-axis magnetometer measurement */
#define TEMP_OUT   0x1600 /* R       Temperature output */
#define AUX_ADC    0x1800 /* R       Auxiliary ADC measurement */
#define XGYRO_OFF  0x1A00 /* R/W     X-axis gyroscope bias offset factor */
#define YGYRO_OFF  0x1C00 /* R/W     Y-axis gyroscope bias offset factor */
#define ZGYRO_OFF  0x1E00 /* R/W     Z-axis gyroscope bias offset factor */
#define XACCL_OFF  0x2000 /* R/W     X-axis acceleration bias offset factor */
#define YACCL_OFF  0x2200 /* R/W     Y-axis acceleration bias offset factor */
#define ZACCL_OFF  0x2400 /* R/W     Z-axis acceleration bias offset factor */
#define XMAGN_HIF  0x2600 /* R/W     X-axis magnetometer, hard-iron factor */
#define YMAGN_HIF  0x2800 /* R/W     Y-axis magnetometer, hard-iron factor */
#define ZMAGN_HIF  0x2A00 /* R/W     Z-axis magnetometer, hard-iron factor */
#define XMAGN_SIF  0x2C00 /* R/W     X-axis magnetometer, soft-iron factor */
#define YMAGN_SIF  0x2E00 /* R/W     Y-axis magnetometer, soft-iron factor */
#define ZMAGN_SIF  0x3000 /* R/W     Z-axis magnetometer, soft-iron factor */
#define GPIO_CTRL  0x3200 /* R/W     Auxiliary digital input/output control */
#define MSC_CTRL   0x3400 /* R/W     Miscellaneous control */
#define SMPL_PRD   0x3600 /* R/W     Internal sample period (rate) control */
#define SENS_AVG   0x3800 /* R/W     Dynamic range and digital filter control */
#define SLP_CNT    0x3A00 /* W       Sleep mode control */
#define DIAG_STAT  0x3C00 /* R       System status */
#define GLOB_CMD   0x3E00 /* W       System command */
#define ALM_MAG1   0x4000 /* R/W     Alarm 1 amplitude threshold */
#define ALM_MAG2   0x4200 /* R/W     Alarm 2 amplitude threshold */
#define ALM_SMPL1  0x4400 /* R/W     Alarm 1 sample size */
#define ALM_SMPL2  0x4600 /* R/W     Alarm 2 sample size */
#define ALM_CTRL   0x4800 /* R/W     Alarm control */
#define AUX_DAC    0x4A00 /* R/W     Auxiliary DAC data */
#define PRODUCT_ID 0x5600 /* R */

/*---------------------------------------------------------
TYPES
---------------------------------------------------------*/
struct heli_sensor_state_t
    {
    alt_16 gyroX;
    alt_16 gyroY;
    alt_16 gyroZ;
    alt_16 accelX;
    alt_16 accelY;
    alt_16 accelZ;
    alt_16 magX;
    alt_16 magY;
    alt_16 magZ;
    };

/*---------------------------------------------------------
GLOBAL VARIABLES
---------------------------------------------------------*/
extern struct heli_sensor_state_t currentHeliState;

extern char reg_str[][13];
extern char reg_defaults[][6];

/*---------------------------------------------------------
MACROS
---------------------------------------------------------*/
/*-------------------------------------------
Values obtained from IMU datasheet
-------------------------------------------*/
#define RAW_TO_DPS( gyroData )               ( (float)gyroData / 20.0 )
#define RAW_TO_GRAV( accelData )             ( (float)accelData * 3.33 / 1000.0 )
#define RAW_TO_GAUSS( magData )              ( (float)magData / 2000.0 )

#define RAW_TO_RPS( gyroData )               ( (float)gyroData / 20.0*3.1416/180)

/*---------------------------------------------------------
PROCEDURES
---------------------------------------------------------*/
/* imu.c procedures */
void IMU_reg_display();
void readUsefulIMU();
void calibrate_IMU();

#endif /* IMU_H_ */
