#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>

#define MAXIN 100  //max input
#define MAXTOK 30  //max token/word size
#define MAXNUM 15  //max number of tokens
#define MAXOUT 256 //max output size

//prototypes
int parseString(char* inString, char* inDelimiters, char** outStrings);
void zeroStringArr(char** stringArr, int numElements);


int main(int argc, char ** argv)
{
	char* prompt = "ucart> "; 			//string cli prompt
	char** parsedInput = (char**)malloc(sizeof(char) * (MAXNUM + 1));		
	
	char* delimiters = " \n";		  	//string of delimiters for parsing input
	char input[MAXIN];				  	//string of input to cli (unparsed)
	int numInputs;					//number of inputs read from cli (sudo argc)
	
//initialize ----------------------------------------------------------------------------		
	//initialize parsedInput to null pointers
	zeroStringArr(parsedInput, MAXNUM + 1);
	
	//check cli option for changing prompt name
	int i = 0;
	for(i; i < argc; i++)
	{
		//check for change cli option
		if(strcmp("-p", argv[i]) == 0)
		{
			//prompt changes to next command line argument
			//error check if nothing is given: use default
			if(i+1 < argc)
			{
				prompt = malloc(strlen(argv[i+1]) + 3); 
				prompt = strcat(prompt, argv[i+1]); 
				prompt = strcat(prompt, "> ");
			}
		}
	}
	
	printf(prompt);

//loop -------------------------------------------------------------------------------------	
	while(1)
	{
		//waits here for input from stdin
		fgets(input, MAXIN, stdin); 
				
		//breaks the input into tokens	
		numInputs = parseString(input, delimiters, parsedInput);
		
		
//built in commands ************************************************************************	
		//'enter': displays new prompt
		if(strncmp(input, "\n", 1) == 0)
		{
			//user pressed enter; display prompt
			printf(prompt);			
			continue;		
		}
		//help: displays all available commands and syntax
		else if(strncmp(parsedInput[0], "help", 4) == 0)
		{
			
		}
		//quad: displays quad control commands and syntax
		else if(strncmp(parsedInput[0], "quad", 4) == 0)
		{
			
		}
		//q: exits the cli
		else if(strncmp(parsedInput[0], "q", 1) == 0)
		{
			return 0;
		}
		//exit: exits the cli
		else if(strncmp(parsedInput[0], "exit", 4) == 0)
		{
			return 0;
		}
		//clear: clears terminal screen
		else if(strncmp(parsedInput[0], "clear", 5) == 0)
		{
			system("clear"); //terminal commands are capable through this function
		}
		//autonomous quad lift off algorithm
		else if(strncmp(parsedInput[0], "lift", 4) == 0)
		{
			
		}
		//autonomous quad landing algorithm
		else if(strncmp(parsedInput[0], "land", 4) == 0)
		{
			
		}
//altitude ----------------------------------------------
		//alt: adjusts the altitude of the quad 
		else if(strncmp(parsedInput[0], "alt", 3) == 0)
		{
			printf("adjust alt\n");
		} 
		//salt: sets the altitude of the quad
		else if(strncmp(parsedInput[0], "salt", 4) == 0)
		{
			//prompt to double check for safety
			printf("set alt\n");
		}
//latitude ---------------------------------------------
		//lat: adjusts the latitude position of the quad (in meters)
		else if(strncmp(parsedInput[0], "lat", 3) == 0)
		{
			//no errors
			printf("lat\n");
		}
		//slat: sets the latitude position of the quad (in meters)
		else if(strncmp(parsedInput[0], "slat", 4) == 0)
		{
			//no errors
			printf("slat\n");
		}
//longitude --------------------------------------------
		//lon: adjusts the longitude position of the quad (in meters)
		else if(strncmp(parsedInput[0], "lon", 3) == 0)
		{
			//no errors
			printf("lon\n");
		}
		//slon: sets the longitude position of the quad (in meters)
		else if(strncmp(parsedInput[0], "slon", 4) == 0)
		{
			//no errors
			printf("slon\n");
		}
//pitch ----------------------------------------------- 
		//pit: adjusts the pitch orientation of the quad (in pwm increments)
		else if(strncmp(parsedInput[0], "pit", 3) == 0)
		{
			//no errors
			printf("pit\n");
		}
		//spit: sets the pitch orientation of the quad (in pwm increments)
		else if(strncmp(parsedInput[0], "spit", 4) == 0)
		{
			//no errors
			printf("spit\n");
		}
//roll ----------------------------------------------------  
		//rol: adjusts the pitch orientation of the quad (in pwm increments)
		else if(strncmp(parsedInput[0], "rol", 3) == 0)
		{
			//no errors
			printf("rol\n");
		}
		//srol: sets the pitch orientation of the quad (in pwm increments)
		else if(strncmp(parsedInput[0], "srol", 4) == 0)
		{
			//no errors
			printf("srol\n");
		}
//yaw ----------------------------------------------------
		//yaw: adjusts the pitch orientation of the quad (in pwm increments))
		else if(strncmp(parsedInput[0], "yaw", 3) == 0)
		{
			//no errors
			printf("yaw\n");
		}
		//syaw: sets the pitch orientation of the quad (in pwm increments))
		else if(strncmp(parsedInput[0], "syaw", 4) == 0)
		{
			//no errors
			printf("syaw\n");
		}
//throttle ---------------------------------------------------- 
		//thr: adjusts the pitch orientation of the quad (in pwm increments)
		else if(strncmp(parsedInput[0], "thr", 3) == 0)
		{
			//no errors
			printf("thr\n");
		}
		//sthr: sets the pitch orientation of the quad (in pwm increments)
		else if(strncmp(parsedInput[0], "sthr", 4) == 0)
		{
			//0 args - do nothing 
			if (parsedInput[1] == NULL)
			{
	 			printf("sthr\n");
				//todo	
			}
			//>=1 arg - set throttle to arg value
			else 
			{
	 			//safety check for large values 
	 			if(parsedInput[1] > 1)
	 			{
	 				printf("this may be a large value. are you sure this is correct?\n");
					//todo
	 			}
				//value is reasonable
	 			else
				{
					//todo
				}
			}
		}
		else
		{
			printf("command not found, try \"help\" for a list of commands\n");
		}
					
		//print prompt to indicate cli is ready for input (about to loop back to fgets) 
		printf(prompt);
		
		//reset parsedInput back to null pointers
		i = 0;
		while(parsedInput[i] != NULL)
		{
			parsedInput[i] = NULL;
			i++;
		}		
	}	
	return 0;
}

//Helper Functions----------------------------------------------------------------------------

//returns number of outStrings 
//array of strings will end with null pointer 
int parseString(char* inString, char* inDelimiters,  char** outStrings)
{
	char* token; // = malloc(sizeof(char) * MAX);
	token = strtok(inString, inDelimiters);	
	
	//tokenize input
	int i = 0;
	while(token != NULL)
	{
		outStrings[i] = token;
		token = strtok(NULL, inDelimiters);
		i++;
	}
			
	return i;
}

//zeros an array of strings to null pointers
void zeroStringArr(char** stringArr, int numElements)
{
	int i = 0;
	for(i; i < numElements; i++)
	{
		*(stringArr + i) = (char*)0;
	}
}




