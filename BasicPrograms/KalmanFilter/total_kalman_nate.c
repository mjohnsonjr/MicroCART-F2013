#include <stdio.h>
#include <math.h>

	int size;
	
	float H[4][4];
	float x[4][1];
	float P[4][4];
	float Q[4][4];
	float R[4][4];
	
	float A[4][4];
	
	float dt, p, q, r,
			roll, pitch, yaw,
			ax, ay, az,
			phi, theta, psi,
			Pp, xp, z,
			phi_a, theta_a, psi_a;
			

void Kalman_2014_init(){

	int i;
	int j;

	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(i == j){
				H[i][j] = 1;
			}
			else{
				H[i][j] = 0;
			} 
			printf("%d",H[i][j]);
			printf("\n");
		}
	} 
	

	

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(i == j){
				Q[i][j] = .003;
			}
			else{
				Q[i][j] = 0;
			} 
			printf("%d",Q[i][j]);
		printf("\n");
		}
	} 

	
	

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(i == j){
				R[i][j] = .67;
			}
			else{
				R[i][j] = 0;
			} 
			printf("%d",R[i][j]);
			printf("\n");
		}
	} 


	

	for(i = 0; i < 1; i++){
		for(j = 0; j < 4; j++){
			if(i == j){
				x[i][j] = 1;
			}
			else{
				x[i][j] = 0;
			} 
			printf("%d",x[i][j]);
			printf("\n");
		}
	} 
	
	

    for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(i == j){
				P[i][j] = 1;
			}
			else{
				P[i][j] = 0;
			} 
			printf("%d",P[i][j]);
			printf("\n");
		}
	} 
	
	
	//int phi=0;
	//int theta=0;
	//int psi=0;
}

int Kalman_2014_getData(float* roll, float* pitch, float* yaw){

	



	*roll = phi;
	*pitch  = theta;
	*yaw = psi;
}


//------------------//
// Private Funcions //
//------------------//

int Kalman_2014_convert(float dt, float p, float q, float r, float ax, float ay, float az){
	float z[4];
	float A[4][4];
	float theta_a;
	float phi_a;
	float psi_a=0;

	dt = dt*.001;
	p = p*3.1415/180;
	q = q*3.1415/180;
	r = r*3.1415/180;

	Kalman_calcA(A, dt, p, q, r);

	Kalman_accelEst(&phi_a, &theta_a, ax, ay, az);

	Kalman_eulerToQuaternion(z, phi_a, theta_a, 0);

	Kalman_EulerKalman(&phi, &theta, &phi, A, z);

	return 1;
}

int Kalman_2014_Euler_Kalman(float* phi, float* theta, float* psi, float* A, float* z){
	float K[4][4];
	float Pp[4][4];
	float xp[4][1];
	float A_[4][4];
	float H_[4][4];

	Kalman_calcxp(xp, A, x);           
	Kalman_calcPp(Pp, A, P, A_, Q);		
	Kalman_calculateK(K, Pp, H_, H, R);				
	Kalman_calcx(x, xp, K, z, H);					
	Kalman_calcP(P, Pp, K, H);						
	Kalman_calcPhiThetaPsi(P, Pp, K, H);				
}

//values stored into A, which is output
void Kalman_calcA(float** A, float dt, float p, float q, float r){
	
	// A[4][4] = { {1,-p*.5*dt,-q*.5*dt,-r*.5*dt},
	//				  {p*.5*dt,1,r*.5*dt,-q*.5*dt},
	//				  {q*.5*dt,-r*.5*dt,1,p*dt},
	//				  {r*.5*dt,q*.5*dt,-p*.5*dt,1} };
	
	A[0][0] = 1;
	A[0][1] = -p*.5*dt;
	A[0][2] = -q*.5*dt;
	A[0][3] = -r*.5*dt;
	A[1][0] = p*.5*dt;
	A[1][1] = 1;
	A[1][2] = r*.5*dt;
	A[1][3] = -q*.5*dt;
	A[2][0] = q*.5*dt;
	A[2][1] = -r*.5*dt;
	A[2][2] = 1;
	A[2][3] = p*dt;
	A[3][0] = r*.5*dt;
	A[3][1] = q*.5*dt;
	A[3][2] = -p*.5*dt;
	A[3][3] = 1;
}

int Kalman_calcPp(float* Pp, float* A, float* P, float* A_, float* Q){
	
	
	float Pp_part1[4][4] = MatrixMultiply(A,P);   //write
	float A_trans[4][4] = Transpose(A);			  //write
	float Pp_part2[4][4] = MatrixMultiply(Pp_part1,);  //write


}


