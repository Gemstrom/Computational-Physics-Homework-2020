#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MM 0.5    /*����*/
#define SS 0.5        /*��׼��*/

float sample(float x){
	if( 0 < x && x < 0.5)
	return 0.0;
	
	if(0.5< x && x < 1)
	return 1.0;
}
void arrange( double x, double*p, int l){/*����l>1�Ķ�̬����,��(p+l-2)��p��ָ����������θ���(p+l-1)����p+1����ָ������ݣ�Ȼ��x����p��ַ*/
	int j;/*ѭ������*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

void TEST1( int l, int a, int m, int r, int q, int seed, int N){   /*�Ը�����l����������飬����껯��z��������ļ�testl.txt*/ 
    double *p, x, S=0, z;/*p���ڱ������ڵ�l��xn��x�������,S=N<X>*/ 
    FILE *fp;/*�洢z*/
    int n,j;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    char s[14] = "Bernouli_N=00";
    
    if(l == 5)
    s[12] = '5';
    
    
    if(l == 10)
    s[11]='1';
    	  
    
    fp=fopen(s,"a+") ;     /*�洢z*/
    
    I = seed;/*������ֵ����I0*/
    
    p = (double*) malloc(l*sizeof(double));/*����ͷָ��Ϊp�Ķ�̬���飬���ڱ������ڵ�l��xn*/ 
    if(p == NULL){/*����*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( n = 0 ; n < l ; n++ ){/*��䶯̬����*/
	   x = (double)I/m;/*��xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1��ѭ������ʱI=Il*/ 
		if( I < 0 )
		I = I + m ; 
	   *( p + l - 1 - n )=x;/*��x0��xl-1���θ���p+l-1��pָ����ڴ�*/
	}
    /*����Ϊl�Ķ�̬������������S���̿�ʼ*/
    
    for( n = l; n < N + l; n ++){             /*��Schrage��������xl��xN+l-1����z*/ 
    	
    	for( j = 0; j < l; j++ ){
    		S += sample(*(p+j));
		}
		
		z = ((double)S/l -MM) /SS * sqrt((double)l);
    	fprintf(fp,"%f\n", z) ;
    	
		x = (double)I/m;
    	arrange( x, p, l);/*���¶�̬����*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1*/ 
		if( I < 0 )
				I = I + m ;
				
		S = 0;
	}
    
    free(p);/*�ͷŶ�̬�����ڴ�*/
	
	fclose(fp);  
    
    
    return; 
} 

void TEST2(int a, int m, int r, int q, int seed, int N){  /*�Ը�����l����������飬����껯��z��������ļ�test2.txt*/  
	FILE *fp;/*���z*/
    double x,y,z;/*��x,y�������������,z�Ǳ�׼����*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
     
	I = seed; /*������ֵ����I0*/
    fp=fopen("Bernouli_N=2.txt","a+") ;
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 ){
				I = I + m ; 
		}
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
		
		z = ((sample(x)+sample(y))/2.0- MM)/SS*sqrt(2.0);
		fprintf(fp,"%f\n", z) ;                    
	}
    
	fclose(fp);  
    
    
    return; 
}

int main() {
	int a,b,m,r,q,Q,seed;/*Schrage������������*/
	int n;/*n��ѭ������õ��ı���*/
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &Q) ;
    
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	TEST2(a,m,r,q,seed,Q);/*N=2*/ 
	TEST1(5,a,m,r,q,seed,Q);/*N=5*/
	TEST1(10,a,m,r,q,seed,Q);/*N=10*/
	
	return 0; 
} 
