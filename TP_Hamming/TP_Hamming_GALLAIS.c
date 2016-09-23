#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void decode(int *msgEnc){

int j;
//printf("Msg decoded : ");
printf("m' : ");
for(j = 0; j < 4; j++)
	{
    printf("%d", msgEnc[j]);
	}
printf("\n");
//printf("\n");
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
	printf(" -> ");
	for(j = 0; j < 7; j++)
		{
		printf("%d", result[j]);
		}
	//printf("\n");
}

void correct(int *msgEncErr){
	int matrixH[3][7] = {
		{0, 0, 0, 1, 1, 1, 1},
		{0, 1, 1, 0, 0, 1, 1},
		{1, 0, 1, 0, 1, 0, 1}
	};
	int j, k;
	int result[3]={0,0,0};

    for(j=0; j<3; j++){
        for(k=0; k < 7; k++){
                result[j] += matrixH[j][k] * msgEncErr[k];
		}
	}
	for(j = 0; j < 3; j++)
		{
        result[j]=result[j] % 2;
        //printf("%d",result[j]);
		}
	//printf("\n");
    int pos=0;
    int l;
    int p=0;
    for (l=3; l>0; l--){
        pos += (result[l-1]*pow(2,p));
        p++;
    }
    //printf("Correction at position : %d\n",pos);
    int i;
    if (pos != 0){
        for (i=0;i<7;i++){
            if (i==pos-1){
                msgEncErr[i]=(msgEncErr[i]+1) %2;
            }
        }
    }
    printf(" -> ");
    for (i=0; i<7; i++){
    printf("%d", *(msgEncErr+i));
    }
    printf(" -> ");
}

void generate(int* msg){
    int i;
    //printf("Random msg : ");
    printf(("m : "));
    for (i=0; i<4; i++){
        *(msg+i) = rand() %2;
        printf("%d", *(msg+i));
    }
    //printf("\n");
}

void noise (float p, int* clrMsg, int* altMsg){
    int i;
    for (i=0; i<7; i++){
        float r = (float)rand()/(float)RAND_MAX;
        if (r<p){
            altMsg[i]=(clrMsg[i]+1) %2;
    } else {
            altMsg[i]=clrMsg[i];
            }
    }
    printf(" + noise : ");
    for (i=0;i<7; i++){
    printf("%d", altMsg[i]);
    }
    //printf("\n");
}

int main(){

srand(time(NULL));
int* c=malloc(7*sizeof(int));
int* m=malloc(4*sizeof(int));
int* m_prime=malloc(4*sizeof(int));
int* c_prime=malloc(7*sizeof(int));
int i;

float p = 0.001;
printf("P = %f \n", p);

    for (i=0; i<10; i++){
        printf("%d) ", i);
        generate(m);
        encode(m,c);
        noise(p,c,c_prime);
        correct(c_prime);
        decode(c_prime);
    }

printf("\n");

float p2 = 0.5;
printf("P = %f \n", p2);

    for (i=0; i<10; i++){
        printf("%d) ", i);
        generate(m);
        encode(m,c);
        noise(p2,c,c_prime);
        correct(c_prime);
        decode(c_prime);
    }

free(c);
free(m);
free(m_prime);
free(c_prime);
}
