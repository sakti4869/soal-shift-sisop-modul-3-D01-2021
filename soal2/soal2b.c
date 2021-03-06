#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
typedef long long ll;

pthread_t thrid[24];
void *factorial_thread(void *arg);
ll factorial(int a, int b);
int (*init)[6];
int input[4][6];
ll result[4][6];

int main(int argc, char* argv[]) {
	int matrixID;
	int key;
	sscanf(argv[1], "%d", &key);

	if ((matrixID = shmget(key, 100, IPC_CREAT | 0666)) < 0)
        	printf("shmget returned -1\n");
	if (!(init = shmat(matrixID, NULL, 0))){
        	printf("Process shmat returned NULL\n");
    	}
	
	printf("Input Matrix 4x6:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			scanf("%d", &input[i][j]);
		}
	}
	printf("\n");
	printf("Previous Matrix 4x6:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			printf("%d ", init[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	for(int i=0; i<24; i++){
		if(pthread_create(&(thrid[i]), NULL, &factorial_thread, NULL));
	}
	for(int i=0; i<24; i++) pthread_join(thrid[i],NULL);
	printf("Resulting Matrix 4x6:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			printf("%lld ", result[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	shmdt(init);
	exit(0);
	return 0;
}

ll factorial(int a, int b){
	ll res=1;
	if(!a || !b) res=0;
	else if(a<b) for(int i=1; i<=a; i++) res *= i;
	else for(int i=a; i>a-b; --i) res *= i;
	return res;
}

void *factorial_thread(void *arg){
	pthread_t id = pthread_self();
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			if(pthread_equal(id, thrid[i])) {
			result[i][j] = factorial(init[i][j], input[i][j]);

			}
		}
	}

}
