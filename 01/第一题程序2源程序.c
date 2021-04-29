#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

void arrange( double x, double*p, int l){/*更新l>1的动态数组,用(p+l-2)到p所指向的数据依次覆盖(p+l-1)到（p+1）所指向的数据，然后将x存入p地址*/
	int j;/*循环变量*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

void lTest( int l, int a, int m, int r, int q, int seed, int N){   /*对给定的l用C(l)测试2维独立性*/ 
    double *p, x, S=0, T=0,test;/*p用于保存相邻的l个xn，x是随机数,S=N<xnxn+l>,T=x0+x1+……+xN+l-1,test=|C(l)|*/ 
    FILE *fp;/*存放l,C(l)*/
    int n;/*循环变量*/ 
    int I;/*随机数生成的Ij*/
    
    I = seed;/*将种子值赋给I0*/
    
    p = (double*) malloc(l);/*创建头指针为p的动态数组，用于保存相邻的l个xn*/ 
    if(p == NULL){/*报错*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( n = 0 ; n < l ; n++ ){/*填充动态数组*/
	   x = (double)I/m;/*求xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1，循环结束时I=Il*/ 
		if( I < 0 )
				I = I + m ;
		
	   T = T + x;/*循环结束时T=x0+x1+……+xl-1*/ 
	   *( p + l - 1 - n )=x;/*将x0到xl-1依次赋给p+l-1到p指向的内存*/
	}
    /*长度为l的动态数组填充结束求S过程开始*/
    
    for( n = l; n < N + l; n ++){             /*用Schrage方法生成xl到xN+l-1，求S、T*/ 
    	x = (double)I/m;
    	
    	T = T + x;
    	
    	S = S + x*( *( p + l - 1 ));
    	
    	arrange( x, p, l);/*更新动态数组*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1*/ 
		if( I < 0 )
				I = I + m ;
	}
    
    free(p);/*释放动态数组内存*/
    
    test =  (double)S/N - pow((double)T/(N+l),(double)2) ;       /*计算|C(l)|*/
	if( test<0 )
	test = - test;
	
	fp=fopen("l-square test.txt","a+") ;     /*存储C(l)*/
	fprintf(fp,"%d %f\n", l, test) ;
	fclose(fp);  
    
    
    return; 
} 

void lTest2(int a, int m, int r, int q, int seed, int N){ /*用C(1)测试2维独立性*/ 
	FILE *fp;/*存放|C(l)|*/
    double x,y,S,T,test;/*（x,y）是随机点坐标,S用于存放x0x1+……+xN-1xN,T=x0+……+xN*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    
    S = 0;
    T = 0;
	I = seed; /*将种子值赋给I0*/
    
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
		
		S += x*y;                          
		T += x;
	}
    
    T += y; /*循环结束时S=x0x1+……+xN-1xN,T=x0+……+xN-1，y=xN，补上y*/ 
    
    test = (double)S/N - pow((double)T/(N+1),(double)2);
    if( test<0 )
	test = - test;
	
    fp=fopen("l-square test.txt","a+") ;     /*存储C(l)*/
	fprintf(fp,"1 %f\n", test) ;
	fclose(fp);  
    
    
    return; 
}

int main() {
	int a,b,m,r,q,N,seed;/*Schrage方法所需数据*/
	int l[5];/*C(l)支持输入5个待测试的l*/ 
	char string[] = "data000";/*保存文件的名字*/ 
	int n,h;/*n是循环语句用到的变量*/
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
	printf("Please input 5 l-values you would like to test.\n");/*输入5个l*/ 
	for( n=0; n<5; n++) {
	   scanf( "%d" , l+n );
	}
    
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	 
	for( n = 0; n < 5; n++ ){/*依次进行5个l的C(l)检验*/  
	    if( l[n] < N && l[n] > 1  )
		lTest(l[n],a,m,r,q,seed,N);
    
        else if(l[n] == 1)
        lTest2(a,m,r,q,seed,N);
        
        else
        printf("Illegal l-value.");
	}
	return 0; 
}
