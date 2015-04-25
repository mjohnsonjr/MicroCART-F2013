#include "kalmanfilter.h"

//Set this to 1 to show debugging information.
//Every function will print it's input argument matrices
//At the end of the kalman filter iteration, print all the state matrices.
#define debug 0

//------------------//
// Public Functions //
//------------------//

extern int KALMANFILTER_init() {
	float temp_H[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	memcpy(H, temp_H, sizeof(H));

	float temp_x[4] = {1,0,0,0};
	memcpy(x, temp_x, sizeof(x));

	float temp_P[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	memcpy(P, temp_P, sizeof(P));

	float temp_I[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	memcpy(I, temp_I, sizeof(I));

	float	temp_Q[16] = {Q_factor,0,0,0,0,Q_factor,0,0,0,0,Q_factor,0,0,0,0,Q_factor};
	memcpy(Q, temp_Q, sizeof(Q));

	float temp_R[16] = {R_factor,0,0,0,0,R_factor,0,0,0,0,R_factor,0,0,0,0,R_factor};
	memcpy(R, temp_R, sizeof(R));

	phi   = 0;
	theta = 0;
	psi   = 0;
	return 1;
}

extern int KALMANFILTER_update(float t, float p, float q, float r, float ax, float ay, float az) {
	#if debug == 1
	printf("inputs ==========\n");
	printf("      t: %.2f\n", t);
	printf("      p: %.2f\n", p);
	printf("      q: %.2f\n", q);
	printf("      r: %.2f\n", r);
	printf("      ax: %.2f\n", ax);
	printf("      ay: %.2f\n", ay);
	printf("      az: %.2f\n", az);
	#endif

	KALMANFILTER_convert(t, p, q, r, ax, ay, az);

	#if debug == 1
	printf("printState ==========\n");
	printf("      H:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7], H[8], H[9], H[10], H[11], H[12], H[13], H[14], H[15]);
	printf("      x:  %e\t%e\t%e\t%e\n", x[0], x[1], x[2], x[3], x[4]);
	printf("      P:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",P[0], P[1], P[2], P[3], P[4], P[5], P[6], P[7], P[8], P[9], P[10], P[11], P[12], P[13], P[14], P[15]);
	printf("      I:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",I[0], I[1], I[2], I[3], I[4], I[5], I[6], I[7], I[8], I[9], I[10], I[11], I[12], I[13], I[14], I[15]);
	printf("      Q:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",Q[0], Q[1], Q[2], Q[3], Q[4], Q[5], Q[6], Q[7], Q[8], Q[9], Q[10], Q[11], Q[12], Q[13], Q[14], Q[15]);
	printf("      R:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",R[0], R[1], R[2], R[3], R[4], R[5], R[6], R[7], R[8], R[9], R[10], R[11], R[12], R[13], R[14], R[15]);
	printf("      phi: %e\n", phi);
	printf("      theta: %e\n", theta);
	printf("      psi: %e\n", psi);
	#endif
	return 1;
}

extern int KALMANFILTER_getData(float* roll, float* pitch, float* yaw) {
	*roll = phi;
	*pitch = theta;
	*yaw = psi;
	return 1;
}

//------------------//
// Private Funcions //
//------------------//

int KALMANFILTER_convert(float t, float p, float q, float r, float ax, float ay, float az) {
	float z[4];
	float A[16]; //A[4][4]
	float phi_est;
	float theta_est;

	// Normalize sensor inputs
	t = t * 0.0001;
	p = p * (pi/(180*20));
	q = q * (pi/(180*20));
	r = r * (pi/(180*20));
	ax = ax * ((-1*1*3.33)/1000);
	ay = ay * ((-1*1*3.33)/1000);
	az = az * ((1*3.33)/1000); //Used for yaw calculations

	//A = eye(4) + t*1/2*[0 -p -q -r; p 0 r -q; q -r 0 p; r q -p 0];
	KALMANFILTER_calculateA(A, t, p, q, r);

	//Estimate roll and pitch using accelerometer readings
	KALMANFILTER_eulerAccel(&phi_est, &theta_est, ax, ay, az);

	//Get measurement z from Complex Algorithm(tm).
	//We have assumed yaw estimate to be zero for now
	KALMANFILTER_eulerToQuaternion(z, phi_est, theta_est, 0);

	//Calculate the output values of phi theta and psi
	KALMANFILTER_eulerKalman(&phi, &theta, &psi, A, z);

	return 1;
}

int KALMANFILTER_eulerKalman(float* phi, float* theta, float* psi, float* A, float* z) {
	//Argument Sizes
	//phi
	//theta
	//psi
	//A[4][4]
	//z[1][4]

	float K[16];  //K[4][4]
	float Pp[16]; //Pp[4][4]
	float xp[4];  //xp[4][1]
	float A_[16]; //A_[4][4]
	float H_[16]; //H_[4][4]

	MATRIXMATH_transpose(A_, A, 4, 4);
	MATRIXMATH_transpose(H_, H, 4, 4);//As long as H is an identity matrix H = H_

	//xp = A * x
	KALMANFILTER_calculatexp(xp, A, x);

	//Pp = A * P * A' + Q
	KALMANFILTER_calculatePp(Pp, A, P, A_, Q);

	//K = Pp * H' * inv(H*Pp*H' + R)
	KALMANFILTER_calculateK(K, Pp, H_, H, R);

	//x = xp + K*(z - H*xp);
	KALMANFILTER_calculatex(x, xp, K, z, H);

	//P = Pp - K*H*Pp;
	KALMANFILTER_calculateP(P, Pp, K, H);

	KALMANFILTER_calculatePhiThetaPsi(phi, theta, psi, x);

	return 1;
}

int KALMANFILTER_eulerToQuaternion(float* z, float phi_est, float theta_est, float psi_est) {
	//Argument Sizes
	//z[4][1]
	//phi_est
	//theta_est
	//psi_est

	float sin_phi;
	float sin_theta;
	float sin_psi;
	float cos_phi;
	float cos_theta;
	float cos_psi;

	sin_phi   = (float) sin(phi_est/2);
	sin_theta = (float) sin(theta_est/2);
	sin_psi   = (float) sin(psi_est/2);
	cos_phi   = (float) cos(phi_est/2);
	cos_theta = (float) cos(theta_est/2);
	cos_psi   = (float) cos(psi_est/2);

	z[0] = cos_phi*cos_theta*cos_psi + sin_phi*sin_theta*sin_psi;
	z[1] = sin_phi*cos_theta*cos_psi - cos_phi*sin_theta*sin_psi;
	z[2] = cos_phi*sin_theta*cos_psi + sin_phi*cos_theta*sin_psi;
	z[3] = cos_phi*cos_theta*sin_psi - sin_phi*sin_theta*cos_psi;

	#if debug == 1
	printf("z ==========\n");
	printf("  out z: %e\t%e\t%e\t%e\n", z[0], z[1], z[2], z[3]);
	printf("  in  phi_est: %e\n", phi_est);
	printf("  in  theta_est: %e\n", theta_est);
	printf("  in  psi_est: %e\n", psi_est);
	#endif
	return 1;
}

int KALMANFILTER_eulerAccel(float* phi_est, float* theta_est, float ax, float ay, float az) {
	//Argument Sizes
	//phi_est
	//theta_est
	//ax
	//ay
	float temp;

	*theta_est = atan(ax / sqrt(ay*ay+az*az));
	*phi_est = -atan(ay / sqrt(ax*ax+az*az));

	//temp = (float) asin(ax/g);
	//*theta_est = temp;
	//*phi_est   = (float) asin( -ay/(g*cos(temp)));

	#if debug == 1
	printf("eulerAccel ==========\n");
	printf("  out phi_est: %e\n", *phi_est);
	printf("  out theta_est: %e\n", *theta_est);
	printf("  in  ax: %e\n", ax);
	printf("  in  ay: %e\n", ay);
	#endif
	return 1;
}

int KALMANFILTER_calculatexp(float* xp, float* A, float* x) {
	//Argument Sizes
	//xp[4][1]
	//A[4][4]
	//x[4][1]

	MATRIXMATH_multiply(xp, A, x, 4, 1);

	#if debug == 1
	printf("xp ==========\n");
	printf("  out xp: %e\t%e\t%e\t%e\n",xp[0], xp[1], xp[2], xp[3]);
	printf("  in  A:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[8], A[9], A[10], A[11], A[12], A[13], A[14], A[15]);
	printf("  in  x:  %e\t%e\t%e\t%e\n",x[0], x[1], x[2], x[3]);
	#endif
	return 1;
}

int KALMANFILTER_calculateA(float* A, float t, float p, float q, float r) {
	//Matlab equivilent code
	//A = eye(4) + t*1/2*[0 -p -q -r;
	//                    p  0  r -q;
	//                    q -r  0  p;
	//                    r  q -p  0]

	//Argument Sizes
	//A[4][4]
	//t
	//p
	//q
	//r
	float n;

	n = t*0.5;
	A[0]  = 1;
	A[1]  = -p*n;
	A[2]  = -q*n;
	A[3]  = -r*n;
	A[4]  = p*n;
	A[5]  = 1;
	A[6]  = r*n;
	A[7]  = -q*n;
	A[8]  = q*n;
	A[9]  = -r*n;
	A[10] = 1;
	A[11] = p*n;
	A[12] = r*n;
	A[13] = q*n;
	A[14] = -p*n;
	A[15] = 1;

	#if debug == 1
	printf("A ==========\n");
	printf("  out A:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[8], A[9], A[10], A[11], A[12], A[13], A[14], A[15]);
	printf("  in  t: %e\n", t);
	printf("  in  p: %e\n", p);
	printf("  in  q: %e\n", q);
	printf("  in  r: %e\n", r);
	#endif
	return 1;
}

int KALMANFILTER_calculatePp(float* Pp, float* A, float* P, float* A_, float* Q) {
	//Matlab equivilent code
	//Pp = (A * P) * A' + Q

	//Argument Sizes
	//pP[4][4]
	//A[4][4]
	//P[4][4]
	//A_[4][4]
	//Q[4][4]
	float temp1[16];
	float temp2[16];

	MATRIXMATH_multiply(temp1, A, P, 4, 4);
	MATRIXMATH_multiply(temp2, temp1, A_, 4, 4);
	MATRIXMATH_add(Pp, temp2, Q, 4, 4);

	#if debug == 1
	printf("Pp ==========\n");
	printf("  out Pp:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",Pp[0], Pp[1], Pp[2], Pp[3], Pp[4], Pp[5], Pp[6], Pp[7], Pp[8], Pp[9], Pp[10], Pp[11], Pp[12], Pp[13], Pp[14], Pp[15]);
	printf("  in  A:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",A[0], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[8], A[9], A[10], A[11], A[12], A[13], A[14], A[15]);
	printf("  in  P:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",P[0], P[1], P[2], P[3], P[4], P[5], P[6], P[7], P[8], P[9], P[10], P[11], P[12], P[13], P[14], P[15]);
	printf("  in  A_:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",A_[0], A_[1], A_[2], A_[3], A_[4], A_[5], A_[6], A_[7], A_[8], A_[9], A_[10], A_[11], A_[12], A_[13], A_[14], A_[15]);
	printf("  in  Q:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",Q[0], Q[1], Q[2], Q[3], Q[4], Q[5], Q[6], Q[7], Q[8], Q[9], Q[10], Q[11], Q[12], Q[13], Q[14], Q[15]);
	#endif
	return 1;
}

int KALMANFILTER_calculateK(float* K, float* Pp, float* H_, float* H, float* R) {
	//Matlab equivilent code
	//K = Pp*H_*inv(H*Pp*H_ + R)
	//K = Pp*inv(Pp+R)

	//Argument Sizes
	//K[4][4]
	//Pp[4][4]
	//H_[4][4]
	//H[4][4]
	//R[4][4]
	float temp1[16]; //temp1[4][4]
	float temp2[16]; //temp2[4][4]
	//float temp3[16]; //temp2[4][4]
	//float temp4[16]; //temp2[4][4]
	//float temp5[16]; //temp2[4][4]

	MATRIXMATH_add(temp1, Pp, R, 4, 4);
	MATRIXMATH_inverse4x4(temp2, temp1);
	MATRIXMATH_multiply(K, Pp, temp2, 4, 4);

	//MATRIXMATH_multiply(temp1, H, Pp, 4, 4);//Bad if H is eye(4)
	//MATRIXMATH_multiply(temp2, temp1, H_, 4, 4);//Bad if H_ is eye(4)
	//MATRIXMATH_add(temp3, temp2, R, 4 ,4);
	//MATRIXMATH_inverse4x4(temp4, temp3);
	//MATRIXMATH_multiply(temp5, Pp, H_, 4, 4);//Bad if H_ is eye(4)
	//MATRIXMATH_multiply(K, temp5, temp4, 4, 4);

	#if debug == 1
	printf("K ==========\n");
	printf("  out K:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",K[0], K[1], K[2], K[3], K[4], K[5], K[6], K[7], K[8], K[9], K[10], K[11], K[12], K[13], K[14], K[15]);
	printf("  in  H_:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",H_[0], H_[1], H_[2], H_[3], H_[4], H_[5], H_[6], H_[7], H_[8], H_[9], H_[10], H_[11], H_[12], H_[13], H_[14], H_[15]);
	printf("  in  Pp:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",Pp[0], Pp[1], Pp[2], Pp[3], Pp[4], Pp[5], Pp[6], Pp[7], Pp[8], Pp[9], Pp[10], Pp[11], Pp[12], Pp[13], Pp[14], Pp[15]);
	#endif
	return 1;
}

int KALMANFILTER_calculateP(float* P, float* Pp, float* K, float* H) {
	//Matlab equivilent code
	//P = Pp - K*H*Pp;
	//H is the identity matrix
	//We simplify the equation to P = Pp - K*Pp

	//Argument Sizes
	//P[4][4]
	//Pp[4][4]
	//K[4][4]
	//H[4][4]
	float temp1[16]; //temp1[4][4]

	MATRIXMATH_multiply(temp1, K, Pp, 4, 4);
	MATRIXMATH_subtract(P, Pp, temp1, 4, 4);

	#if debug == 1
	printf("P ==========\n");
	printf("  out P:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",P[0], P[1], P[2], P[3], P[4], P[5], P[6], P[7], P[8], P[9], P[10], P[11], P[12], P[13], P[14], P[15]);
	printf("  in  Pp: %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",Pp[0], Pp[1], Pp[2], Pp[3], Pp[4], Pp[5], Pp[6], Pp[7], Pp[8], Pp[9], Pp[10], Pp[11], Pp[12], Pp[13], Pp[14], Pp[15]);
	printf("  in  K:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",K[0], K[1], K[2], K[3], K[4], K[5], K[6], K[7], K[8], K[9], K[10], K[11], K[12], K[13], K[14], K[15]);
	#endif
	return 1;
}

int KALMANFILTER_calculatex(float* x, float* xp, float* K, float* z, float* H) {
	//Matlab equivilent code
	//x = xp + K*(z - H*xp)
	//x = xp + K*(z-xp)

	//Argument Sizes
	//x[4][1]
	//xp[4][1]
	//K[4][4]
	//z[4][1]
	//H[4][4]
	float temp1[4]; //temp1[4][1]
	float temp2[4]; //temp2[4][1]

	MATRIXMATH_subtract(temp1, z, xp, 4, 1);
	MATRIXMATH_multiply(temp2, K, temp1, 4, 1);
	MATRIXMATH_add(x, xp, temp2, 4, 1);

	#if debug == 1
	printf("x ==========\n");
	printf("  out x:  %e\t%e\t%e\t%e\n",x[0], x[1], x[2], x[3]);
	printf("  in  xp: %e\t%e\t%e\t%e\n",xp[0], xp[1], xp[2], xp[3]);
	printf("  in  K:  %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n          %e\t%e\t%e\t%e\n",K[0], K[1], K[2], K[3], K[4], K[5], K[6], K[7], K[8], K[9], K[10], K[11], K[12], K[13], K[14], K[15]);
	printf("  in  z:  %e\t%e\t%e\t%e\n",z[0], z[1], z[2], z[3], z[4]);
	#endif
	return 1;
}

int KALMANFILTER_calculatePhiThetaPsi(float* phi, float* theta, float* psi, float* x) {
	//Argument Sizes
	//phi
	//theta
	//psi
	//x[4][1]

	float temp1;
	float temp2;
	float temp3;
	float temp4;
	float temp5;

	// Calculate phi
	// phi = atan2(2*real((x(3)*x(4) + x(1)*x(2))), real(1 - 2*(x(2)^2 + x(3)^2)));
		temp1 = 2 * (x[2]*x[3] + x[0]*x[1]);
		temp2 = 1 - (2*(    x[1]*x[1] + x[2]*x[2]    ));
	*phi = (float) atan2(temp1, temp2);

	// Calculate theta
	// theta = -asin(2*(x(2)*x(4) - x(1)*x(3)));
		temp3 = 2 *(x[1]*x[3] - x[0]*x[2]);
	*theta = (float) 0 - asin((float)temp3);

	// Calculate psi
	// psi = atan2(2*real((x(2)*x(3) + x(1)*x(4))), real(1 - 2*(x(3)^2 + x(4)^2)));
		temp4 = 2 * (x[1]*x[2] + x[0]*x[3]);
		temp5 = 1 - (2*(    x[2]*x[2] + x[3]*x[3]    ));
	*psi = (float) atan2(temp4, temp5);
	return 1;
}
