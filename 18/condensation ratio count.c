#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define a 16807/*Schrage方法数据*/
#define m 2147483647
#define r 2836
#define q 127773
#define N 2050/*考察区域边长*/ 
#define center 1025/*区域中心*/

int field[N][N]={};/*初始化,区域无粒子*/
int I;/*Schrage 方法随机数*/
int x,y;/*随机行走的粒子坐标*/

int dla( int inf ) {/*进行粒子从距离center>inf的区域开始的dla模拟*/
	int Q;/*用来存储余数进行判断，避免计算两次浪费算力*/
	
	/*生成不被占据的粒子初始位置x,y*/
	
	do{
		do{
		Q = I % (N - 1 - 2*inf) ;

	    I= a * (I%q)- r*((I-(I%q))/q);      /*更新Schrage方法生成的随机数*/ 
	    if( I < 0 )
     	I = I + m ;
	
	    }
	    while( Q == 0 || Q == N - 2 - 2 * inf );           /*Q不在生长区域则舍去，更新Schrage方法生成的随机数,重新生成Q直到符合条件为止*/ 
		
    	if( Q < center - inf ){
		    x = Q;
	    }
	    else
	        x = Q + 1 + 2*inf;
	    
	    do{
		    Q = I % (N - 1 - 2*inf) ;

	        I= a * (I%q)- r*((I-(I%q))/q);      /*更新Schrage方法生成的随机数*/ 
	        if( I < 0 )
     	    I = I + m ;
	
	    }
	    while( Q == 0 || Q == N - 2 - 2 * inf );            /*Q不在生长区域则舍去，更新Schrage方法生成的随机数,重新生成Q直到符合条件为止*/ 
		
	    if( Q < center - inf ){
	    	y = Q;
	    }
	    else
	        y = Q + 1 + 2*inf;
	    
	} 
	while( field[y][x] == 1 );
	
	/*没有被粘住的时候进行随机行走*/   
	while(field[y+1][x] == 0 && field[y-1][x] == 0 && field[y][x+1] == 0 && field[y][x-1] == 0 ){
		
		switch(I%4) {/*random walk*/
			case 0: x++; break;
			case 1: x--; break;
			case 2: y++; break;
			case 3: y--; break;
		}
	
		I= a * (I%q)- r*((I-(I%q))/q);      /*更新Schrage方法生成的随机数*/ 
	    if( I < 0 )
	    I = I + m ;	
	    
		if( x < 1 || x > N - 2 || y < 1 || y > N - 2 ) {/*粒子逃离*/
			return 0;
		}
	}
	
	/*被粘住了就退出循环，此时粒子的坐标是field[x][y]*/ 
    field[y][x] = 1;/*占据*/
    return 1; 
}
int main() {
	int seed;/*种子值*/
	int i, j = 10;/*循环变量*/
	FILE *fp;/*存放凝聚粒子位置*/
	int count = 1;/*保存的粒子数，用于进行分维计算*/ 
	int inf = 0;/*团簇的边界，用于保证粒子生成位置远离种子*/
	int S = 0;/*粒子到中心之距平方和，用于计算回转半径*/
	double Rg;/*回转半径*/
	
	printf("Please input seed.");/*输入种子值*/
	scanf("%d", &seed) ;
	I = seed;
	
	fp = fopen("condensation ratio count.txt","a+") ;/*保存凝聚的粒子位置*/
	
	field[center][center]=1;/*放置种子*/
	
	fprintf(fp, "n condensation_ratio\n");/*打印表头*/ 
	
	for(i = 0; i < 419430; i++) {/*进行n个粒子的DLA模拟*/
	    printf("i=%d\n",i);
	    
		if( dla( inf ) ){/*凝聚*/
		
			if(abs(x - center) < inf)/*更新粒子生成区域*/
			inf = abs(x - center);
			if(abs(y - center) < inf)
			inf = abs(y - center);
			
			count ++;/*更新粒子计数*/ 
		}
	
	    if( i == 10*j -1 ){/*每隔10个粒子进行一次取样计算凝聚率*/
	        printf("j = %d\n", j);
	    	fprintf(fp, "%d %f\n", i+1, (double)count/(i+1) );/*输出粒子数目和凝聚率*/ 
	    	j ++;
		}
		
	}
	
	printf("j=%d\n",j);
	
	fclose(fp) ;
	
	return 0 ;
}