//what it does: multiplies first matrix by second matrix and stores in result
//returns: -1 if impossible to multiply matrices, 1 if multiplication successful 
//output: result[][]
//input: first[][], second[][], size_i, size_j
char MatrixMultiply(float** result, float** first, float** second, int numRow1, int numCol1, int numRow2, int numCol2){

	int i;
	int j;
	int k;
	
	int sum = 0;
		
	if(numCol1 != numRow2)
	{
		return -1;
	}
	else
	{
		// multiplcation and results matrix filled	
		for( i = 0; i < numRow1; i++){
			for( j = 0; j < numCol2; j++){
				for( k = 0; k < numCol1, k++){
					sum = sum + first[i][k]*second[k][j];
				}
			result[i][j] = sum;
			}
		}	
		// displays result matrix
		for( i = 0; i < numRow1; i++){
			for( j = 0; j < numCol2; j++){
			printf(" %d ", result[i][j]);
			printf("\n");		
			}
		}	
	}
	return 1;
}

// adds matrix second to matrix first, and stores in result matrix
// 
//
void MatrixAdd(float** result, float** first, float** second, int size_i, int size_j){

	int i;
	int j;
		
	// addition and results matrix filled	
	for( i = 0; i < size_i; i++){
		for( j = 0; j < size_j; j++){
						
			result[i][j] = first[i][j] + second[i][j];
					
		}
	}	
	// displays result matrix
	for( i = 0; i < size_i; i++){
		for( j = 0; j < size_j; j++){
		printf(" %d ", result[i][j]);
		printf("\n");		
		}
	}	
}

// subtracts matrix second to matrix first, and stores in result matrix
// 
//
void MatrixSubtract(float** result, float** first, float** second, int size_i, int size_j){

	int i;
	int j;
		
	// addition and results matrix filled	
	for( i = 0; i < size_i; i++){
		for( j = 0; j < size_j; j++){
						
			result[i][j] = first[i][j] - second[i][j];
					
		}
	}	
	// displays result matrix
	for( i = 0; i < size_i; i++){
		for( j = 0; j < size_j; j++){
		printf(" %d ", result[i][j]);
		printf("\n");		
		}
	}	
}


void MatrixInverse(float** result, float** first, float** inverse int size_i, int size_j){

	int i;
	int j;
	
  float determ_3; 
  float determ_4;
  
  	for( i = 0; i < size_i; i++)
  		determ_3 =	(first[0][i]*(first[1][(i+1)%3]*first[2][(i+2)%3] - first[1][(i+2)%3]*first[2][(i+1)%3]));
		
		
		determ[4][4] = first[0][0]*(determ_3)-first[0][1]*(determ_3) + first[0][2]*(determ_3) -first[0][3]*(determ_3);
		
		inverse[4][4] =   
		




int Kalman_calcK(float* K, float* Pp, float* H_, float* H, float* R) {

}

int Kalman_calcP(float* P, float* Pp, float* K, float* H) {

}

int Kalman_calcxp(float* x, float* xp, float* K, float* z, float* H) {

}

int Kalman_calcPhiThetaPsi(float* phi, float* theta, float* psi, float* x) {

}




int KALMANFILTER_eulerToQuaternion(float* z, float phi_a, float theta_a, float psi_a) {

	float sin_phi;
	float sin_theta;
	float sin_psi;
	float cos_phi;
	float cos_theta;
	float cos_psi;

	sin_phi   = (float) sin(phi_a/2);
	sin_theta = (float) sin(theta_a/2);
	sin_psi   = (float) sin(psi_a/2);
	cos_phi   = (float) cos(phi_a/2);
	cos_theta = (float) cos(theta_a/2);
	cos_psi   = (float) cos(psi_a/2);

	z[0] = cos_phi*cos_theta*cos_psi + sin_phi*sin_theta*sin_psi;
	z[1] = sin_phi*cos_theta*cos_psi - cos_phi*sin_theta*sin_psi;
	z[2] = cos_phi*sin_theta*cos_psi + sin_phi*cos_theta*sin_psi;
	z[3] = cos_phi*cos_theta*sin_psi - sin_phi*sin_theta*cos_psi;

	return 1;
}


void Transpose(float** mat){
	
	int i;
	int j;
	
	int k = j;
	int l = i;
	
	float trans;
	float** mat;
	
	for(i = 0; i < k; i++){
		for( j = 0; j < l; j++){
			trans[i][j] = mat[j][i]; 
			printf("%d",trans[i][j]);
			printf("\n");
			printf("%d",mat[j][i]);
			printf("\n");
		}
	}
	
	
/*    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            std::swap(m[i][j], m[j][i]);
        }
    }
} */
