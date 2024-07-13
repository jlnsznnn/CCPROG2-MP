#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i = 4;
    double d = 4.0;
    char s[] = "HackerRank ";
    
    // Declare second integer, double, and String variables.
    
    int input1;
    double input2;
    char input3[100];
    
    int nSum;
    double dSum;
    char sLine[100];
    
    // Read and save an integer, double, and String to your variables.
    
    scanf("%d", &input1);
    scanf("%lf", &input2);
    scanf(" %[^\n]", input3);
    
    
    // Print the sum of both integer variables on a new line.
    nSum = i + input1;
    printf("%d\n", nSum);
    
    // Print the sum of the double variables on a new line.
    dSum = d + input2;
    printf("%.1lf\n", dSum);
    
    // Concatenate and print the String variables on a new line
    // The 's' variable above should be printed first.
    strcpy(sLine, strcat(s, input3));
    printf("%s", sLine);

    return 0;
}