#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
double w;/*正弦力场频率*/
double E;/*随机行走概率中场的影响大小*/

int OnedimensionRW( int a, int m, int r, int q, int seed, int N){   /*粒子的一维随机行走*/ 
	double x;/*x是随机数*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    FILE *fp;/*储存生成的粒子位移*/
    int S;/*向力场方向行走步数*/ 
    
	fp=fopen("1D RW.txt","a+") ;
	fprintf(fp,"x t(N)\n");
	
	S = 0;/*初始化S*/
    I = seed;/*将种子值赋给I0*/
    
    for( n = 0; n < N; n ++) {                   /*用In求出xn、行走方向,然后用 Schrage方法求In+1*/ 
	
	x = (double)I/m;
	
	if(0 < x && x < (1-E*sin(w*n))*0.5)            /*判断行走方向,更新位置，报错*/
	S --;
	else if(x > (1-E*sin(w*n))*0.5 && x<1 )
	S++;
	else{
		printf("Error.\n");
		return -1;
	}
	
	fprintf(fp,"%d %d\n",S,n+1);
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	}

	fclose(fp);  
	
	return 0;
}

int TwodimensionRW( int a,int m,int r,int q,int seed,int N){/*Schrage方法生成以连续两个随机数实现点的二维随机行走*/
    FILE *fp;/*存放随机数*/
    double x,y;/*（x,y）是随机点坐标*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    int X,Y;/*横、纵向位移*/
    
    fp = fopen("2D RW.txt","a+") ;
    fprintf(fp,"X Y N\n");/*表头*/
    
    X = 0;/*初始化位置*/ 
    Y = 0;
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
		
		if(0 < x && x < (1-E*sin(w*n))*0.5)            /*判断X行走方向,更新位置，报错*/
	    X --;
	    else if(x > (1-E*sin(w*n))*0.5 && x<1 )
	    X ++;
	    else{
		    printf("Error.\n");
		    return -1;
	    }
	    
	    if(0 < y && y < 0.5)            /*判断Y行走方向,更新位置，报错*/
	    Y --;
	    else if( y > 0.5 && y < 1 )
	    Y ++;
	    else{
		    printf("Error.\n");
		    return -1;
	    }
		
		fprintf(fp,"%d %d %d\n",X,Y,n+1) ;       /*写入文件*/ 
		
	}
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

void arrange( double x, double*p, int l){/*更新l>1的动态数组,用(p+l-2)到p所指向的数据依次覆盖(p+l-1)到（p+1）所指向的数据，然后将x存入p地址*/
	int j;/*循环变量*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}
int ThreedimensionRW( int a,int m,int r,int q,int seed,int N){/*Schrage方法生成以连续两个随机数实现点的三维随机行走*/
    FILE *fp;/*存放随机数*/
    double x;/*x是随机数*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    double X,Y,Z;/*三个方向位移*/
    double *p;/*p是长为3用于保存相邻三个随机数的数组头指针*/
    
    p = (double*) malloc(3*sizeof(double));/*创建头指针为p的动态数组，用于保存相邻的3个xn*/ 
    if(p == NULL){/*报错*/ 
    	printf("memory allocation error\n");
    	return;
	}
    
    fp = fopen("3D RW.txt","a+") ;
    fprintf(fp,"X Y Z N\n");/*表头*/
    
    X = 0;/*初始化位置*/ 
    Y = 0;
    Z = 0;
    I = seed; /*将种子值赋给I0*/
    
    for( n = 0 ; n < 3 ; n++ ){/*填充动态数组*/
	   x = (double)I/m;/*求xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1，循环结束时I=Il*/ 
		if( I < 0 )
				I = I + m ;
		
	   *( p + 2 - n )=x;/*将x0到xl-1依次赋给p+l-1到p指向的内存*/
	}
    /*长度为l的动态数组填充结束求S过程开始*/
    
    for( n = 3; n < N + 3; n ++){             /*用Schrage方法生成xl到xN+2,三位随机行走*/ 
    	if(0 < *(p+2) && *(p+2) < (1-E*sin(w*n))*0.5)            /*判断X行走方向,更新位置，报错*/
	    X --;
	    else if(*(p+2) > (1-E*sin(w*n))*0.5 && *(p+2)<1 )
	    X ++;
	    else{
		    printf("Error.\n");
		    return -1;
	    }
	    
	    Y += (*(p+1)) * cos(2.0*3.14*(*p));
	    Z += (*(p+1)) * sin(2.0*3.14*(*p));
    	
    	fprintf(fp,"%f %f %f %d\n",X,Y,Z,n-2);
    	
		x = (double)I/m;
    
    	arrange( x, p, 3);/*更新动态数组*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*用Schrage方法生成In+1*/ 
		if( I < 0 )
				I = I + m ;
	}
    
    free(p);/*释放动态数组内存*/
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

int main() {
	int a,b,m,r,q,N,seed;/*Schrage方法所需数据*/
	int n,h;/*n是循环语句用到的变量，h是报错用的变量*/
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the step.");/*输入数据量*/
	scanf("%d", &N) ;
	
	printf("Please input frequency.");/*输入力场频率*/
	scanf("%f", &w) ;
	
	printf("Please input the value of e.");/*输入力场频率*/
	scanf("%f", &E) ;
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = OnedimensionRW(a,m,r,q,seed,N);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to render 1D RW.");
    
    h = TwodimensionRW(a,m,r,q,seed,N);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to render 2D RW.");
	
	h = ThreedimensionRW(a,m,r,q,seed,N);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to render 3D RW.");
    
	return 0; 
}
