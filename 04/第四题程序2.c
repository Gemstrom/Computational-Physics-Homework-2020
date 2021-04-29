#include<stdio.h> 
#include<math.h>

double lagrange( double y){/*通过函数lagrange求x(ξ)|ξ=y的数值*/
    double ksai[11] = {0,0.12903,0.2,0.23226,0.24516,0.25806,0.29032,0.36129,0.49032,0.69677,1};/*用于存放反函数插值点自变量ξ*/
	int n, i, j;/*循环用*/
	double l, S = 0 ;/*l存放li(ξ)的值；S存放L10(ξ)*/ 
		
	for( i = 0; i <11; i ++){
		l = 1; 
		for( j = 0 ; j < 10; j ++ ) {   /*计算li(y)的值*/
		    if( j == i )
		    continue;
		    
		    l *=  y - ksai[j] ;
		    l /=  ksai[i] - ksai[j] ;
		    
		} 
		
	    S += l * ( i - 5 ); /*和li（y)对应系数xi= i-5*/
	
    }
    
    return S;
}

int main(){
	double x, y;/*y是(0,1)上均匀分布随机数x是抽样*/
	int a,m,r,q,N,seed;/*Schrage方法所需数据*/
	int I;/*随机数生成的In*/
	FILE* fp;/*存储抽样随机数*/ 
    int n;/*循环变量*/ 
	double test;/*ξ(L(x)),和x对比可以得到插值的准确性*/ 
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
	a=16807;               /*生成Schrage方法所需数据*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	I = seed; 
	
	fp = fopen("sample2.txt","a+") ;
    fprintf(fp,"seed=%d\nξ x ξ(x)\n",seed);/*表头*/
	
	for( n = 0; n < N; n ++) {  /*用In求出yn,抽样xn写入文件然后用 Schrage方法求In+1*/ 
	
	y = (double)I/m;
	
	x = lagrange( y );
	
	test =(double) ( pow(x,3) +3*pow(x,2) +6 * x +80 )/310;
	
	fprintf(fp,"%f %f %f\n", y, x, test) ; 
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	}
	
	fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
}
