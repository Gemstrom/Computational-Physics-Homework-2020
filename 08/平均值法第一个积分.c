#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define f(x) sqrt( x+sqrt(x))

void avr( int a, int m, int r, int q, int seed, int N){  /*计算积分和标准差*/ 
	double x, S=0, T = 0;/*x是随机数,y指f(x)，S=y0^2+y1^2+……+yN-1^2，T=y0+y1+……+yN-1，由S、T得到标准差*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    
    I = seed;/*将种子值赋给I0*/
    
    for( n = 0; n < N; n ++) {                   /*用In求出xn,然后用 Schrage方法求In+1*/ 
	
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	S += pow( f(2*x), 2.0 ); 
	T += f(2*x);
	}
    
    printf("integer=%f\n sigma = %f\n",(double)T/N*2,sqrt((double)S/N-pow((double)T/N,2.0))*2/sqrt((double)N)) ;/*通过数组返回标准差*/
    
	return;
}

int main(){
	int a,b,m,r,q,N,seed;/*Schrage方法所需数据*/ 
	int n;/*n是循环语句用到的变量*/
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	 
    avr(a,m,r,q,seed,N);
	
	return 0; 
}
