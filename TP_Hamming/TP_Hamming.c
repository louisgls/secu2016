#include <stdio.h>
#include <stdlib.h>

void decode(int * x){

int j;

printf("Message décodé : ");

for(j = 0; j < 4; j++)
	{
	printf("%d ", x[j]);
	}
printf("\n");

}

void encode(int message[], int *x){
	int matrixG[4][7] = {
		{1, 0, 0, 0, 0, 1, 1},
		{0, 1, 0, 0, 1, 0, 1},
		{0, 0, 1, 0, 1, 1, 0},
		{0, 0, 0, 1, 1, 1, 1}
	};
	int k;
	for (k=0; k<7; k++){
		x[k] = 0;
	}
	int i, j;
	for (j = 0; j < 7; ++j)
	{
		for (i = 0; i < 4; ++i)
		{
			x[j] += message[i] * matrixG[i][j];
		}
		x[j] = x[j] % 2;
	}
	printf("Message encodé : ");
	for(j = 0; j < 7; j++)
		{
		printf("%d ", x[j]);
		}
	printf("\n");
}

void correct(int *x){
	int matrixH[3][7] = {
		{0, 0, 0, 1, 1, 1, 1},
		{0, 1, 1, 0, 0, 1, 1},
		{1, 0, 1, 0, 1, 0, 1}
	};
	int j, k;
	int w[3]={0,0,0};




    int xx[]={1,1,1,1,0,0,1};
	//printf("%d", xx[0][j]);

    for(j=0; j<3; j++){
        for(k=0; k < 7; k++){
                w[j] += matrixH[j][k] * xx[k];
                printf("j=%d k=%d \n",j,k);
                printf("H=%d xx=%d \n", matrixH[j][k],xx[k]);
                printf("w=%d\n",w[j]);
                printf("-----\n");

		}
	}
	printf("result:");
	for(j = 0; j < 3; j++)
		{
        w[j]=w[j] % 2;
		printf("%d  ", w[j]);
		}
	/*for(k=0; k < 7; k++){
		for(j=0; j<3; j++){
        printf("k et j %d %d",k,j);
        printf("etape %d %d \n", matrixH[k][j],xx[0][k]);
		w[k] += matrixH[j][k] * xx[0][k];
		printf("Calcul %d \n",w[k]);
		}
		//w[k] = w[k] % 2;
	}
	printf("Test : ");

	for(j = 0; j < 3; j++)
		{
		printf("%d ", w[j]);
		}

	printf("\n");*/

}

int main(){

int* x= malloc(7*sizeof(int));
int message[4]={1,1,0,1};
encode(message, x);
decode(x);
correct(x);


}

