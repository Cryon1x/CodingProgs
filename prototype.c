/* Voombot API by Vikrant Sharma. 

Dear maintainer,
This program takes in user input for various vacuumbot-related (i.e. Roomba) parameters (e.g. location, roomsize, etc.)
and determines if a movement instruction set is valid. It prints the final location of the vacuumbot. Program catches
errors and ignores extra spaces as well as gibberish input after the intended input on the line (e.g. "1   3 N noise" is read
as "1 3 N"). New features may be added as standalone functions, such as the inbuilt ones like "roomsize". 

The output for each bot should be its final co-ordinates and heading. 
INPUT AND OUTPUT 
Test Input: 
5 5 
1 2 N 
LMLMLMLMM 
3 3 E 
MMRMMRMRRM 
Expected Output: 
1 3 N 
1 5 E 

*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VOOMBOTNUM 2 // number of voombots 
#define MAXINPUT 1000 //longest line of user input

typedef struct VOOMBOT {
	 int x,y,DIRECTION;
    //float battery;    // Add some more information that might be useful to a voombot
    //char SERIAL_NUMBER;
    struct VOOMBOT * next;
}  botinfo;
typedef botinfo * botptr; // struct that stores all voombot info

void roomsize( int *,  int *);  // gets roomsize
void botlocator(botptr,  int,  int); // gets bot location
void botparser(botptr, int, int); // parses and applies bot movement command
void trav(botptr); //traverses struct and prints final bot location


int main(void) {

	botptr init = NULL, last = NULL;
	int xMax, yMax, i = 1; 

	init = (botptr) malloc(sizeof(botinfo)); // initialize voombot struct
	last = init;

	roomsize(&xMax, &yMax);  

	for (i = 1;i <= VOOMBOTNUM; i++) { 

		botlocator(last, xMax,yMax);
		botparser(last, xMax,yMax); 
		//botbattery(inputs);		//stick more functions here to add functionality

		last -> next = malloc(sizeof(botinfo));
		last = last -> next;
	} // loop for # of voombots
	trav(init);
	return 0;
}



void roomsize( int * xMax,  int * yMax) {	
   /* Instead of references directly to the voombot structure, variables like 'x' and 'y' 
	 below are declared again in these functions. This allows the program to run 
	 faster and it's easier to read. */

	char input[MAXINPUT]; 
	int x,y;

	fgets(input, MAXINPUT, stdin); 

		if (sscanf(input, "%i %i", &x, &y) == 2 ) { // error-checking for the first line of input.
			*xMax = abs(x);
			*yMax = abs (y);
		}
		else {
			printf("Unrecognizable Input. Exiting.\n"); exit(0);
		}
}

void botlocator(botptr current,  int xmax,  int ymax) {
	char input[MAXINPUT], direction; 
	int x,y;
    fgets(input, MAXINPUT, stdin); 

	if ((sscanf(input, "%i %i %c", &x, &y, &direction) == 3) && ((direction == 'N') || (direction == 'S') || (direction == 'W') || (direction == 'E')) && x <= xmax && y <= ymax) { // error-checking for the second line of input.
		current -> x = abs(x);
		current -> y = abs(y);
		switch(direction) {
			case 'N': 		current -> DIRECTION = 0; break;
			case 'W':		current -> DIRECTION = 1; break;
			case 'S':			current -> DIRECTION = 2; break;
			case 'E': 			current -> DIRECTION = 3; break;
			default: 			printf("Input isn't a valid direction. Exiting.\n"); exit(0);
		}
	}
	else {
		printf("Unrecognizable Input. Exiting.\n"); exit(0);
	}

}

void botparser(botptr current, int xmax, int ymax) {
	char input[MAXINPUT];
	int x = current -> x,y = current -> y, d = current -> DIRECTION, i = 0;           

	fgets(input, MAXINPUT, stdin); sscanf(input, "%c", &input);
	
	while (input[i] != '\n') {
		switch (input[i]) {
			case 'M': 		switch(d) {
   										case 0: 		y++; break;
   										case 1:		x++; break;
   										case 2:		y--; break;
   										case 3:		x--; break;
   										default:		printf("Internal 'direction' doesn't seem to be set correctly. Exiting.\n"); exit(0);
   									} break;  	
   			case 'L':			d = (d + 3) % 4; break;
   			case 'R':			d = (d + 1) % 4; break;
   			default:			printf("Unrecognizable input. Exiting.\n"); exit(0);
		}
		if (x > xmax || x < 0 || y < 0|| y > ymax) {
			printf("Voombot instruction exceeds room bounds! Exiting.\n"); exit(0);
		}
		i++;
	}

current -> x = x;
current -> y = y;
current -> DIRECTION = d;
}


void trav(botptr current) {
	while (current -> next != NULL) {
		printf("%i %i ", current -> x, current -> y);
		switch(current -> DIRECTION) {
			case 0: 		printf("N\n"); break;
			case 1: 		printf("W\n"); break;
			case 2: 		printf("S\n"); break;
			case 3: 		printf("E\n"); break;
			default: 		printf(" NOT FOUND \n");
		}
		current = current -> next;
	}

}