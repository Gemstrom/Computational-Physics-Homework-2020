#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int RandomNumber( int N,int seed,int a,int m,int r,int q){/*Schrage方法生成以连续两个随机数作为点的坐标值*/
    FILE *fp;/*存放随机数*/
    double x,y;/*（x,y）是随机点坐标*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    double X,Y;/*随机抽样值*/
    
    fp = fopen("sampling.txt","a+") ;
    fprintf(fp,"seed=%d\nx\n",seed);/*表头*/
    
    I = seed; /*将种子值赋给I0*/
    
    for(n=0;n<N;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*生成xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*生成x(n+1)=yn*/
		
		X = -5 + 10*x;/*生成对应的(X,Y)*/ 
		Y = (double) 3/310 + (double) 54 * y / 155;
		 
		if( Y <= ((double)3/310 * ( pow(x,(double)2) + 2 *x + 2)) )
		fprintf(fp,"%f\n",X) ;       /*将生成的抽样随机数X写入文件*/ 
		
	}
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

int main() {
	int a,b,m,r,q,N,seed;/*Schrage方法所需数据*/
	int n,h;/*n是循环语句用到的变量，h是报错用的变量*/
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
	a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	h = RandomNumber(N,seed,a,m,r,q);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to create random number.");
    
    return 0; 
}
