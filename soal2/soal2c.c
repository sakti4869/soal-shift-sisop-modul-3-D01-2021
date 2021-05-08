#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int pipe1[2];
int pipe2[2];

void exec1() {
  	dup2(pipe1[1], 1);

  	close(pipe1[0]); close(pipe1[1]);

  	execlp("ps", "ps", "aux", NULL);

  	perror("EXEC PS FAIL");
  	_exit(1);
}

void exec2() { 
  	dup2(pipe1[0], 0);
  	dup2(pipe2[1], 1);

  	close(pipe1[0]); close(pipe1[1]);
  	close(pipe2[0]); close(pipe2[1]);

  	execlp("sort", "sort", "-nrk", "3,3", NULL);

  	perror("EXEC SORT FAIL");
 	_exit(1);
}

void exec3() {
  	dup2(pipe2[0], 0);

  	close(pipe2[0]); close(pipe2[1]);

  	execlp("head", "head", "-5", NULL);
  	perror("EXEC HEAD FAIL");
  	_exit(1);
}
int pid;

void main() {

	if (pipe(pipe1) == -1) {
    		perror("PIPE 1 FAILED");
    		exit(1);
  	}

  	if ((pid = fork()) == -1) {
    		perror("FORK 1 FAILED");
    		exit(1);
  	} 
	else if (pid == 0) exec1();

  	if (pipe(pipe2) == -1) {
    		perror("PIPE 2 FAILED");
    		exit(1);
  	}
	
	if ((pid = fork()) == -1) {
    		perror("FORK 2 FAILED");
    		exit(1);
  	} 
	else if (pid == 0) exec2();

  	close(pipe1[0]);
  	close(pipe1[1]);

  	if ((pid = fork()) == -1) {
    		perror("FORK 3 FAILED");
    		exit(1);
  	} 
	else if (pid == 0) exec3();
}
