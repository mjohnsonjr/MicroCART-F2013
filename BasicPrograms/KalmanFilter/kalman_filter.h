/*
 * total_kalman.h
 *
 *  Created on: Mar 30, 2014
 *      Author: Kevin Engel
 */

// Include guard 
#ifndef TOTAL_KALMAN_H_   
#define TOTAL_KALMAN_H_

// function declaration
	void Kalman_init(void);
	void Kalman_getOrientation(float* outputOrientation, float dt, float p, float q, float r, float ax, float ay, float az);
	void Kalman_calcA(float dt, float p, float q, float r);
	void Kalman_eulerAccel(float ax, float ay, float az);
	void Kalman_eulerToQuaternion(void);
	void Kalman_eulerKalman(void);
	void Kalman_calcxp(void);
	void Kalman_calcPp(void);
	void Kalman_calcK(void);
	void Kalman_calcx(void);
	void Kalman_calcP(void);
	void Kalman_calcPhiThetaPsi(void);
	
#endif
