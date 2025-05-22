#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
char getchar_no_block(){

}
int divisionquiz() {
	int numQuestions,correctAnswer = 0;
	int num1, num2, userAnswer, correctAnswer;
	srand(time(NULL));
	printf("Enter the number of questions: ");
	scanf("%d", &numQuestions);
	for(int i=0; i<numQuestions;i++){
		num1 = rand() % 100;
		num2 = rand() % 100;
		if (num1 < num2){
			int temp=num1;
			num1=num2;
			num2=temp;
		}
		correctAnswer = num1 / num2;
	}
}
int subtractionquiz() {
    int numQuestions, correctAnswers = 0;
    int num1, num2, userAnswer, correctAnswer;

    // Seed the random number generator
    srand(time(NULL));

    // Get the number of questions from the user
    printf("Enter the number of questions: ");
    scanf("%d", &numQuestions);

    for (int i = 0; i < numQuestions; i++) {
        // Generate two random numbers
        num1 = rand() % 100; // Numbers between 0 and 99
        num2 = rand() % 100;

        // Ensure num1 is greater than or equal to num2 to avoid negative results
        if (num1 < num2) {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        // Calculate the correct answer
        correctAnswer = num1 - num2;

        // Ask the user the question
        printf("Question %d: What is %d - %d? ", i + 1, num1, num2);
        scanf("%d", &userAnswer);

        // Check if the user's answer is correct
        if (userAnswer == correctAnswer) {
            printf("Correct!\n");
            correctAnswers++;
        } else {
            printf("Wrong! The correct answer is %d.\n", correctAnswer);
        }
    }

    // Display the results
    printf("\nYou answered %d out of %d questions correctly.\n", correctAnswers, numQuestions);

    return 0;
}
int main(){
	char ans;
	printf("Please type charecter for mode\n    A:Subtraction quiz\n    B: Multiplication quiz\n    C:Times table quiz\n    D: Multiplicarion quiz\n");
	ans = getchar();
	while(getchar() !='\n');
	if(ans != '\n' || ans != '\0'){printf("%c\n",ans);}else{printf("Input is NULL or empty\n");}
}
