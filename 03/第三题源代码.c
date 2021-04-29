#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int RandomNumber( int N,int seed,int a,int m,int r,int q ){/*Schrage�������������������������Ϊ�������ֵ*/
    FILE *fp;/*��������*/
    double x,y;/*��x,y�������������,�򵥳�����rau=1,theta=acos(1-2x),phi=y/2Pi*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    
    fp = fopen("Spherical.txt","a+") ;
    fprintf(fp,"seed=%d\nrau theta phi\n",seed);/*��ͷ*/
    
    I = seed; /*������ֵ����I0*/
    
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I += m ;
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
		
		fprintf(fp,"1 %f %f\n",acos(1-2*x),y*(2*3.1415926)) ;       /*д���ļ�*/ 
		
	}
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

int main(){
	int a,m,r,q,N,seed;/*Schrage������������*/
	int j;/*����ʹ��*/
	
	a=16807;               /*����Schrage������������*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
	j = RandomNumber( N, seed, a, m, r, q );/*ͨ������RandomNumber�ķ���ֵ���м���*/
	if(j != 0 ) 
	printf("Failed to calculate random point upon spherical surface. Try again.\n") ;
	
	return 0;
}
