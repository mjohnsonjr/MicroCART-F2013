#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//basically, this code should follow almost line for line from Matlab Kalman filter.

	//no idea how to set this up.  not sure what format the data is coming in.
	//should take arguments dt, p, q, r, fx, fy, fz
	//run Kalman_2014_init  if it is the first time through
	//run Kalman_2014 which saves phi theta psi as pointers
	
	float H[4][4];
	float Q[4][4];
	float R[4][4];
	float x[4][1];
	float P[4][4];
	float phi;
	float theta;
	float psi;
	char initializeFlag = 0;

//checked
//initialize persistent variables used in EulerKalman
void Kalman_init(){


	initIdentityMat(H, 4, 4, 1); 
	initIdentityMat(Q, 4, 4, .0003);
	initIdentityMat(R, 4, 4, .67);
	initIdentityMat(x, 4, 1, 1);
	initIdentityMat(P, 4, 4, 1); 
/*
	H[4][4]	= { {1,0,0,0},
					  {0,1,0,0},
					  {0,0,1,0},
					  {0,0,0,1} };
					  

	Q[4][4] = { {.0003,0,0,0},
					  {0,.0003,0,0},
					  {0,0,.0003,0},
					  {0,0,0,.0003} };
	
	R[4][4] = { {.67,0,0,0},
					  {0,.67,0,0},
					  {0,0,.67,0},
					  {0,0,0,.67} };
	
	x[4][1] = {1,0,0,0};
	
	P[4][4] = { {1,0,0,0},
					  {0,1,0,0},
					  {0,0,1,0},
					  {0,0,0,1} };
					  */
}

//checked
//start of Kalman Filter. calls all functions unsed except for initialized
// outputOrientation is an array of pitch roll yaw values
// dt is delta time
// p,q,r are the gyroscope outputs
// ax,ay,az are the accelerometer outputs
void Kalman_getOrientation(float* outputOrientation, float dt, float p, float q, float r, float ax, float ay, float az){
	float z[4][1];
	float A[4][4];
	float theta_a = 0; 
	float phi_a = 0;
	float psi_a = 0;
	float phi = 0;
	float theta = 0;
	float psi = 0;

	dt = dt*.001;
	p = p*3.1415/180;
	q = q*3.1415/180;
	r = r*3.1415/180;
	if(initializeFlag == 0)
	{
		Kalman_init();
		initializeFlag = 1;
	}
//setup data for Euler Kalman algorithm
	Kalman_calcA(A, dt, p, q, r);   
	Kalman_eulerAccel(&phi_a, &theta_a, ax, ay, az); //done
	Kalman_eulerToQuaternion(z, phi_a, theta_a, psi_a);  //done

//perform Kalman filter algorithm
	Kalman_eulerKalman(&phi, &theta, &psi, A, z); 

	outputOrientation[0] = phi;
	outputOrientation[1] = theta;
	outputOrientation[2] = psi;

}

///start private functions

void Kalman_eulerKalman(float A, float z){
	float K[4][4];
	float Pp[4][4];
	float xp[4][1];
	float A_trans[4][4];
	float H_trans[4][4];

	Matrix_transpose(A_trans, A);
	Matrix_transpose(H_trans, H);
	
	Kalman_calcxp(xp, A, x);            
	Kalman_calcPp(Pp, A, P, A_trans, Q);		
	Kalman_calculateK(K, Pp, H_trans, H, R);				
	Kalman_calcx(x, xp, K, z, H);						
	Kalman_calcP(P, Pp, K, H);						
	Kalman_calcPhiThetaPsi(P, Pp, K, H);				
}

//checked - needs editing
//outputs: A
//inputs dt, p, q, r
void Kalman_calcA(float** A, float dt, float p, float q, float r){
	
	//EDIT: copy from nates
	A = { {1,-p*.5*dt,-q*.5*dt,-r*.5*dt},
					  {p*.5*dt,1,r*.5*dt,-q*.5*dt},
					  {q*.5*dt,-r*.5*dt,1,p*dt},
					  {r*.5*dt,q*.5*dt,-p*.5*dt,1} };
}

//checked
//outputs:phi_a, theta_a
//inputs ax, ay, az
void Kalman_accelEst(float** phi_a, float** theta_a, float ax, float ay, float az){
	*theta_a = (float) 0 - atan((double) ax/sqrt(ay*ay+ az*az)); //output in radians
    *phi_a = (float) atan((double) ay/sqrt(ax*ax + az*az));  //outputs in radians
 
}

//checked
//outputs: z
//inputs: phi_a, theta_a,  psi_a
void KALMANFILTER_eulerToQuaternion(float** z, float phi_a, float theta_a, float psi_a) {

	float sin_phi;
	float sin_theta;
	float sin_psi;
	float cos_phi;
	float cos_theta;
	float cos_psi;

	sin_phi   = (float) sin((double) phi_a/2);
	sin_theta = (float) sin((double) theta_a/2);
	sin_psi   = (float) sin((double) psi_a/2);
	cos_phi   = (float) cos((double) phi_a/2);
	cos_theta = (float) cos((double) theta_a/2);
	cos_psi   = (float) cos((double) psi_a/2);

	z[0] = cos_phi*cos_theta*cos_psi + sin_phi*sin_theta*sin_psi;
	z[1] = sin_phi*cos_theta*cos_psi - cos_phi*sin_theta*sin_psi;
	z[2] = cos_phi*sin_theta*cos_psi + sin_phi*cos_theta*sin_psi;
	z[3] = cos_phi*cos_theta*sin_psi - sin_phi*sin_theta*cos_psi;

}

