/*
 * estimationtest.h
 *
 *  Created on: Mar 26, 2013
 *      Author: root
 */

float squared(float x);
void normalize3DVector(float* vector);
void getEstimatedInclination();
void setZero(struct MCTPIDERR *pid);
void initializeToZero();
int getCorrections(float *sigCor, float curAlt, float curLon, float curLat, float curPitch, float curRoll, float curDir, float targetDir, float targetAlt, float targetLat, float targetLon, float targetPitch, float targetRoll);
float get_PID_correction(float current, float target, struct MCTPIDERR *err, struct MCTPID pid);
void calc_orientation(float targetPitch, float targetRoll, float targetLat, float curLat, float current_direction, float target_direction, float targetLon, float curLon);
void* readDataThread();
