#ifndef MCTUTILITIES_H
#define MCTUTILITIES_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "MCTStructures.h"

/*---------------------------------------------------------
CONSTANTS
---------------------------------------------------------*/
/** @brief Approximation of PI.
  * @details Change this to a static double.
  */
#define PI 3.14159265
/*---------------------------------------------------------
MACROS
---------------------------------------------------------*/

/** @brief Converts raw gyroscope data to degrees per second.
  * @todo Change these to inline functions.
  */
#define RAW_TO_DPS(gyroData) ((float)gyroData /20.0)

/** @brief Converts raw gyroscope data to radians per second
  * @todo Change these to inline functions.
  */
#define RAW_TO_RPS(gyroData) ((float)gyroData/20.0 * PI/180)

/** @brief Converts raw accelerometer data to g force.
  * @todo Change these to inline functions.
  */
#define RAW_TO_GRAV(accelData) ((float)accelData * 3.33/1000.0)

/** @brief Converts raw magnetometer data to gauss
  * @todo Change these to inline functions.
  */
#define RAW_TO_GAUSS(magData) ((float)magData/2000.0)

/** @brief Finds the minimum of two values.
  * @todo Change these to inline functions.
  */
#define MIN( X, Y ) ( X < Y ? X : Y )

/** @brief Gets the USB port number that corresponds to a specifice device id.
  * @param[in] dev_id The id of the desired device.
  * @return The USB port number that corresponds to the device.
  *         -1 if the device could not be found.
  */
int get_USB_port(std::string dev_id);

/** @deprecated This function is never used.
  * @brief Retrieves the proper constants from the file.
  * @details I don't actually know what this does, and it isn't used anywhere in the code
  *          so I'm just going to deprecate it.
  * @param[in] filename The name of the file to read data from.
  * @return MCTUAV structure containing the constants
  */
MCTUAV read_UAV_model(std::string filename);

/** @deprecated This function is never used.
  * @brief Writes the current constants to the UAV model file
  * @details I don't actually know what this does, and it isn't used anywhere in the code
             so I'm just going to deprecate it.
  * @param[in] filename The name of the file to write the data to.
  * @param[in] model MCTUAV structure containg data to write.
  */
void write_UAV_model(std::string filename, MCTUAV model);

/** @deprecated This function was never implemented.
  */
bool in_UAV_tolerance(MCTposition current, MCTposition target);

/** @brief Checks if a double variable is 'NaN' (Not a number).
  * @return True if 'Nan'.  False otherwise.
  */
bool cus_nancheck( double var );

/** @brief Sets all members of a MCTPIDERR structure to zero.
  * @param[in,out] pid Pointer to a MCTPIDERR structure.
  */
void setZero(MCTPIDERR *pid);

/** @brief Makes pitch and yaw spand from -180 to 180 degrees.
  * @param[in,out] ori Pointer to a MCTorientation structure.
  */
void normalize_Orientation(MCTorientation *ori);

/** @brief Converts from degrees to radians.
  * @param[in] angle Angle in degrees.
  * @return Angle in radians.
  */
double DEG_TO_RAD(double angle);

/** @brief Converts from radians to degrees.
  * @param[in] angle Angle in radians.
  * @return Angle in degrees.
  */
double RAD_TO_DEG(double angle);

/** @brief Converts raw GPS data into a more readable and formatted string.
  * @param[in] coord The raw GPS coordinate.
  * @param[in] lat Format the output string as a latitude value or a longitude value.
  * @return Formatted string representing a raw gps coordinate.
  */
std::string GPS_TO_STRING(double coord, bool lat);

/** @brief Finds the distance between two GPS coordinates and formats the result into a readable string.
  * @param[in] lat_a The latitude of the first GPS coordinate.
  * @param[in] long_a The longitude of the first GPS coordinate.
  * @param[in] lat_b The latitude of the second GPS coordinate.
  * @param[in] long_b The longitude of the second GPS coordinate.
  * @param[in] lat Format the output string as a latitude value or a longitude value.
  * @return Formatted string representing a raw gps coordinate.
  */
std::string DIST_FROM_GPS(double lat_a, double long_a, double lat_b, double long_b, bool lat);

#endif // MCTUTILITIES_H

