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

void sandbox(double Rg){/*sandbox法计算分维*/
	int R;/*最大半径*/
	int r0;/*计数半径*/ 
	int count = 1;/*占据格点数*/
	int i;/*循环变量*/
	FILE *fp;/*存放r,N数据*/ 
	
	fp = fopen("sandbox_count.txt" , "a+");
	fprintf(fp, "lnN lnr\n");/*打印表头*/
	
	R = floor( Rg ) ;
	
	for( r0 = 1; r0 <= R; r0++ ){/*对占据格点进行计数和输出*/
	
		for( i = center - r0; i <= center + r0; i++ ){
			count += field[center - r0][i] + field[center + r0][i];
		}
		for( i = center - r0 + 1; i <= center + r0 -1; i ++){
			count += field[i][center -r0] + field[i][center + r0];
		}
		
		fprintf(fp,"%f %f\n", log((double)count),log((double)r0));
	}
	
	fclose(fp) ;
	
}
int check( int step, int j, int k ) {/*检查j行k列的网格，如果里面有占据元素那么返回1，否则返回0*/
    int l,n;/*循环变量*/ 
    
	for( l = j * step + 1 ; l < (j + 1) * step + 1; l ++ ){ /*遍历这个网格里的各行*/
		for( n = k * step + 1 ; n < (k+1) * step + 1 ; n ++){ /*遍历选中这行的各个元素*/ 
			if( field[l][n] == 1 ) 
			return 1;/*出现占据元素返回1*/ 
		}
	}

    return 0;/*如果没找到就返回0*/
}
void boxcount() {/*盒计数法*/
	int i, j, k;/*循环变量*/
	FILE *fp; /*输出盒计数法检验的lnN和ln(1/epsilon)*/
	int step = 2 * N;/*检验的步长*/
	int n;/*N(epsilon)*/
	 
	fp = fopen("boxcount.txt","a+") ;
	fprintf(fp, "lnN ln(1/epsioln)\n");/*打印表头*/
	
	for( i = 0; i <= 11; i++ ) {
		
		n = 0;/*预置n*/ 
		step /= 2;/*求步长*/
		
		/*求占据网格数N*/ 
		for( j = 0; j < pow(2.0, i); j ++ ){  /*遍历各行*/
			for( k = 0; k < pow(2.0, i); k ++){/*遍历行内各列元素*/ 
				n += check(step,j,k) ;/*检查中心区域j行k列的方格，如果含有占据像素,n加一*/
			}
		}
		
		fprintf(fp, "%f %f\n",log((double)n), i*log(2.0)) ;/*将结果输出到文件*/
	}
	
	fclose(fp) ;/*关闭文件*/
	
}
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
	int seed, n;/*种子值，粒子数*/
	int i;/*循环变量*/
	FILE *fp;/*存放凝聚粒子位置*/
	int count = 1;/*保存的粒子数，用于进行分维计算*/ 
	int inf = 0;/*团簇的边界，用于保证粒子生成位置远离种子*/
	int S = 0;/*粒子到中心之距平方和，用于计算回转半径*/
	double Rg;/*回转半径*/
	
	printf("Please input seed.");/*输入种子值*/
	scanf("%d", &seed) ;
	I = seed;
	
	printf("Please input the number of particles.(1 to 419430)");/*输入粒子数*/
	scanf("%d", &n) ;
	
	if( n <= 0 || n > 419430 ){ /*粒子数太大或者太小报错*/
	    printf("Inapropriate particle number.\n");
	    return 0;
	}
	
	fp = fopen("location.txt","a+") ;/*保存凝聚的粒子位置*/
	
	field[center][center]=1;/*放置种子*/
	
	fprintf(fp, "x y\n");/*打印表头*/ 
	fprintf(fp, "%d %d\n", center,center);/*输出起始粒子坐标*/
	
	for(i = 0; i < n; i++) {/*进行n个粒子的DLA模拟*/
	
		if( dla( inf ) ){/*凝聚*/
			printf("Particle No.%d successfully aggregated.\n",i);
			
			if(abs(x - center) < inf)/*更新粒子生成区域*/
			inf = abs(x - center);
			if(abs(y - center) < inf)
			inf = abs(y - center);
			
			fprintf(fp, "%d %d\n", x,y);/*凝聚成功时输出粒子坐标*/
			count ++;/*更新粒子计数*/ 
			S += (x - center) * (x - center) + (y - center) * (y - center);
			continue;
		}
		
		printf("Particle No.%d escaped.\n",i);
		
	}
	
	fclose(fp) ;
	Rg = sqrt( (double) S / count ) ;
	printf("Rg = %f\ncount=%d\n", Rg, count) ;
	
	boxcount();
	sandbox(Rg);
	
	return 0 ;
}

