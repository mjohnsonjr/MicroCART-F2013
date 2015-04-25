#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#define g 9.81
#define pi 3.14159265358
#define Q_factor 0.00003//0.0001 //0.0003
#define R_factor 10//.001 //0.69

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrixmath.h"

/*
	Rough stack diagram for kalman filter functions.
  update
    convert
      calculateA
      eulerAccel
      eulerToQuaternion
      eulerKalman
				calculatexp
				calculatePp
        calculateK
        calculatex
        calculateP
				calculatePhiThetaPsi
*/

//------------------//
// Global Variables //
//----------------- //

static float H[16]; //!H4][4] State to state measurement matrix.
static float x[4];  //!x[1][4] Estimate of the state variable.
static float P[16]; //!P[4][4] Estimate of the error covarience.
static float I[16]; //!I[4][4] Identity Matrix
static float Q[16]; //!Q[4][4] Covarience matrix of wk = state transition noise.
static float R[16]; //!R[4][4] Covarience matrix of vk = measurement noise.
static float phi;   //! Storage for the output data.
static float theta; //! Storage for the output data.
static float psi;   //! Storage for the output data.

//------------------//
// Public Functions //
//------------------//

/** @brief Initializes the kalman filter.
  * @details This must be called to initialize the state matrices.
  * Otherwise they will contains garbage and you will get irrational results.
  * Calling this funciton again resets the kalman filter back to an just-initialized state.
  * @return Always 1;
  */
extern int KALMANFILTER_init();

/** @brief Gets the most recent roll, pitch, and yaw angles calculated by the kalman filter.
  * @details This funciton has no side effects.
  * @param[out] roll
  * @param[out] pitch
  * @param[out] yaw
  * @return Always 1.
  * @todo roll, pitch, and yaw are arbitrarily assigned to psi theta and psi and are probably wrong
	*/
extern int KALMANFILTER_getData(float* pitch, float* roll, float* yaw);

/** @brief Updates the kalman filter with new data and performs a single iteration of calculations
  * @param[in] t
  * @param[in] p
  * @param[in] q
  * @param[in] r
  * @param[in] ax
  * @param[in] ay
  * @param[in] az
  * @return 1 if successful.  0 if any of the three output variables was detected as nan or inf.  The three output variables are phi, theta, and psi corresponding to roll, pitch, and yaw.  When this happens, the kalman filter is corrupted and you should either reinitialise it or terminate the program.
  */
extern int KALMANFILTER_update(float t, float p, float q, float r, float ax, float ay, float az);

//-------------------//
// Private Functions //
//-------------------//

/**
  * @param[in] t
  * @param[in] p
  * @param[in] q
  * @param[in] r
  * @param[in] ax
  * @param[in] ay
  * @param[in] az
  */
int KALMANFILTER_convert(float t, float p, float q, float r, float ax, float ay, float az);

/**
  * @param[out] phi
  * @param[out] theta
  * @param[out] psi
  * @param[in] A
  * @param[in] z
  */
int KALMANFILTER_eulerKalman(float* phi, float* theta, float* psi, float* A, float* z);

/**
  * @param[out] z
  * @param[in] phi
  * @param[in] theta
  * @param[in] psi
  */
int KALMANFILTER_eulerToQuaternion(float* z, float phi, float theta, float psi);

/**
  * @param[out] phi
  * @param[out] theta
  * @param[in] ax
  * @param[in] ay
  */
int KALMANFILTER_eulerAccel(float* phi, float* theta, float ax, float ay, float az);

/**
  * @param[out] xp
  * @param[in] A
  * @param[in] x
  */
int KALMANFILTER_calculatexp(float* xp, float* A, float* x);

/**
  * @param[out] A
  * @param[in] t
  * @param[in] p
  * @param[in] q
  * @param[in] r
  */
int KALMANFILTER_calculateA(float* A, float t, float p, float q, float r);

/**
  * @param[out] Pp
  * @param[in] A
  * @param[in] P
  * @param[in] A_
  * @param[in] Q
  */
int KALMANFILTER_calculatePp(float* Pp, float* A, float* P, float* A_, float* Q);

/**
  * @param[out] K
  * @param[in] H_
  * @param[in] Pp
  */
int KALMANFILTER_calculateK(float* K, float* Pp, float* H_, float* H, float* R);

/**
  * @param[out] P
  * @param[in] Pp
  * @param[in] K
  */
int KALMANFILTER_calculateP(float* P, float* Pp, float* K, float* H);

/**
  * @param[in] xp
  * @param[in] K
  * @param[in] z
  */
int KALMANFILTER_calculatex(float* x, float* xp, float* K, float* z, float* H);

/**
  * @param[out] phi
  * @param[out] theta
  * @param[out] psi
  * @param[in] x
  */
int KALMANFILTER_calculatePhiThetaPsi(float* phi, float* theta, float* psi, float* x);

#endif // KALMANFILTER_H
