#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#define a 16807/*Schrage��������*/
#define m 2147483647
#define r 2836
#define q 127773

int I;/*Schrage�������ɵ������*/ 
int RW1( int* A1 , int*A2, int NN ) { /*NN���������깹��2������ΪNN��һά����������һ����ά�������,���ػص��������������*/
	int n;/*ѭ������*/ 
	double x;
	int T = 0;/*��ԭ���������*/ 
	for(n = 0; n < NN; n ++) {     /*Schrage�������������x���ڽ���һά�������*/ 
		x = (double)I/m;/*����x*/ 
		 
		if(x <= 0.25 && x >= 0 ) {/*��ά�������*/ 
			*(A1+n) = *(A1+n) + 1;
		}
		
		else if (x <= 0.5 && x > 0.25 ) {
			*(A1+n) = *(A1+n) - 1;
		}
	    
	    else if(x <= 0.75 && x >= 0.5 ) {
			*(A2+n) = *(A2+n) + 1;
		}
		
		else if (x <= 1 && x > 0.75 ) {
			*(A2+n) = *(A2+n) - 1;
		} 
	    else{
	    	printf("RW Error.");/*����*/
	    	return -1; 
		}
		
		if( *(A1+n) == 0 && *(A2+n) == 0 ) /*����*/ 
		T ++;
		
	    I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	}
	return T;
}
int main(){
	int N, NN;/*N�����Ӳ�����NN��������*/ 
	int *p1,*p2;/*����x,y����λ��*/
	int n;/*�����˶�����*/ 
	int h;/*Pd*/
	FILE *fp;/*Pd(N)�ļ�*/ 
	
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &I) ;
	
	printf("Please input the step of each particle.");/*���뵥���Ӳ���*/
	scanf("%d", &N) ;
	
	printf("Please input the number of particle.");/*����������*/
	scanf("%d", &NN) ;
	
	fp=fopen("2D RW.txt","a+") ;
	fprintf(fp,"Pd(N) N\n");
	 
	p1 = (int *) malloc(NN*sizeof(int));
	p2 = (int *) malloc(NN*sizeof(int));
	
	for(n=0; n< N; n++) {/*����N���������*/
		h = RW1(p1, p2, NN);
		if(h < 0) {
			printf("Error.");/*����*/
		}
		if( n%2 == 1 )/*����Ϊż���ĵ�*/
		fprintf(fp,"%f %d\n",(double)h/NN,n+1);/*�����n����Pd*/ 
	}
	free(p1);
	free(p2);
	
	fclose(fp);  
	
	return 0;
}
