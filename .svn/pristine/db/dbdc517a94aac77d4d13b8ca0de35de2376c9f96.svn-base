#ifndef MCTSTRUCTURES_H
#define MCTSTRUCTURES_H

#include <sys/time.h>

/** @brief Enumerator for the state of a class or module.
  * @details A lot of classes may want to keep track of a state.
  *          We can try to use this as a universal enumerator for
  *          keeping track of a classes state.
  */
enum STATE
{
    STATE_IDLE,
    STATE_STARTED
};

/** @brief Mulitpurpose use structure for storing positioning info.
  * @details Use this as a universal structure to store one or more of the contained values.
  */
typedef struct {
    double x;
    double y;
    double z;
    double heading;
    double pitch;
    double yaw;
    double roll;
}Position;

/** @deprecated Try to use Position.
  * @brief Structure storing position info.
  */
typedef struct {
    double latitude;
    double longitude;
    double altitude;
    double GPSlat;
    double GPSlong;
    double GPSalt;
}MCTposition;

/** @deprecated Try to use Position.
  * @brief Structure storing orientation info.
  */
typedef struct {
    double pitch;
    double roll;
    double throttle;
}MCTorientation;

/** @deprecated Try to use Position.
  * @brief Structure storing position, orientation, and heading info.
  */
typedef struct {
    MCTposition position;
    MCTorientation orientation;
    double direction;
}MCTstatus;

typedef struct {
    double Kp;
    double Ki;
    double Kd;
    double Kf;
    double Kt;
}MCTPID;

typedef struct {
    double err;
    double preverr;
    double prevI;
    double prevD;
    double correction;
    timespec mark;
}MCTPIDERR;

typedef struct {
    MCTPID roll;
    MCTPID pitch;
    MCTPID yaw;
    MCTPID altitude;
    MCTPID longitude;
    MCTPID latitude;
}MCTUAV;


#endif // MCTSTRUCTURES_H

