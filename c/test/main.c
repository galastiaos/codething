#include <stdio.h>
typedef union{
	int num1;
	int num2;
	int num3;
}un; //an example union
typedef enum{
	changed,
	setto
	}unnstatushow;
void getunn(un un, enum unnstatus unstat){ //not confusing at all
		printf("num1 %s to %i\n num2 %s to %i\n", (unstat = setto) ? "set" : "changed", un.num1, (unstat = setto) ? "set" : "changed", un.num2, (unstat = setto) ? "set" : "changed", num3);
}
int main(int argc, char *argv[]){
	printf("Hello, world!\n");
	char name[256];//a string with 256 bytes allocated
	scanf("%s",name);//get user input and store it in name
	printf("Hello, %s\n",name);
	un unn; //note un is the type  name unn is the actual object name
	unn.num1=2;
	printf("num1: %i\n",unn.num1);
	unn.num2=1;
	printf("changed num2 to %i\n, num1 is %i\n", unn.num2, unn.num1);
	return 0;
}
