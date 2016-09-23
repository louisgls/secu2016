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

void correct(int *msgEncErr){
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
	printf("\ncorrect result :\n");
	for(j = 0; j < 3; j++)
		{
        result[j]=result[j] % 2;
        printf("%d",result[j]);
		//printf("%d ", result[j]);
		}
    int pos=0;
    int l=3;
    for (l=3; l>0; l--){
        pos = pos +(result[l-1]*pow(2,l-1));
    }
    printf("\nposition :%d\n",pos);
    int i;
    if (pos != 0){
        for (i=0;i<7;i++){
            if (i==pos-1){
                printf("correction at %d",i);
                msgEncErr[i]=(msgEncErr[i]+1) %2;
                //printf("correction : %d", )
            }
        }
    }
}

void generateMsg(int* msg){
    int i;
    for (i=0; i<4; i++){
        *(msg+i) = rand() %2;
        printf("%d\n", *(msg+i));
    }
}

void noise (float p, int* clrMsg, int* altMsg){
    int i;
    float r = (float)rand()/(float)RAND_MAX;
    if (r<p){
        int change= rand()%7;
        for (i=0;i<7;i++){
            if (i==change){
                altMsg[i]=(clrMsg[i]+1) %2;
            } else {
                altMsg[i]=clrMsg[i];
            }
        }

    } else {
        for (i=0;i<7;i++){
                altMsg[i]=clrMsg[i];
            }
    }

}

int main(){

srand(time(NULL));
int* c= malloc(7*sizeof(int));
int* m=malloc(4*sizeof(int));
int* m_prime=malloc(4*sizeof(int));
int* c_prime=malloc(7*sizeof(int));
int* c_second=malloc(7*sizeof(int));
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
int i;
printf("c\n");
for (i=0; i<7; i++){
    printf("%d", *(c+i));}
noise(0.5,c,c_prime);
printf("\nc prime\n");
for (i=0; i<7; i++){
    printf("%d", *(c_prime+i));}
correct(c_prime);
printf("\nc prime corrected\n");
for (i=0; i<7; i++){
    printf("%d", *(c_prime+i));}
//decode(c_prime,m_prime);
//int i;
//for (i=0; i<4; i++){
//    printf("%d\n", *(m_prime+i));
//}

}
