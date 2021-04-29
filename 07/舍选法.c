#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int main(){
	int a,b,m,r,q,Q,seed;/*Schrage������������*/
	int n;/*n��ѭ������õ��ı���*/
	FILE *fp;/*fp�����ڵ������ݣ������ڱ������ɵ�����*/
	double x,y;/*Schrage�������ɵ��������*/ 
	int I;/*��������ɵ�In*/
	int N = 0, N0=0;/*N��ʵ�����ݵ�ĸ�����N0��Ƶ���Ͻ�*/
	int X,Y;/*��ѡ���ķ���*/
	int DATA[114][2];/*������׵�����*/ 
	int J;/*�ɹ���������*/
	
	/*��������*/ 
	fp = fopen("data.txt","r") ;
	
	if(fp == NULL){/*��ʧ�ܻᱨ��*/
        printf("Failed to open data.txt.\n");
        return -1;
	}
	
	for(n = 0; n <114; n++){/*������ʵ��ֵ�����������*/
		fscanf(fp,"%d %d",DATA[n],(DATA[n]+1));
		N += DATA[n][1] ;/*�����ݵ����*/
		
		if(DATA[n][1] > N0) /*��Ƶ���Ͻ�����ѡ*/
		N0 = DATA[n][1];
	}
	
	fclose(fp);
	/*Schrage��������������ԣ�������ѡ�����������׳���*/ 
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &Q) ;
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    fp=fopen("tune2.txt","a+") ;     /*������ģ���ļ�*/
	fprintf(fp,"E/eV\n");/*��ӡ����*/
		
	I = seed; /*������ֵ����I0*/
	J = 0;
    
    for(n=0;n<Q;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
		 
		X = 2900 + (int)floor(113 * x);/*��ѡ����*/
		Y = y * N0;
		if( Y <= DATA[(int)floor(113 * x)][1]){
			fprintf(fp,"%d\n",X);
			J ++;
		}
		
		
	}
	
	fclose(fp);                          /*�ر��ļ�*/ 
    
    printf("%f",(double)J/Q) ;/*������ͨ��ѡ���ĳ���Ч��*/
    
    return 0;
    
}
