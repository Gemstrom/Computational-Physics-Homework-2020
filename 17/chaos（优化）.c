#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
 
#define m 2000000/*用于生成(0，2)上的随机数*/ 

int seed ;/*初值x0来源*/
int R = 0;
int N;/*周期数上限*/ 
void sort(double *sample){/*对长为N，头指针sample的双精度数组进行排序*/
    int i,j;/*循环变量*/	
    double swap;/*交换用*/
    for( i = 0; i < N - 1 ; i ++){/*进行N-1趟排序*/
    	for(j = 0; j < N - 1 - i; j++) { /*每趟遍历前(N-i)个元素*/
    		if (*(sample + j) > *(sample + j + 1)){/*如果第j个元素和第(j+1)个元素的顺序不是从小到大，那么调转它们*/ 
    			swap = *(sample + j) ;
    			*(sample + j)  = *(sample + j + 1) ;
    			*(sample + j + 1 ) = swap ;
			}
		}
	}
}
void check( double lambda, double *sample){/*判断系统状态并生成文件*/
	int T = 1;/*周期数*/
	FILE *fp1, *fp2;/*用于存储系统状态和倍周期分叉*/ 
	double sp;/*对照使用*/
	int i;/*循环变量*/ 
	
	fp1 = fopen("data_lamda_new.txt","a+");
	fp2 = fopen("data_delta_new.txt","a+");
		
	sort(sample);/*排序*/
	
	sp = *sample;/*进行比较*/ 
	fprintf(fp1,"%f %f\n",lambda, sp);
	
	for( i = 1; i < N; i++ ) {
		if( sp != *(sample + i) ){/*出现新的迭代结果*/
			T ++;
			fprintf(fp1,"%f %f\n",lambda, *(sample + i));
			sp = *(sample + i);
		}
	}
	
	if(T == 1 && R == 0){
		fprintf(fp2,"%d %f\n", T, lambda);
		R = 1;
	}
	
	
	if(T < N && T == 2*R ) {/*分叉点*/
	    printf("R = %d\n",R) ;
		fprintf(fp2,"%d %f\n", T, lambda);
		R = 2 * R; 
	}
	
	fclose(fp1);
	fclose(fp2);
	
}

void chaos( double lambda , int n){
	double x; 
	int i;/*循环变量*/
	double *sample;/*采样数组*/
	
	sample = (double*)malloc(N * sizeof(double));
	x = (double) (seed%m)/m;
	
	for( i = 0; i < n; i ++ ){/*热化*/ 
		x = lambda * sin(3.14159 * x );
	}
	
	for( i = 0; i < N; i ++ ) {/*生成采样*/
	    *(sample + i) = x;
	    x = lambda * sin(3.14159 * x );
	}
	
	check(lambda, sample);
	
	free(sample);
	
}
int main() {
	double max, min, step = 0.000001;/*lambda的最值和步长*/
	int n;/*热化步数*/
	double lambda;/*计算的lambda*/
	FILE *fp1, *fp2;/*用于存储系统状态和倍周期分叉*/
	
	printf("Please input seed.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input lambda min.") ;/*输入lambda的最值*/
	scanf("%lf",&min);
	printf("Please input lambda max.") ;
	scanf("%lf",&max);
	
	lambda = min;
	
	printf("Please input the step of heating process.");/*输入热化步骤数目*/
	scanf("%d", &n) ;
	printf("Please input the maxim of cycle length.");/*输入最大周期数*/
	scanf("%d", &N) ;
	
	fp1 = fopen("data_lamda_new.txt","a+");
	fp2 = fopen("data_delta_new.txt","a+");
	fprintf(fp1,"lamda x\n");/*打印表头*/
	fprintf(fp2,"n lamda\n");
	fclose(fp1);
	fclose(fp2);
	
	do{
	    chaos(lambda, n);
	    lambda += step;
	}
	while( lambda < max );
	
	return 0;
	
}
