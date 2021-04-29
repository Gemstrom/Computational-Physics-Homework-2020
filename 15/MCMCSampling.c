#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define a 16807/*Schrage��������*/
#define m 2147483647
#define r 2836
#define q 127773
int I;/*Schrage�������ɵ������*/ 
int n;/*n���Ȼ�������*/
int N;/*N�ǳ�������*/
double sx, sy;/*�ֲ�����*/
double delta;/*����*/ 

int MCMC( ) {/*Metropolis�����ͼ���<x^2>,<y^2>,<x^2+y^2>*/ 
	double x = 10,y = 10,xt,yt;/*��������(Ԥ��Ϊ(0,0)),��̽������*/
    double u;/*��Schrage�������ɵ������*/	
    int i;/*����*/ 
    double X = 0, Y = 0, Z = 0;    /*�ֱ���x^2,y^2,x^2+y^2�����*/
    FILE *fp;/*�洢������������*/
    double dH;/*������*/
    
    fp = fopen("Monte-Carol&Markov-Chain.txt","a+") ;
    fprintf(fp, "x y\n");/*��ͷ*/
    
    for( i = 0; i < n + N; i ++ ){/*Metropolis��������*/
    	/*x��̽��*/ 
		u = (double) I/m;
    	I= a * (I%q)- r*((I-(I%q))/q);      /*�����µ������I*/ 
		if( I < 0 )
		I = I + m ;
		
		xt = x + (u - 0.5) * delta ;
		
		/*y��̽��*/ 
		u = (double) I/m;
    	I= a * (I%q)- r*((I-(I%q))/q);      /*�����µ������I*/ 
		if( I < 0 )
		I = I + m ;
		
		yt = y + delta * (u - 0.5) ;
		
		/*����*/ 
		dH = 0.5 * ((pow(xt,2.0) - pow(x, 2.0) ) / pow(sx,2.0) + (pow(yt,2.0) - pow(y, 2.0) ) / pow(sy,2.0));
		
		if( dH < 0 ){/*���ܸò�*/
			x = xt;
			y = yt; 
		}
		
		else {
			u = (double) I/m;
    	    I= a * (I%q)- r*((I-(I%q))/q);      /*�����µ������I*/ 
		    if( I < 0 )
		    I = I + m ;
			
			if( u < exp(- dH) ){
				x = xt;
			    y = yt; 
			}
			
		}
		
		if( i >= n ){/*�Ȼ����������*/
			X += pow(x, 2.0);
		    Y += pow(y, 2.0);
		    Z += pow(x, 2.0) + pow(y, 2.0);
		
		}
		
		fprintf(fp, "%f %f\n",x,y);/*�������*/
		
	}
	
    fclose(fp) ;
    
    printf("<x^2>=%f,<y^2>=%f,<x^2+y^2>=%f\n",(double)X/N,(double)Y/N,(double)Z/N);
    
	return 0; 
}

int main(){
	int seed;/*seed������ֵ*/
	int i,h;/*ѭ���������������*/ 
	 
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the step of heating process.");/*�����Ȼ�������Ŀ*/
	scanf("%d", &n) ;
	
	printf("Please input the step of sampling.");/*�������������*/
	scanf("%d", &N) ;

	printf("Please input delta.");/*���벽��deltaֵ*/
	scanf("%lf", &delta);
		
	printf("Please input the value of sigma_x.");/*����sigmaxֵ*/
	scanf("%lf", &sx);
	
	printf("Please input the value of sigma_y.");/*����sigmayֵ*/
	scanf("%lf", &sy);
	
	I = seed;
	
	h = MCMC(delta) ;/*Metropolis���������ƽ��ֵ�����ӹ켣������Ƿ����*/
	if(h != 0 ) /*����*/
	printf("Error.\n");
	
	return 0 ; 
}
