///*---------------------------------------------------------
// File: labet_main_kalman.c
//
// Procedures:
// - main
// - PredictAccG_pitch
// - PredictAccG_roll
// --------------------------------------------------------*/
//
///*---------------------------------------------------------
// INCLUDES
// ---------------------------------------------------------*/
//#include <system.h>
//#include <stdarg.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <stddef.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <math.h>
//#include <sys/alt_timestamp.h>
//#include <alt_types.h>
//#include <sys/time.h>
//#include "hello_world.h"
//#include "labet.h"
//#include "imu.h"
//#include "ars.h"
//#include "ping.h"
//#include "controls.h"
//
//
////#include "kalmanfilter.h"
///*---------------------------------------------------------
// DEFINITIONS
// ---------------------------------------------------------*/
//#define SIZE_OF_DATA_PACKET 56
//#define GYR_CMPF_FACTOR 300
//#define INV_GYR_CMPF_FACTOR (1/(GYR_CMPF_FACTOR+1))
//#define GYRO_SCALE (4 / 20.0 * PI / 180.0 / 1000000.0)
//#define ACC_LPF_FACTOR 4
//#define ACC_1G 256
//#define ROLL 0
//#define PITCH 1
//#define YAW 2
///*---------------------------------------------------------
// TYPES
// ---------------------------------------------------------*/
//typedef struct fp_vector {
//  float X,Y,Z;
//} t_fp_vector_def;
//
//typedef union {
//  float A[3];
//  t_fp_vector_def V;
//} t_fp_vector;
//
//typedef struct int32_t_vector {
//  unsigned int X,Y,Z;
//} t_int32_t_vector_def;
//
//typedef union {
//  unsigned int A[3];
//  t_int32_t_vector_def V;
//} t_int32_t_vector;
//typedef struct {
//  unsigned short angle[2];            // absolute angle inclination in multiple of 0.1 degree    180 deg = 1800
//  unsigned short heading;             // variometer in cm/s
//} att_t;
//
//static t_fp_vector EstG;
//static t_int32_t_vector EstG32;
//static unsigned int accLPF32[3]    = {0, 0, 1};
//static float invG; // 1/|G|
//extern att_t att;
//
//
//unsigned short _atan2(unsigned int y, unsigned int x){
//  float z = (float)y / x;
//  unsigned short a;
//  if ( fabs(y) < fabs(x) ){
//     a = 573 * z / (1.0f + 0.28f * z * z);
//   if (x<0) {
//     if (y<0) a -= 1800;
//     else a += 1800;
//   }
//  } else {
//   a = 900 - 573 * z / (z * z + 0.28f);
//   if (y<0) a -= 1800;
//  }
//  return a;
//}
//float sq (float x){
//	return x*x;
//}
//float InvSqrt (float x){
//  union{
//    unsigned int i;
//    float   f;
//  } conv;
//  conv.f = x;
//  conv.i = 0x5f3759df - (conv.i >> 1);
//  return 0.5f * conv.f * (3.0f - x * conv.f * conv.f);
//}
//
//// Rotate Estimated vector(s) with small angle approximation, according to the gyro data
//void rotateV(struct fp_vector *v,float* delta) {
//  struct fp_vector v_tmp = *v;
//  v->Z -= delta[ROLL]  * v_tmp.X + delta[PITCH] * v_tmp.Y;
//  v->X += delta[ROLL]  * v_tmp.Z - delta[YAW]   * v_tmp.Y;
//  v->Y += delta[PITCH] * v_tmp.Z + delta[YAW]   * v_tmp.X;
//}
//
//
////ESTIMATE PITCH/ROLL FROM MULTIWII
//void getEstimatedAttitude(){
//  unsigned char axis;
//  int accMag = 0;
//  float scale, deltaGyroAngle[3];
//  unsigned char validAcc;
//  static alt_timestamp_type previousT;
//  unsigned int accSmooth[3];
//  alt_timestamp_type currentT = alt_timestamp();
//  scale = (currentT - previousT)*.02 * GYRO_SCALE; // Convert from clks to us.  GYRO_SCALE unit: radian/microsecond
//  previousT = currentT;
//  readUsefulIMU();
//  // Initialization
//  deltaGyroAngle[0] = currentHeliState.gyroX  * scale; // radian
//  deltaGyroAngle[1] = currentHeliState.gyroY  * scale; // radian
//  deltaGyroAngle[2] = currentHeliState.gyroZ  * scale; // radian
//  accLPF32[0]    -= accLPF32[0]>>ACC_LPF_FACTOR;
//  accLPF32[1]    -= accLPF32[1]>>ACC_LPF_FACTOR;
//  accLPF32[2]    -= accLPF32[2]>>ACC_LPF_FACTOR;
//  accLPF32[0]    += currentHeliState.accelX;
//  accLPF32[1]    += currentHeliState.accelY;
//  accLPF32[2]    += currentHeliState.accelZ;
//  for (axis = 0; axis < 3; axis++) {
//    accSmooth[axis]    = accLPF32[axis]>>ACC_LPF_FACTOR;
//    accMag += (int)accSmooth[axis]*accSmooth[axis];
//  }
//
//  rotateV(&EstG.V,deltaGyroAngle);
//
//  accMag = accMag*100/((int)ACC_1G*ACC_1G);
//  validAcc = 72 < (unsigned short)accMag && (unsigned short)accMag < 133;
//  // Apply complimentary filter (Gyro drift correction)
//  // If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range => we neutralize the effect of accelerometers in the angle estimation.
//  // To do that, we just skip filter, as EstV already rotated by Gyro
//  for (axis = 0; axis < 3; axis++) {
//    if ( validAcc )
//      EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
//      EstG32.A[axis] = EstG.A[axis]; //int32_t cross calculation is a little bit faster than float
//  }
//
//  /*if ((short)EstG32.A[2] > ACCZ_25deg)
//    f.SMALL_ANGLES_25 = 1;
//  else
//    f.SMALL_ANGLES_25 = 0;
//*/
//  // Attitude of the estimated vector
//  int sqGX_sqGZ = sq(EstG32.V.X) + sq(EstG32.V.Z);
//  invG = InvSqrt(sqGX_sqGZ + sq(EstG32.V.Y));
//  att.angle[ROLL]  = _atan2(EstG32.V.X , EstG32.V.Z);
//  att.angle[PITCH] = _atan2(EstG32.V.Y , InvSqrt(sqGX_sqGZ)*sqGX_sqGZ);
//
//}
