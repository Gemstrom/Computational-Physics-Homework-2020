#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define MM 0.5    /*期望*/
#define SS sqrt((double)1/12)        /*标准差*/
void arrange( double x, double*p, int l){/*更新l>1的动态数组,用(p+l-2)到p所指向的数据依次覆盖(p+l-1)到（p+1）所指向的数据，然后将x存入p地址*/
	int j;/*循环变量*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

void TEST1( int l, int a, int m, int r, int q, int seed, int N){   /*对给定的l生成随机数组，计算标化和z，输出到文件testl.txt*/ 
    double *p, x, S=0, z;/*p用于保存相邻的l个xn，x是随机数,S=N<X>*/ 
    FILE *fp;/*存储z*/
    int n,j;/*循环变量*/ 
    int I;/*随机数生成的In*/
    char s[] = "uniformity_N=00.txt";
    
    if(l == 5)
    s[14] = '5';
    
    
    if(l == 10)
    s[13]='1';
    	  
    
    fp=fopen(s,"a+") ;     /*存储z*/
    
    I = seed;/*将种子值赋给I0*/
    
    p = (double*) malloc(l*sizeof(double));/*创建头指针为p的动态数组，用于保存相邻的l个xn*/ 
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
    /*长度为l的动态数组填充结束求S过程开始*/
    
    for( n = l; n < N + l; n ++){             /*用Schrage方法生成xl到xN+l-1，求S*/ 
    	
    	for( j = 0; j < l; j++ ){
    		S += *(p+j);
		}
		
		z = ((double)S/l -MM) /SS * sqrt((double)l);
    	fprintf(fp,"%f\n", z) ;
    	
		x = (double)I/m;
    	arrange( x, p, l);/*更新动态数组*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1*/ 
		if( I < 0 )
				I = I + m ;
				
		S = 0;
	}
    
    free(p);/*释放动态数组内存*/
	
	fclose(fp);  
    
    
    return; 
} 

void TEST2(int a, int m, int r, int q, int seed, int N){  /*对给定的l生成随机数组，计算标化和z，输出到文件test2.txt*/  
	FILE *fp;/*存放z*/
    double x,y,z;/*（x,y）是随机点坐标,z是标准化和*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
     
	I = seed; /*将种子值赋给I0*/
    fp=fopen("uniformity_N=2.txt","a+") ;
    for(n=0;n<N;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*生成xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 ){
				I = I + m ; 
		}
		
		y = (double)I/m;                   /*生成x(n+1)=yn*/
		
		z = ((x+y)/2.0- MM)/SS*sqrt(2.0);
		fprintf(fp,"%f\n", z) ;                    
	}
    
	fclose(fp);  
    
    
    return; 
}

int main() {
	int a,b,m,r,q,Q,seed;/*Schrage方法所需数据*/
	int n;/*n是循环语句用到的变量*/
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &Q) ;
    
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	TEST2(a,m,r,q,seed,Q);/*N=2*/ 
	TEST1(5,a,m,r,q,seed,Q);/*N=5*/
	TEST1(10,a,m,r,q,seed,Q);/*N=10*/
	
	return 0; 
} 
