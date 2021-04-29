#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#define a 16807/*Schrage方法数据*/
#define m 2147483647
#define r 2836
#define q 127773

int I;/*Schrage方法生成的随机数*/ 
int RW1( int* A1 , int*A2, int NN ) { /*NN个粒子坐标构成2个长度为NN的一维随机数组进行一步二维随机行走,返回回到出发点的粒子数*/
	int n;/*循环变量*/ 
	double x;
	int T = 0;/*在原点的粒子数*/ 
	for(n = 0; n < NN; n ++) {     /*Schrage方法生成随机数x用于进行一维随机行走*/ 
		x = (double)I/m;/*生成x*/ 
		 
		if(x <= 0.25 && x >= 0 ) {/*二维随机行走*/ 
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
	    	printf("RW Error.");/*报错*/
	    	return -1; 
		}
		
		if( *(A1+n) == 0 && *(A2+n) == 0 ) /*计数*/ 
		T ++;
		
	    I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	}
	return T;
}
int main(){
	int N, NN;/*N是粒子步数，NN是粒子数*/ 
	int *p1,*p2;/*粒子x,y方向位移*/
	int n;/*粒子运动步数*/ 
	int h;/*Pd*/
	FILE *fp;/*Pd(N)文件*/ 
	
	printf("Please input seed.");/*输入种子值*/
	scanf("%d", &I) ;
	
	printf("Please input the step of each particle.");/*输入单粒子步数*/
	scanf("%d", &N) ;
	
	printf("Please input the number of particle.");/*输入粒子数*/
	scanf("%d", &NN) ;
	
	fp=fopen("2D RW.txt","a+") ;
	fprintf(fp,"Pd(N) N\n");
	 
	p1 = (int *) malloc(NN*sizeof(int));
	p2 = (int *) malloc(NN*sizeof(int));
	
	for(n=0; n< N; n++) {/*进行N步随机行走*/
		h = RW1(p1, p2, NN);
		if(h < 0) {
			printf("Error.");/*报错*/
		}
		if( n%2 == 1 )/*步数为偶数的点*/
		fprintf(fp,"%f %d\n",(double)h/NN,n+1);/*输出第n步的Pd*/ 
	}
	free(p1);
	free(p2);
	
	fclose(fp);  
	
	return 0;
}