//********functions for eulerKalman**********

//checked
//outputs: x
//inputs: xp, K, z, H
void Kalman_calcxp(float** x, float** xp, float** K, float** z, float** H) {
	//xp = A*x;
	MatrixMultiply(xp, A, x, 4, 4, 4, 1);

}
//checked
//outputs: Pp
//inputs: A, P,A_trans, Q
void Kalman_calcPp(float** Pp, float** A, float** P, float** A_trans, float** Q){
	//Pp = A*P*A' + Q;
	
	float Pp_part1[4][4];
	float Pp_part2[4][4];

	MatrixMultiply(Pp_part1, A, P); 		 //write
	MatrixMultiply(Pp_part2, Pp_part1, A_trans); 
	MatrixAdd(Pp, Pp_part2, Q); 			//write

}

//checked
//output: K[][]
//input: Pp, H_trans, H, R
void Kalman_calcK(float** K, float** Pp, float** H_trans, float** H, float** R) {
	//K = Pp*H'/(H*Pp*H'+R);
	float K_part1[4][4];
	float K_part2[4][4];
	float K_part3[4][4];
	float K_part4[4][4];
	float K_part4_inv[4][4];

	MatrixMultiply(K_part1, Pp, H_trans);
	MatrixMultiply(K_part2, H, Pp);
	MatrixMultiply(K_part3, K_part2, H_trans);
	MatrixAdd(K_part4, K_part3, R);
	MatrixInverse(K_part4_inv, K_part4);			//write
	MatrixMultiply(K, K_part1, K_part4_inv);
	//FOR TESTING: Array Output
	printf("K: \n%.01f, %.01f, %.01f, %.01f\n%.01f, %.01f, %.01f, %.01f\n
		%.01f, %.01f, %.01f, %.01f\n%.01f, %.01f, %.01f, %.01f\n", 
		K[0][0],K[0][1],K[0][2],K[0][3],
		K[1][0],K[1][1],K[1][2],K[1][3],
		K[2][0],K[2][1],K[2][2],K[2][3],
		K[3][0],K[3][1],K[3][2],K[3][3]);

}

//outputs x
//inputs xp K z H
void Kalman_calcx(float** x, float** xp, float** K, float** z, float** H) {
	//x = xp + K*(z-H*xp);

	float x_part1[4][4];
	float x_part2[4][4];
	float x_part3[4][4];
	
	MatrixMultiply(x_part1, H, xp);
	MatrixSubtract(x_part2, z, x_part1);			//write
	MatrixMultiply(x_part3, K, x_part2);
	MatrixAdd(x, xp, x_part3);

}
//outputs P
//inputs: Pp, K, H
void Kalman_calcP(float** P, float** Pp, float** K, float** H) {
	//P = Pp - K*H*Pp;

	float P_part1[4][4];
	float P_part2[4][4];
	
	MatrixMultiply(P_part1, K, H);
	MatrixMultiply(P_part2, P_part1, Pp);
	MatrixSubtract(P, Pp, P_part2);

}
//outputs: phi, theta, psi
//inputs x
int Kalman_calcPhiThetaPsi(float** phi, float** theta, float** psi, float** x) {
	//phi   =  atan2(2*(x(3)*x(4)+x(1)*x(2)), 1-2*(x(2)^2 + x(3)^2));
	//theta = -asin(2*(x(2)*x(4)-x(1)*x(3)) );
	//psi   =  atan2(2*(x(2)*x(3)+x(1)*x(4)), 1-2*(x(3)^2 + x(4)^2));

	float phi1;
	float phi2;
	float theta1;
	float psi1;
	float psi2;

	phi1 = 2*(x[3][1] * x[4][1] + x[1][1] * x[2][1]);
	phi2 = 1 - 2*(x[2][1] * x[2][1] + x[3][1] * x[3][1]);

	theta1 = 2*(x[2][1] * x[4][1] - x[1][1] * x[3][1]);

	psi1 = 2*(x[2][1] * x[3][1] + x[1][1] * x[4][1]);
	psi2 = 1 - 2*(x[3][1] * x[3][1]) + x[4][1] * x[4][1]);

	*phi = (float) atan2(phi1, phi2);
	*theta = (float) 0 - asin((float)theta1);
	*psi = (float) atan2(psi1, psi2);

	return 1;

}

//fills matrix with values such that it is an identity matrix 
void createIdentityMat(float** matrix, int numRows, int numCols, float value)
{
	int i = 0;
	int j = 0;

	//matrix must be square
	if(rows != cols)
	{
		return 0;
	}
	
	for(i = 0; i < numRows; i++)
	{
		for(j = 0; j < numCols; j++)
		{
			if(i == j)
			{
				matrix[i][j] = value;
			}	
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
}






