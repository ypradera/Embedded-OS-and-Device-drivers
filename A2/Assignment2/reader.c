/*
  ECE 373
  Josh Pradera
  Assignment2: Simple Reader
*/

#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h>     

int main(int argc, char *argv[]){
  int descr_f = 0;
  int buf_var;
  descr_f = open("opening char device", O_RDONLY);
  
  // In case open fails
  if(descr_f < 0){
    printf("Could not open!\n");
    perror("Error");
    return(-1);
  }
  //Reading the syscall 
  if(read(descr_f, &buf_var, sizeof(int)) < 0){
    printf("Could not read!\n");
    return(-1);
  }

  printf("Received syscall  = %d from the module\n", (int)buf_var);
 
  close(descr_f);
  return(0);
}
