#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int Sample(double x) {
	int n;/*循环变量*/
	int N = 0;/*实验数据点的个数*/
	int P = 0 ;/*N0+N1+……+Nn*/
	FILE *fp;/*data.txt的指针*/ 
	int DATA[114][2];
	
	fp = fopen("data.txt","r") ;
	
	if(fp == NULL){/*打开失败会报错*/
        printf("Failed to open data.txt.\n");
        return -1;
	}
	
	for(n = 0; n <114; n++){/*将能谱实验值输入数组待用*/
		fscanf(fp,"%d %d",DATA[n],(DATA[n]+1));
		N += DATA[n][1] ;/*求数据点个数*/
	}
	
	fclose(fp);
	
	x *= N;/*因比较N*x和P，求出比较量Nx赋给x节省内存*/ 
	
	n = 0;
	do{                   /*比较xN和P找到满足条件的n，循环结束时n的值是符合条件的n+1*/ 
		P += DATA[n][1];
		n ++; 
	} 
	while(x > P );
	n --;
	
    return (n+2900) ;/*返回能量*/
}

int main() {
	int a,b,m,r,q,Q,seed;/*Schrage方法所需数据*/
	int n;/*n是循环语句用到的变量*/
	FILE *fp;/*储存生成的能量*/
	double x;/*Schrage方法生成的随机数*/ 
	int I;/*随机数生成的In*/
	
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &Q) ;
	
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    fp=fopen("tune1.txt","a+") ;     /*打开能谱模拟文件*/
	fprintf(fp,"E/eV\n");/*打印标题*/
	
	I = seed;/*将种子值赋给I0*/
    
    for( n = 0; n < Q; n ++) {                   /*用In求出xn,然后用 Schrage方法求In+1,将xn导入Sample生成E*/ 
	
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
	fprintf(fp,"%d\n",Sample(x)) ;
	}

	fclose(fp); 
	return 0; 
}
