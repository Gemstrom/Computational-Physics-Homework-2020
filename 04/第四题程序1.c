#include<stdio.h> 
#include<math.h>

#define L(x) -4.999999999999999-1679.414511925006*x+1306.604336498538*pow(x,2.0)+718483.6883936822*pow(x,3.0)-11057257.78954862*pow(x,4.0)+77264158.80698961*pow(x,5.0)-302904372.690824*pow(x,6.0)+702521844.3357706*pow(x,7.0)-950240462.1130562*pow(x,8.0)+687294971.9494734*pow(x,9.0)-203596983.3770245*pow(x,10.0)
int main(){
	/*取样*/
	int n;/*循环变量*/
	double z;/*满足p(x)抽样概率的随机数x*/
	/*Schrage方法生成随机数*/ 
	FILE *fp;/*存放随机数*/
	int I;/*随机数生成的In*/
	int a,m,r,q,N,seed;/*Schrage方法所需数据*/
	double y;/*随机生成的ξ*/
	double test;/*ξ(L(x)),和x对比可以得到插值的准确性*/ 
	
	a=16807;               /*生成Schrage方法所需数据*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	/*输入待定数据*/ 
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
	/*打开文件*/ 
	fp = fopen("sample1.txt","a+") ;
    fprintf(fp,"seed=%d\nξ x ξ(x)\n",seed);/*表头*/
    
    I = seed; /*将种子值赋给I0*/
    
    for( n = 0; n < N; n ++) {                   /*用In求出ξn,然后用 Schrage方法求In+1,由ξn求xn，ξ（xn)，输出到文件"sample1.txt"*/ 
	
	y = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	z =  L(y);
	
	test =(double) ( pow(z,3) +3*pow(z,2) +6 * z +80 )/310;
	fprintf(fp,"%f %f %f\n",y,z,test);
	}
	fclose(fp);
	
	return 0;
}
