#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define a 16807/*Schrage方法数据*/
#define m 2147483647
#define r 2836
#define q 127773
int I;/*Schrage方法生成的随机数*/ 
int n;/*n是热化步骤数*/
int N;/*N是抽样步骤*/
double sx, sy;/*分布参数*/
double delta;/*步长*/ 

int MCMC( ) {/*Metropolis抽样和计算<x^2>,<y^2>,<x^2+y^2>*/ 
	double x = 10,y = 10,xt,yt;/*粒子坐标(预置为(0,0)),试探步坐标*/
    double u;/*用Schrage方法生成的随机数*/	
    int i;/*步数*/ 
    double X = 0, Y = 0, Z = 0;    /*分别是x^2,y^2,x^2+y^2的求和*/
    FILE *fp;/*存储粒子坐标数据*/
    double dH;/*能量差*/
    
    fp = fopen("Monte-Carol&Markov-Chain.txt","a+") ;
    fprintf(fp, "x y\n");/*表头*/
    
    for( i = 0; i < n + N; i ++ ){/*Metropolis方法抽样*/
    	/*x试探步*/ 
		u = (double) I/m;
    	I= a * (I%q)- r*((I-(I%q))/q);      /*生成新的随机数I*/ 
		if( I < 0 )
		I = I + m ;
		
		xt = x + (u - 0.5) * delta ;
		
		/*y试探步*/ 
		u = (double) I/m;
    	I= a * (I%q)- r*((I-(I%q))/q);      /*生成新的随机数I*/ 
		if( I < 0 )
		I = I + m ;
		
		yt = y + delta * (u - 0.5) ;
		
		/*抽样*/ 
		dH = 0.5 * ((pow(xt,2.0) - pow(x, 2.0) ) / pow(sx,2.0) + (pow(yt,2.0) - pow(y, 2.0) ) / pow(sy,2.0));
		
		if( dH < 0 ){/*接受该步*/
			x = xt;
			y = yt; 
		}
		
		else {
			u = (double) I/m;
    	    I= a * (I%q)- r*((I-(I%q))/q);      /*生成新的随机数I*/ 
		    if( I < 0 )
		    I = I + m ;
			
			if( u < exp(- dH) ){
				x = xt;
			    y = yt; 
			}
			
		}
		
		if( i >= n ){/*热化结束后计数*/
			X += pow(x, 2.0);
		    Y += pow(y, 2.0);
		    Z += pow(x, 2.0) + pow(y, 2.0);
		
		}
		
		fprintf(fp, "%f %f\n",x,y);/*输出坐标*/
		
	}
	
    fclose(fp) ;
    
    printf("<x^2>=%f,<y^2>=%f,<x^2+y^2>=%f\n",(double)X/N,(double)Y/N,(double)Z/N);
    
	return 0; 
}

int main(){
	int seed;/*seed是种子值*/
	int i,h;/*循环变量，报错变量*/ 
	 
	printf("Please input seed.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the step of heating process.");/*输入热化步骤数目*/
	scanf("%d", &n) ;
	
	printf("Please input the step of sampling.");/*输入抽样步骤数*/
	scanf("%d", &N) ;

	printf("Please input delta.");/*输入步长delta值*/
	scanf("%lf", &delta);
		
	printf("Please input the value of sigma_x.");/*输入sigmax值*/
	scanf("%lf", &sx);
	
	printf("Please input the value of sigma_y.");/*输入sigmay值*/
	scanf("%lf", &sy);
	
	I = seed;
	
	h = MCMC(delta) ;/*Metropolis抽样，输出平均值和粒子轨迹，检查是否错误*/
	if(h != 0 ) /*报错*/
	printf("Error.\n");
	
	return 0 ; 
}
