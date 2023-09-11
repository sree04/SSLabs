// Question : Write a program to display the environmental variable of the user (use environ).

#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(){
int i = 0;
while(environ[i]) {
  printf("%s\n", environ[i++]);
}
return 0;
}

