#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x) 0.1*exp(-pow((double)(x-3000),2.0)/50)
#define  e 7*pow(10.0,-7.0)  /*精度控制值*/


double Romberg(int b) { /*F(x)从2900到b的定积分数值*/
	int a = 2899;/*区间左端点2899右端点b*/
	int i,j,k;/*循环变量*/ 
	double *p1, *p2;/*用于存储第k-1和第k行的动态数组*/ 
	int N =121 - 1;/*取点数目N'=121*/
	double h;
	double S;/*S = \sum f(x0+h*0.5*i),i=0,1,……，2^(k-1)*/
	
	h = (double)(b - a);
	p1 = (double *) malloc(sizeof(double)*(1));/*Romberg积分的第0行*/
	*p1 = (F(a)+F(b))*h/2.0;
	if(p1 == NULL){/*报错*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( k=1; k <= N; k++ ){/*计算、存储Romberg积分的第k行，比较e和|R_k,k-R_k-1,k-1|直到误差符合要求，第k个循环中h=h_k-1=h*2^(-k+1)*/
		p2 = (double*)malloc(sizeof(double)*(k+1));/*Romberg积分的第k行,k=1,2,……，N*/
		if(p2 == NULL){/*报错*/ 
    	printf("memory allocation error\n");
    	return;
	    }
		
		S = 0;/*对S初始化*/
		for(i = 1; i <= pow(2.0,(double)(k-1)) ; i++){  /*计算梯形积分*/ 
			S += F(a + (2*i-1)* h/2);
		}
		*p2 = 0.5*(*p1 + h*S) ;
		for( j = 1; j <= k; j++ ){/*生成R_k,1到R_k,k*/
			*(p2+j)=(pow(4.0,(double)j) * ( *(p2+j-1) ) - *(p1 + j - 1))/(pow(4.0,(double)j) - 1);
		}
		
		if ( fabs(*(p2+k) - * (p1 + k-1 )) < e )/*判断精度是否符合要求*/
		return *(p2 + k);
		
		free(p1) ;
		p1 = p2 ;
		free(p2);
		h /= 2.0;
	}
	
}

int sample1 (double *z,double X0){/*当z[n]=X0时求最接近的整数解x*/
	int n;/*循环变量*/
	
	for(n = 0; n < 114; n ++){
		if( X0 <= *(z+n) )
		break;
	}
	
	if (n=114) 
	printf("?");
	
	return n+2900;
}


int main(){
	int a,b,m,r,q,Q,seed;/*Schrage方法所需数据*/
	int n;/*n是循环语句用到的变量*/
	FILE *fp;/*fp先用于导入数据，再用于保存生成的能量*/
	double X,Y;/*Schrage方法生成的随机数对*/ 
	int I;/*随机数生成的In*/
	int N = 0;/*N：实验数据点的个数*/
	int x,y;/*舍选法的分量*/
	int DATA[114][2];/*存放能谱的数组*/ 
	int J;/*成功抽样次数*/
	double z[114];/*积分值*/
	
	/*输入能谱*/ 
	fp = fopen("data.txt","r") ;
	
	if(fp == NULL){/*打开失败会报错*/
        printf("Failed to open data.txt.\n");
        return -1;
	}
	
	for(n = 0; n <114; n++){/*将能谱实验值输入数组待用*/
		fscanf(fp,"%d %d",DATA[n],(DATA[n]+1));
		N += DATA[n][1] ;/*求数据点个数*/
		z[n] = Romberg(DATA[n][0]);/*积分值*/
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
	
    fp=fopen("tune3.txt","a+") ;     /*打开能谱模拟文件*/
	fprintf(fp,"E/eV\n");/*打印标题*/
		
	I = seed; /*将种子值赋给I0*/
	J = 0;
    
    for(n=0;n<Q;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		X = (double)I/m;                    /*生成xn*/ 
		else
		X = Y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		Y = (double)I/m;                   /*生成x(n+1)=yn*/
		 
		x = sample1(z,X*z[113]);
		y = Y * F(x);
		
		if( y*N <= DATA[x-2900][1]){
			fprintf(fp,"%d\n",x);
			J ++;
		}
		
		
	}
	
	fclose(fp);                          /*关闭文件*/ 
    
    printf("%f",(double)J/Q) ;/*能谱普通舍选法的抽样效率*/
    
    return 0;
    
}
