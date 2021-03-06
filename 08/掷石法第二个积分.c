#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x,y,z,u,v)  6-pow((x),2.0)-pow((y),2.0)-pow((z),2.0)-pow((u),2.0)-pow((v),2.0)

void arrange( double x, double*p, int l){/*更新l>1的动态数组,用(p+l-2)到p所指向的数据依次覆盖(p+l-1)到（p+1）所指向的数据，然后将x存入p地址*/
	int j;/*循环变量*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

void stone( int a, int m, int r, int q, int seed, int N){  
    double *p,x, test,X;/*p用于保存相邻的l=6个xn，x是随机数,test=F(x,y,z,u,v),X是Xp*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的Ij*/
    int l = 6;/*随机数组的长*/
    int Q = 0;/*成功抽样次数*/
    
    I = seed;/*将种子值赋给I0*/
    
    p = (double*) malloc( 6 * sizeof(double));/*创建头指针为p的动态数组，用于保存相邻的l个xn*/ 
    if(p == NULL){/*报错*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( n = 0 ; n < l ; n++ ){/*填充动态数组*/
	   x = (double)I/m;/*求xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1，循环结束时I=Il*/ 
		if( I < 0 )
				I = I + m ;
				
		*( p + l - 1 - n )=x;/*将x0到xl-1依次赋给p+l-1到p指向的内存*/
	}
    /*长度为l的动态数组填充结束求积分过程开始*/
    
    
    for( n = l; n < N + l; n ++){             /*用Schrage方法生成xl到xN+l-1，进行掷石法积分*/ 
    	x = (double)I/m;
    	
    	X = -1.95 + 7.95 * (*p);
    	test = F(0.9*(*(p+5)),0.8*(*(p+4)),0.9*(*(p+3)),2.0*(*(p+3)),1.3*(*(p+1)));
		
		if(test > X && X > 0 )
		{  Q++;
		  
		}
		
    	else if(test < X && X< 0)
    	{   Q--;
         
		}
		 
    	arrange( x, p, l);/*更新动态数组*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	}
    
    free(p);/*释放动态数组内存*/
    
    printf("%f",13.39416*(double)Q/N) ;/*输出积分值*/ 
    
    return; 
} 

int main() {
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
	
	stone(a,m,r,q,seed,N);
	
	return 0; 
}
