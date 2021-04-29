#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int Marsaglia(int N,int seed,int a,int m,int r,int q){/*Schrage方法生成以连续两个随机数抽样和变换后作为点投影的坐标值*/
    FILE *fp;/*存放随机数*/
    double X,Y,x,y;/*X,Y是(0,1)上均匀分布随机数，(x,y)随机点投影坐标*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    
    fp = fopen("MarsagliaSampling.txt","a+") ;
    fprintf(fp,"seed=%d\nx y\n",seed);/*表头*/
    
    I = seed; /*将种子值赋给I0*/
    
    for(n=0;n<N;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		X = (double)I/m;                    /*生成xn*/ 
		else
		X = Y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		Y = (double)I/m;                   /*生成x(n+1)=yn*/
		
		if( pow((2*X-1),(double)2) + pow((2*Y-1),(double)2) <= 1 ){/*舍选法判断*/
			x = 2 * ( 2 * X - 1 ) * sqrt( 1- pow((2*X-1),(double)2) - pow((2*Y-1),(double)2) );/*抽样*/ 
			y = 2 * ( 2 * Y - 1 ) * sqrt( 1- pow((2*X-1),(double)2) - pow((2*Y-1),(double)2) );
			fprintf(fp,"%f %f\n",x,y) ;       /*写入文件*/ 
		} 				
		
	}
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

int main() {
	int a,m,r,q,N,seed;/*Schrage方法所需数据*/
	int n,h;/*n是循环语句用到的变量，h是报错用的变量*/
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
    a=16807;               /*生成Schrage方法所需数据*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = Marsaglia(N,seed,a,m,r,q);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to create random number.");
    
	return 0; 
}
