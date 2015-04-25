#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix_utils.h"
#include "total_kalman.h"





//basically, this code should follow almost line for line from Matlab Kalman filter.

	//no idea how to set this up.  not sure what format the data is coming in.
	//should take arguments dt, p, q, r, fx, fy, fz
	//run Kalman_2014_init  if it is the first time through
	//run Kalman_2014 which saves phi theta psi as pointers
	
	float** H;// = createMatrix(4,4); //H[4][4];
	float** Q;// = createMatrix(4,4); //Q[4][4];
	float** R;// = createMatrix(4,4); //R[4][4];
	float** x;// = createMatrix(4,1); //x[4][1];
	float** P;// = createMatrix(4,4); //P[4][4];
	
	//desired outputs
	float phi;
	float theta;
	float psi;

	char initializeFlag;
	
	float** z;
	float** A;
	
	float theta_a = 0; 
	float phi_a = 0;
	float psi_a = 0;

	

	float sin_phi;
	float sin_theta;
	float sin_psi;
	float cos_phi;
	float cos_theta;
	float cos_psi;

	float** K_part1; //K_part1[4][4];
	float** K_part2; //K_part2[4][4];
	float** K_part3; //K_part3[4][4];
	float** K_part4; //K_part4[4][4];
	float** K_part4_inv; //K_part4_inv[4][4];


	float** K; //K[4][4];
	float** Pp; //Pp[4][4];
	float** xp; //xp[4][1];
	float** A_trans; //A_trans[4][4];
	float** H_trans; //H_trans[4][4];

	//used in calcPhiThetaPsi
	float phi1;
	float phi2;
	float theta1;
	float psi1;
	float psi2;

	//kalmanCalcP
	float** P_part1; //P_part1[4][4];
	float** P_part2; //P_part2[4][4];

	float** Pp_part1; //Pp_part1[4][4];
	float** Pp_part2; //Pp_part2[4][4];

	float** x_part1; //x_part1[4][1];
	float** x_part2; //x_part2[4][1];
	float** x_part3; //x_part3[4][1];


