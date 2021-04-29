#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int Sample(double x) {
	int n;/*ѭ������*/
	int N = 0;/*ʵ�����ݵ�ĸ���*/
	int P = 0 ;/*N0+N1+����+Nn*/
	FILE *fp;/*data.txt��ָ��*/ 
	int DATA[114][2];
	
	fp = fopen("data.txt","r") ;
	
	if(fp == NULL){/*��ʧ�ܻᱨ��*/
        printf("Failed to open data.txt.\n");
        return -1;
	}
	
	for(n = 0; n <114; n++){/*������ʵ��ֵ�����������*/
		fscanf(fp,"%d %d",DATA[n],(DATA[n]+1));
		N += DATA[n][1] ;/*�����ݵ����*/
	}
	
	fclose(fp);
	
	x *= N;/*��Ƚ�N*x��P������Ƚ���Nx����x��ʡ�ڴ�*/ 
	
	n = 0;
	do{                   /*�Ƚ�xN��P�ҵ�����������n��ѭ������ʱn��ֵ�Ƿ���������n+1*/ 
		P += DATA[n][1];
		n ++; 
	} 
	while(x > P );
	n --;
	
    return (n+2900) ;/*��������*/
}

int main() {
	int a,b,m,r,q,Q,seed;/*Schrage������������*/
	int n;/*n��ѭ������õ��ı���*/
	FILE *fp;/*�������ɵ�����*/
	double x;/*Schrage�������ɵ������*/ 
	int I;/*��������ɵ�In*/
	
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &Q) ;
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    fp=fopen("tune1.txt","a+") ;     /*������ģ���ļ�*/
	fprintf(fp,"E/eV\n");/*��ӡ����*/
	
	I = seed;/*������ֵ����I0*/
    
    for( n = 0; n < Q; n ++) {                   /*��In���xn,Ȼ���� Schrage������In+1,��xn����Sample����E*/ 
	
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
	fprintf(fp,"%d\n",Sample(x)) ;
	}

	fclose(fp); 
	return 0; 
}
