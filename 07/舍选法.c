#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int main(){
	int a,b,m,r,q,Q,seed;/*Schrage方法所需数据*/
	int n;/*n是循环语句用到的变量*/
	FILE *fp;/*fp先用于导入数据，再用于保存生成的能量*/
	double x,y;/*Schrage方法生成的随机数对*/ 
	int I;/*随机数生成的In*/
	int N = 0, N0=0;/*N：实验数据点的个数，N0：频数上界*/
	int X,Y;/*舍选法的分量*/
	int DATA[114][2];/*存放能谱的数组*/ 
	int J;/*成功抽样次数*/
	
	/*输入能谱*/ 
	fp = fopen("data.txt","r") ;
	
	if(fp == NULL){/*打开失败会报错*/
        printf("Failed to open data.txt.\n");
        return -1;
	}
	
	for(n = 0; n <114; n++){/*将能谱实验值输入数组待用*/
		fscanf(fp,"%d %d",DATA[n],(DATA[n]+1));
		N += DATA[n][1] ;/*求数据点个数*/
		
		if(DATA[n][1] > N0) /*求频数上界以舍选*/
		N0 = DATA[n][1];
	}
	
	fclose(fp);
	/*Schrage方法生成随机数对，进行舍选法，产生能谱抽样*/ 
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &Q) ;
	
    a=16807;               /*生成Schrage方法所需数据*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    fp=fopen("tune2.txt","a+") ;     /*打开能谱模拟文件*/
	fprintf(fp,"E/eV\n");/*打印标题*/
		
	I = seed; /*将种子值赋给I0*/
	J = 0;
    
    for(n=0;n<Q;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*生成xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*生成x(n+1)=yn*/
		 
		X = 2900 + (int)floor(113 * x);/*舍选抽样*/
		Y = y * N0;
		if( Y <= DATA[(int)floor(113 * x)][1]){
			fprintf(fp,"%d\n",X);
			J ++;
		}
		
		
	}
	
	fclose(fp);                          /*关闭文件*/ 
    
    printf("%f",(double)J/Q) ;/*能谱普通舍选法的抽样效率*/
    
    return 0;
    
}
