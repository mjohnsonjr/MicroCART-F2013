/*
 * test_total_kalman.c
 *
 *  Created on: Mar 30, 2014
 *      Author: Kevin Engel
 */
 
 
 //CURRENT PROBLEMS 
 //- outputting to terminal, not file
 //- reading strange values at beginning
 
 
 
#include "total_kalman.h"
#include "matrix_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TORADS 3.1415/180
#define SIZE_LINE 150

void strAppendChar(char* s, char c);

int main()
{		
	//IMU data
	double dx = 0; 
	float p = 0;
	float q = 0; 
	float r = 0; 
	float ax = 0; 
	float ay = 0; 
	float az = 0; 
	
	//Kalman Filter output
	float orientation[3]; //phi theta psi: roll pitch yaw
	
	//open io files
	FILE* inputfp; //gyro, accel
	FILE* outputfp; //kalman filered data
	
	inputfp = fopen("/media/TOSHIBA/College/Senior/S2/CPRE492/KalmanTests/imudata_for_C_code2.txt", "r");
	if(inputfp == NULL)
	{
		printf("can't open input file\n");
		return;
	}
	fseek (inputfp, 0, SEEK_SET );
	//test
	//printf("inputfp: %d\n", inputfp);
	
	
	outputfp = fopen("/media/TOSHIBA/College/Senior/S2/CPRE492/KalmanTests/output.txt", "w+");
	if(outputfp == NULL)
	{
		printf("can't open output file\n");
		return;
	}
	//fseek (outputfp, 12, SEEK_SET );
	//test
	//printf("outputfp: %d\n", outputfp);
	
	//tokenize input
	char inputLine[SIZE_LINE];
	//char lineToken[SIZE_TOKEN];
	char* lineToken;
	char delimiters[] = " \t";
	
	//reading file
	char readBuffer;
	char isReadingLine = 0;
	char hasLine = 0;
	char tokenCount = 0;
	int lineCounter = 0;
	char isEnd = 0;
	
	//initialize inputLine to 0's for appending
	memset(inputLine, 0, SIZE_LINE);
	
	//test
	fseek (inputfp, 0, SEEK_END);  
   int size = ftell(inputfp);
   //fprintf(outputfp, "size of file: %d\n", size);
   fseek(inputfp, 0, SEEK_SET);
		
	while(1)
	{	
		//testing
		/*	
		if(lineCounter == 6)
		{
			break;
		}
		*/
		
		//read character
		if(fread(&readBuffer, 1, 1, inputfp) == 1)
		{
			//find end of line
			if(readBuffer == '\n' || isEnd)
			{
				hasLine = 1; //make function for this
			}
			
			//forming string from line of IMU data 
			if(readBuffer != '\n')
			{
				strAppendChar(inputLine, readBuffer);
			}
	
			//tokenize IMU data sentence, parse and store important data
			if(hasLine)
			{
				//test
				//printf("%s\n", inputLine);
				
				lineToken = strtok(inputLine, delimiters);
				tokenCount++;
				//test
				//printf("token: [%s] count: %d\n\n", lineToken, tokenCount);
				
				//grab all IMU data
				while(lineToken != NULL)
				{
					if(tokenCount == 1)
					{
						dx = strtof(lineToken, NULL);
						//test
						//printf("dx: [%.6f]\n", dx);
					}
					else if(tokenCount == 2)
					{
						p = strtof(lineToken, NULL);
						//test
						//printf("p: %.4f\n", p);
					}
					else if(tokenCount == 3)
					{
						q = strtof(lineToken, NULL);
						//test
						//printf("q: %.4f\n", q);
					}
					else if(tokenCount == 4)
					{
						r = strtof(lineToken, NULL);
						//test
						//printf("r: %.4f\n", r);
					}
					else if(tokenCount == 5)
					{
						ax = strtof(lineToken, NULL);
						//test
						//printf("ax: %.4f\n", ax);
					}
					else if(tokenCount == 6)
					{
						ay = strtof(lineToken, NULL);
						//test
						//printf("ay: %.4f\n", ay);
					}
					else if(tokenCount == 7)
					{
						az = strtof(lineToken, NULL);
						//test
						//printf("az: %.4f\n", az);
					}
					
					lineToken = strtok(NULL, delimiters);
					tokenCount++;
					//test
					//printf("token: [%s] count: %d\n\n", lineToken, tokenCount);
				}
				
				//at this point have IMU data
				
				//conversions
				dx = dx * .001; //convert from msecs to secs
				p = p*TORADS; //convert from deg/sec to rads/sec
				q = q*TORADS; 
				r = r*TORADS;
				
				Kalman_getOrientation(orientation, dx, p,q,r,ax,ay,az);
				
				//test 
				fprintf(outputfp, "%.4f\t%.4f\t%.4f\n", orientation[0], orientation[1], orientation[2]);	
				
				hasLine = 0;
				tokenCount = 0;
				lineCounter++;
				//test
				if(lineCounter == 9999)
				{
					//fprintf(outputfp, "processed line 9999\n");
					//fprintf(outputfp, "seek_cur %d\n", ftell(inputfp));
				}
				
				memset(inputLine, 0, SIZE_LINE);
			}
		}
		
		if(isEnd)
		{
			break;
		}
		
		//find end of file
		if(feof(inputfp))
		{
			isEnd  = 1;
		}
		
		
	}
}
	
void strAppendChar(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
	
	
	
	/*
//	float dx = 1.75532; //1.755300; //1.74686;
//	float p = 39.200; //12.300; //.55;
//	float q = 6.800; //-38.850; //-1.15;
//	float r = 5.200; //13.600; //-.9;
//	float ax = -.013; //-.886; //.1;
//	float ay = .503; //.033; //.097;
//	float az = .866; //.493; //.989;
	
	dx = dx * .001; //convert from msecs to secs
	p = p*TORADS; //convert from deg/sec to rads/sec
	q = q*TORADS; 
	r = r*TORADS; 
	
	float orientation[3]; //phi theta psi: roll pitch yaw
	//.0585, .0608, .0005
	//.0155, .5902, -.0047
	//.3107, .0077, -.0007
	Kalman_getOrientation(orientation, dx, p,q,r,ax,ay,az);
	
	
	printf("orientations...\n%.4f\n%.4f\n%.4f\n", orientation[0], orientation[1], orientation[2]);
}
*/
