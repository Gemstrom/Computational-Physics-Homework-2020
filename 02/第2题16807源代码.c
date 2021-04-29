#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int main() {
	int a,m,r,q,N,seed;/*Schrage方法所需数据*/
	int n, I, S;/*S是满足条件的xn的个数；n是循环语句所用变量；I在Schrage方法中使用*/ 
	double x, y, z;/*x,y,z存放xn-1,xn,xn+1*/  
    FILE *fp;/*创建一个文件用于写入N和比重，用于分析无穷多随机数中满足条件的数的比重*/ 
    
    printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	    
    a=16807;               /*生成Schrage方法所需数据*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	I = seed;/*将种子值赋给I0，依次由Schrage方法生成x0，1，2*/
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成I1*/ 
		if( I < 0 ){
				I = I + m ;
		}
		
	y = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成I2*/ 
		if( I < 0 ){
				I = I + m ;
		}
	
	z = (double)I/m;
	
	if( x < z && z < y )/*n=1，当xn-1<xn<xn+1个数的计数加一*/
	  S ++;
	    
    
	for( n = 2; n <= N; n ++) {/*变量取值n的循环，通过将y,z的值拷贝到x,y先将xn-1,xn依次赋给x,y，再由上个周期生成的In生成In+1、生成z，判断x,y,z是否满足条件，若满足则增加计数*/ 
		x = y;
		y = z;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成I1*/ 
		if( I < 0 ){
				I = I + m ;
		}
		
	    z = (double)I/m;
	    
	if( x < z && z < y )/*当xn-1<xn<xn+1个数的计数加一*/
	  S ++;
	    
	}
	
    printf("%f", (double)S/N ) ;/*输出满足条件随机数比重*/
    
    fp = fopen("OriginData16807.txt","a+") ;/*保存不同N的比重*/
    fprintf(fp,"%d %f\n",N, (double)S/N );
    fclose(fp);
    
	return 0;
}
