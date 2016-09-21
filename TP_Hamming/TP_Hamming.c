#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void decode(int *msgEnc, int* msgDec){

int j;
printf("Message decode : ");

for(j = 0; j < 4; j++)
	{
    msgDec[j]=msgEnc[j];
	}

}

void encode(int* msg, int *result){
	int matrixG[4][7] = {
		{1, 0, 0, 0, 0, 1, 1},
		{0, 1, 0, 0, 1, 0, 1},
		{0, 0, 1, 0, 1, 1, 0},
		{0, 0, 0, 1, 1, 1, 1}
	};
	int k;
	for (k=0; k<7; k++){
		result[k] = 0;
	}
	int i, j;
	for (j = 0; j < 7; ++j)
	{
		for (i = 0; i < 4; ++i)
		{
			result[j] += msg[i] * matrixG[i][j];
		}
		result[j] = result[j] % 2;
	}
	printf("Message encode : ");
	for(j = 0; j < 7; j++)
		{
		printf("%d ", result[j]);
		}
	printf("\n");
}

void correct(int *msgEncErr, int* msgEncCor){
	int matrixH[3][7] = {
		{0, 0, 0, 1, 1, 1, 1},
		{0, 1, 1, 0, 0, 1, 1},
		{1, 0, 1, 0, 1, 0, 1}
	};
	int j, k;
	int result[3]={0,0,0};
    int c[]={1,1,1,1,0,0,1};

    for(j=0; j<3; j++){
        for(k=0; k < 7; k++){
                result[j] += matrixH[j][k] * msgEncErr[k];
		}
	}
	for(j = 0; j < 3; j++)
		{
        result[j]=result[j] % 2;
		printf("test : %d ", result[j]);
		}
    int pos=0;
    int l=3;
    for (l=3; l>0; l--){
        pos = pos +(result[l-1]*pow(2,l-1));
    }
    printf("\n position :%d",pos);
    printf("\n");
    int i;
    if (pos != 0){

        for (i=0;i>7;i++){
            if (i==pos-1){
              msgEncCor[i]=msgEncErr[i]+1 %2;
            } else{
                msgEncCor[i]=msgEncErr[i];
            }
        }
    }else{
        for (i=0;i>7;i++){
            msgEncCor[i]=msgEncErr[i];
        }
    }
}

void generateMsg(int* msg){
    srand(time(NULL));
    int i;
    for (i=0; i<4; i++){
        *(msg+i) = rand() %2;
        printf("%d\n", *(msg+i));
    }
}

int main(){

int* c= malloc(7*sizeof(int));
int* m=malloc(4*sizeof(int));
int* m_prime=malloc(4*sizeof(int));
int* c_prime=malloc(7*sizeof(int));
/*encode(message, x);
decode(x);
correct(x);
*/
/*int i;
for (i=0; i<4; i++){
    printf("%d\n", *(rdmMsg+i));
}*/
generateMsg(m);
encode(m,c);
correct(c,c_prime);
decode(c_prime,m_prime);
int i;
for (i=0; i<4; i++){
    printf("%d\n", *(m_prime+i));
}

}
