#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

int main(){
	int arr1[4][3];
	int arr2[3][6];
	int (*arr3)[6];
	printf("Matrix 4x3:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			scanf("%d", &arr1[i][j]);
		}
	}
	printf("\nMatrix 3x6:\n");
	for(int i=0; i<3; i++){
		for(int j=0; j<6; j++){
			scanf("%d", &arr2[i][j]);
		}
	}

	int matrixID;
	key_t key=ftok(".", 'b');

	FILE *keyid = fopen("key.txt", "w");
	fprintf(keyid, "%d", key);
	fclose(keyid);

	if ((matrixID = shmget(key, 100, IPC_CREAT | 0666)) < 0)
        	printf("smget returned -1\n");
	if (!(arr3 = shmat(matrixID, NULL, 0))){
        	printf("Process shmat returned NULL\n");
    	}

	printf("\nResulting Matrix 4x6:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			arr3[i][j]=0;
			for(int k=0; k<3; k++){ 
				arr3[i][j] += arr1[i][k] * arr2[k][j];
			}
			printf("%d ", arr3[i][j]);
		}
		printf("\n");
	}
	
}
