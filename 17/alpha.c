#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#define epsom 0.001 
#define m 2000000/*用于生成(0，2)上的随机数*/ 

int seed ;/*初值x0来源*/
int r = 0;
int N;/*周期数上限*/ 
double *array;

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
int check( double lambda, double *sample){/*判断系统状态并返回周期数*/
	int T = 1;/*周期数*/
	double sp;/*对照使用*/
	int i;/*循环变量*/ 

	sort(sample);/*排序*/
	
	sp = *sample;/*进行比较*/ 
	*array = sp;

	for( i = 1; i < N; i++ ) {
		if( fabs(sp - *(sample + i)) >= epsom ){/*出现新的迭代结果*/
			*(array + T ) = *(sample + i);
			sp = *(sample + i);
			T ++;
		}
	}
	
	return T;
}

int seek( double key, int T){/*找到array前T个元素中是否有0.5，如果没有返回-1如果有就返回位置*/
      int low = 0, high = T-1, mid;/*搜索范围上下限和中点*/ 
	  
	  while( low <= high ){
	  	mid = (low + high )/2;
	  	
	  	if( fabs(key - *(array + mid)) <= epsom ){
			return mid;
		}
	  	if( key < *(array + mid ) - epsom ){
	  		high = mid - 1;
		  }
		  
		if( key > *(array + mid ) + epsom){
	  		low = mid + 1;
		  }
	
	  }

     return -1;
}
void chaos( double lambda , int n){
	double x; 
	int i, T, h;/*循环变量，周期长度，指示变量*/
	double *sample;/*采样数组*/
	FILE *fp;/*存放T,m,d_m*/
	
	sample = (double*)malloc(N * sizeof(double));
	x = (double) (seed%m)/m;
	
	for( i = 0; i < n; i ++ ){/*热化*/ 
		x = lambda * sin(3.14159 * x );
	}
	
	for( i = 0; i < N; i ++ ) {/*生成采样*/
	    *(sample + i) = x;
	    x = lambda * sin(3.14159 * x );
	}
	
	T = check(lambda, sample);
	if( T == (int) pow(2.0, r+1) && T < N ) {/*N比较大时T<N是冗余的，此处防止N输入值比较小会出错*/
		h = seek( 0.5, T ) ;/*二分法找array前T个元素有没有和0.5差距在0.000001以内的*/
		
		if( h >= 0 ){/*0.5在周期内*/
			fp = fopen("data_alpha.txt","a+");
			
	        if( h % 2 == 1){/*h是奇数*/
	        	fprintf(fp,"%d %d %f\n", T, r, *(array + h) - *(array + h - 1));
			}
			
			else if( h % 2 == 0){/*h是偶数*/
	        	fprintf(fp,"%d %d %f\n", T, r, *(array + h + 1) - *(array + h));
			}
			
			r++;
			 
	        fclose(fp);
		}
		
	}
	
	free(sample);
	
}
int main() {
	double max, min, step = 0.000001;/*lambda的最值和步长*/
	int n;/*热化步数*/
	double lambda;/*计算的lambda*/
	FILE *fp;/*用于存储系统状态和倍周期分叉*/
	int r0;/*节省算力，用于判断N以内的倍周期是否被找完了*/
	
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
	
	array = (double*)malloc(N*sizeof(double));
	r0 = (int)floor(log( N - 1 )/ log (2.0)) ;
	printf("r0=%d\n",r0);
	
	fp = fopen("data_alpha.txt","a+");
	fprintf(fp,"T m d_m\n");/*打印表头*/
	fclose(fp);
	
	do{
	    chaos(lambda, n);
	    lambda += step;
	}
	while( lambda < max && r < r0);
	
	return 0;
	
}
