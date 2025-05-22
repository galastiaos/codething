#include <stdio.h>
#include <math.h>
void radtoDeg(double *val){
	if(val){
		*val = *val * 180 / M_PI;
	} else {
		fprintf(stderr,"Error: Recieved null pointer when converting theta2 to degrees\n");
		val = (double *)calloc(1, sizeof(double));
		if(val){
			*val = 0.0;
			printf("The answer will be wrong, because theta 2 was allocated to it because of a null pointer");
			free(val);
		} else {
			fprintf(stderr,"couldnt initialize val");
		}
	}
}
void degtoRad(double *val){
	if(val){
		*val = *val * M_PI / 180.0;
	}
}
int main(){
	double val1=1.33; //n1 actual value
	double val2=1.0003; //n2 actual value
	double theta2;
	double theta1=25;
	degtoRad(&theta1); //use the degtorad function because this theta1 is the angle in degrees, not radians, which is what sin and asin need for this to be correct.
	double n1=val1*sin(theta1); //left side of equation
	double n2=val2;//= and the right side of equation
	n1 /= n2; //cancel out the the n2 part of the equation
	theta2 = asin(n1); //convert the value of n2 to an angle
	radtoDeg(&theta2); //use the radtoDeg function, because asin(); returns value in radians, not degrees.
	printf("%f\n",theta2);
}
