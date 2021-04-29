#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int RandomNumber( int N,int seed,int a,int m,int r,int q,char *string ){/*Schrage方法生成以连续两个随机数作为点的坐标值*/
    FILE *fp;/*存放随机数*/
    double x,y;/*（x,y）是随机点坐标*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    
    fp = fopen(string,"a+") ;
    fprintf(fp,"seed=%d\nx y\n",seed);/*表头*/
    
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
		
		fprintf(fp,"%f %f\n",x,y) ;       /*写入文件*/ 
		
	}
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

void kTest( int k, int a, int m, int r, int q, int seed, int N){   /*对给定的k用<xk>测试均匀性*/ 
	double x, S=0, test;/*x是随机数,S=x0^k+x1^k+……+xN-1^k，test用于计算|<x^k>-1/(k+1)|*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    FILE *fp;/*储存生成的k,|<x^k>-1/(k+1)|*/
    
    I = seed;/*将种子值赋给I0*/
    
    for( n = 0; n < N; n ++) {                   /*用In求出xn,然后用 Schrage方法求In+1,对xn^k从n=0到N-1求和为S*/ 
	
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	S = S + pow( x, (double)k ); 
	}

    test =  (double)S/N - (double)1/(k+1) ;       /*计算|<x^k>-1/(k+1)|*/
	if( test<0 )
	test = - test;
	
	fp=fopen("k-square test.txt","a+") ;     /*存储为矩检验文件*/
	fprintf(fp,"%d %f\n", k, test) ;
	fclose(fp);  
	return;
}

int main() {
	int a,b,m,r,q,N,seed;/*Schrage方法所需数据*/
	int k[5];/*<x^k>测试支持输入5个待测试的k*/ 
	char string[] = "data000";/*保存文件的名字*/ 
	int n,h;/*n是循环语句用到的变量，h是报错用的变量*/
	
	printf("Please input the number of your test.");/*输入实验序号*/ 
	scanf("%s",string+4);
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
	printf("Please input 5 k-values you would like to test.\n");/*输入5个k*/ 
	for( n=0; n<5; n++) {
	   scanf( "%d" , k+n );
	}
	
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = RandomNumber(N,seed,a,m,r,q,string);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to create random number.");
    
    for( n = 0; n < 5; n++ )/*依次进行5个k的矩检验*/ 
    kTest(k[n],a,m,r,q,seed,N) ;
	
	return 0; 
}