//checked
//initialize persistent variables used in EulerKalman
void Kalman_init(void){


	H = createIdentityMatrix(4,4,1.0);  
	Q = createIdentityMatrix(4,4,.0003);
	R = createIdentityMatrix(4,4,.67);
	x = createIdentityMatrix(4,1,1.0);
	P = createIdentityMatrix(4,4,1.0);
	
	initializeFlag = 0;

	//
	z = createMatrix(4,1);//z[4][1];
	A = createMatrix(4,4);//A[4][4];

	//
	K_part1 = createMatrix(4,4); //[4][4];
	K_part2 = createMatrix(4,4); //[4][4];
	K_part3 = createMatrix(4,4); //[4][4];
	K_part4 = createMatrix(4,4); //[4][4];
	K_part4_inv = createMatrix(4,4); //[4][4];

	K = createMatrix(4,4); //K[4][4];
	Pp = createMatrix(4,4); //Pp[4][4];
	xp = createMatrix(4,1); //xp[4][1];
	A_trans = createMatrix(4,4); //A_trans[4][4];
	H_trans = createMatrix(4,4); //H_trans[4][4];

	P_part1 = createMatrix(4,4); //P_part1[4][4];
	P_part2 = createMatrix(4,4); //P_part2[4][4];

	Pp_part1 = createMatrix(4,4); //Pp_part1[4][4];
	Pp_part2 = createMatrix(4,4); //Pp_part2[4][4];

	x_part1 = createMatrix(4,1); //x_part1[4][1];
	x_part2 = createMatrix(4,1); //x_part2[4][1];
	x_part3 = createMatrix(4,1); //x_part3[4][1];


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
// dt is delta time in seconds
// p,q,r are the gyroscope outputs in rads/sec
// ax,ay,az are the accelerometer outputs g-units
void Kalman_getOrientation(float* outputOrientation, float dt, float p, float q, float r, float ax, float ay, float az){
	//float** z = createMatrix(4,1);//z[4][1];
	//float** A = createMatrix(4,4);//A[4][4];
	//float theta_a = 0; 
	//float phi_a = 0;
	//float psi_a = 0;
	//float phi = 0;
	//float theta = 0;
	//float psi = 0;

	//dt = dt*.001;
	//p = p*3.1415/180;
	//q = q*3.1415/180;
	//r = r*3.1415/180;

	if(initializeFlag == 0)
	{	
		//testing
		//printf("initialized\n");
		
		Kalman_init();
		initializeFlag = 1;
	}
//setup data for Euler Kalman algorithm

	Kalman_calcA(dt, p, q, r); 
	//testing
	//printf("\n");
	//printf("matrix A:\n");
	//printMatrix(A,4,4);
	 
	Kalman_eulerAccel(ax, ay, az); //done

	Kalman_eulerToQuaternion();  //done
	//testing
	//printf("\n");
	//printf("matrix z:\n");
	//printMatrix(z,4,1);

//perform Kalman filter algorithm


	Kalman_eulerKalman(); 

	outputOrientation[0] = phi;
	outputOrientation[1] = theta;
	outputOrientation[2] = psi;

//free memory allocated to temp matrices/vector
	//freeMatrix(z,4,1);
	//freeMatrix(A,4,4);

}

///start private functions


//checked - needs editing
//calculate state transisition matrix
//outputs: A[4][4]
//inputs dt, p, q, r
void Kalman_calcA(float dt, float p, float q, float r){
	
	/*
	A = { {1,-p*.5*dt,-q*.5*dt,-r*.5*dt},
					  {p*.5*dt,1,r*.5*dt,-q*.5*dt},
					  {q*.5*dt,-r*.5*dt,1,p*dt},
					  {r*.5*dt,q*.5*dt,-p*.5*dt,1} };
					  */

	A[0][0] = 1;
	A[0][1] = -1*p*.5*dt;
	A[0][2] = -1*q*.5*dt;
	A[0][3] = -1*r*.5*dt;
	A[1][0] = p*.5*dt;
	A[1][1] = 1;
	A[1][2] = r*.5*dt;
	A[1][3] = -1*q*.5*dt;
	A[2][0] = q*.5*dt;
	A[2][1] = -1*r*.5*dt;
	A[2][2] = 1;
	A[2][3] = p*dt;
	A[3][0] = r*.5*dt;
	A[3][1] = q*.5*dt;
	A[3][2] = -1*p*.5*dt;
	A[3][3] = 1;


}

//calculate euler angles from gyro data
//outputs: phi_a, theta_a, psi_a
//inputs: ax, ay, az
void Kalman_eulerAccel(float ax, float ay, float az)
{
	theta_a = 0 - atan(ax/sqrt(ay*ay+az*az)); //outputs in radians
	phi_a = atan(ay/sqrt(ax*ax+az*az));
	psi_a = 0;
}


//checked
//convert euler angles to quanternion units
//outputs: z[4][1]
//inputs: phi_a, theta_a,  psi_a
void Kalman_eulerToQuaternion(void) 
{

	// float sin_phi;
	// float sin_theta;
	// float sin_psi;
	// float cos_phi;
	// float cos_theta;
	// float cos_psi;

	sin_phi   = sin(phi_a/2);
	sin_theta = sin(theta_a/2);
	sin_psi   = sin(psi_a/2);
	cos_phi   = cos(phi_a/2);
	cos_theta = cos(theta_a/2);
	cos_psi   = cos(psi_a/2);

	z[0][0] = cos_phi*cos_theta*cos_psi + sin_phi*sin_theta*sin_psi;
	z[1][0] = sin_phi*cos_theta*cos_psi - cos_phi*sin_theta*sin_psi;
	z[2][0] = cos_phi*sin_theta*cos_psi + sin_phi*cos_theta*sin_psi;
	z[3][0] = cos_phi*cos_theta*sin_psi - sin_phi*sin_theta*cos_psi;

}

//outputs: phi, theta, psi
//inputs: A[][], z[][]
void Kalman_eulerKalman(void){
	// float K[4][4];
	// float Pp[4][4];
	// float xp[4][1];
	// float A_trans[4][4];
	// float H_trans[4][4];


	matrixTranspose(A_trans, 4, 4, A, 4, 4);
	matrixTranspose(H_trans, 4, 4, H, 4, 4);

	Kalman_calcxp();       
	Kalman_calcPp();	
	Kalman_calcK();	
	Kalman_calcx();			
	Kalman_calcP();
	Kalman_calcPhiThetaPsi();									
}

void Kalman_calcxp(void);
void Kalman_calcPp(void);
void Kalman_calcK(void);
void Kalman_calcx(void);
void Kalman_calcP(void);
void Kalman_calcPhiThetaPsi(void);

//********functions for eulerKalman**********

//checked
//calculate state prediction matrix
//outputs: xp
//inputs: x, A
void Kalman_calcxp(void) {
	//xp = A*x;
	matrixMultiply(xp,4,1,A,4,4,x,4,1);
	//testing
	//printf("\n");
	//printf("matrix xp:\n");
	//printMatrix(xp,4,1);

}
//checked
//calculate error covarience matrix
//outputs: Pp
//inputs: A, P,A_trans, Q
void Kalman_calcPp(void){
	//Pp = A*P*A' + Q;
	
	// float Pp_part1[4][4];
	// float Pp_part2[4][4];

	matrixMultiply(Pp_part1,4,4,A,4,4,P,4,4); 		 //write
	matrixMultiply(Pp_part2,4,4,Pp_part1,4,4,A_trans,4,4); 
	matrixAdd(Pp,4,4,Pp_part2,4,4,Q,4,4); 			//write
	
	//testing
	//printf("\n");
	//printf("matrix Pp:\n");
	//printMatrix(Pp,4,4);

}

//checked
//calculate kalman gain matrix
//output: K[][]
//input: Pp, H_trans, H, R
void Kalman_calcK(void) {
	//K = Pp*H'/(H*Pp*H'+R);
	
	// float K_part1[4][4];
	// float K_part2[4][4];
	// float K_part3[4][4];
	// float K_part4[4][4];
	// float K_part4_inv[4][4];

	matrixMultiply(K_part1,4,4,Pp,4,4,H_trans,4,4);
	matrixMultiply(K_part2,4,4,H,4,4,Pp,4,4);
	matrixMultiply(K_part3,4,4,K_part2,4,4,H_trans,4,4);
	matrixAdd(K_part4,4,4,K_part3,4,4,R,4,4);
	matrixInverse4x4(K_part4_inv,4,4,K_part4,4,4);			//write
	matrixMultiply(K,4,4,K_part1,4,4,K_part4_inv,4,4);
	
	//testing
	//	printf("\n");
	//printf("matrix K:\n");
	//printMatrix(K,4,4);

}

//
//outputs x[][]
//inputs xp[][] K[][] z[][] H[][]
void Kalman_calcx(void) {
	//x = xp + K*(z-H*xp);

	// float x_part1[4][1];
	// float x_part2[4][1];
	// float x_part3[4][1];
	
	matrixMultiply(x_part1,4,1,H,4,4,xp,4,1);
	matrixSubtract(x_part2,4,1,z,4,1,x_part1,4,1);			//write
	matrixMultiply(x_part3,4,1,K,4,4,x_part2,4,1);
	matrixAdd(x,4,1,xp,4,1,x_part3,4,1);

	//testing
	//	printf("\n");
	//printf("matrix x:\n");
	//printMatrix(x,4,1);
}

//
//outputs P[][]
//inputs: Pp[][] K[][] H[][]
void Kalman_calcP(void) {
	//P = Pp - K*H*Pp;

	// float P_part1[4][4];
	// float P_part2[4][4];
	
	matrixMultiply(P_part1,4,4,K,4,4,H,4,4);
	matrixMultiply(P_part2,4,4,P_part1,4,4,Pp,4,4);
	matrixSubtract(P,4,4,Pp,4,4,P_part2,4,4);
	
	//testing
	//	printf("\n");
	//printf("matrix P:\n");
	//printMatrix(P,4,4);

}

//calculate roll, pitch, yaw
//outputs: phi, theta, psi
//inputs: x[][]
void Kalman_calcPhiThetaPsi(void) 
{
	//phi   =  atan2(2*(x(3)*x(4)+x(1)*x(2)), 1-2*(x(2)^2 + x(3)^2));
	//theta = -asin(2*(x(2)*x(4)-x(1)*x(3)) );
	//psi   =  atan2(2*(x(2)*x(3)+x(1)*x(4)), 1-2*(x(3)^2 + x(4)^2));

	// float phi1;
	// float phi2;
	// float theta1;
	// float psi1;
	// float psi2;

		//testing
		//printf("phi1\n");
		//printMatrix(x,4,1);
	phi1 = 2*(x[2][0] * x[3][0] + x[0][0] * x[1][0]);
		//testing
		//printf("phi2\n");
	phi2 = 1 - 2*(x[1][0] * x[1][0] + x[2][0] * x[2][0]);
	
		//testing
		//printf("theta1\n");
	theta1 = 2*(x[1][0] * x[3][0] - x[0][0] * x[2][0]);

		//testing
		//printf("psi1\n");
	psi1 = 2*(x[1][0] * x[2][0] + x[0][0] * x[3][0]);
		//testing
		//printf("psi2\n");
	psi2 = 1 - 2*(x[2][0] * x[2][0] + x[3][0] * x[3][0]);

	phi = atan2(phi1, phi2);
	theta = 0 - asin(theta1);
	psi = atan2(psi1, psi2);

}










