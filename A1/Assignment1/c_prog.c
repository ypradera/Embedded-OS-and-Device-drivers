/* 
   ECE 373
   Josh Pradera
   the programm is able
   to accept an integer input, multiply by 10 and then returns result
*/


#include <stdio.h>
#include <stdlib.h>  
#include <iostream>  

int main(int argc, char *argv[])
{
  //Declaring input number variable
  int input_number;
  
  
  if(argc != 2){
    printf("Please enter an integer.\n\n");
    exit(-1);
  } 
  
  else {
// Now convert input from string to integer
   
    input_number = atoi(argv[1]);
    printf(" Number = %d.\n%d * 30 = %d.\n\n", input_number, input_number, (input_number * 30));
    
    
    exit(0);
  } 
} 
