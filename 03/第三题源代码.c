#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int RandomNumber( int N,int seed,int a,int m,int r,int q ){/*Schrage方法生成以连续两个随机数作为点的坐标值*/
    FILE *fp;/*存放随机数*/
    double x,y;/*（x,y）是随机点坐标,简单抽样中rau=1,theta=acos(1-2x),phi=y/2Pi*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    
    fp = fopen("Spherical.txt","a+") ;
    fprintf(fp,"seed=%d\nrau theta phi\n",seed);/*表头*/
    
    I = seed; /*将种子值赋给I0*/
    
    for(n=0;n<N;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*生成xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I += m ;
		
		y = (double)I/m;                   /*生成x(n+1)=yn*/
		
		fprintf(fp,"1 %f %f\n",acos(1-2*x),y*(2*3.1415926)) ;       /*写入文件*/ 
		
	}
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

int main(){
	int a,m,r,q,N,seed;/*Schrage方法所需数据*/
	int j;/*报错使用*/
	
	a=16807;               /*生成Schrage方法所需数据*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
	j = RandomNumber( N, seed, a, m, r, q );/*通过函数RandomNumber的返回值进行检验*/
	if(j != 0 ) 
	printf("Failed to calculate random point upon spherical surface. Try again.\n") ;
	
	return 0;
}
