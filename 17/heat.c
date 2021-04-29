#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
 
#define m 2000000/*��������(0��2)�ϵ������*/ 

int seed ;/*��ֵx0��Դ*/
int R = 0;
int N;/*����������*/ 
void sort(double *sample){/*�Գ�ΪN��ͷָ��sample��˫���������������*/
    int i,j;/*ѭ������*/	
    double swap;/*������*/
    for( i = 0; i < N - 1 ; i ++){/*����N-1������*/
    	for(j = 0; j < N - 1 - i; j++) { /*ÿ�˱���ǰ(N-i)��Ԫ��*/
    		if (*(sample + j) > *(sample + j + 1)){/*�����j��Ԫ�غ͵�(j+1)��Ԫ�ص�˳���Ǵ�С������ô��ת����*/ 
    			swap = *(sample + j) ;
    			*(sample + j)  = *(sample + j + 1) ;
    			*(sample + j + 1 ) = swap ;
			}
		}
	}
}
void check( int n, double lambda, double *sample){/*�ж�ϵͳ״̬�������ļ�*/
	int T = 1;/*������*/
	FILE *fp;/*���ڴ洢ϵͳ״̬�ͱ����ڷֲ�*/ 
	double sp;/*����ʹ��*/
	int i;/*ѭ������*/ 
	
	fp = fopen("data_0.txt","a+");
		
	sort(sample);/*����*/
	
	sp = *sample;/*���бȽ�*/ 
	
	for( i = 1; i < N; i++ ) {
		if( fabs(sp - *(sample + i)) >= 0.000001 ){/*�����µĵ������*/
			T ++;
			sp = *(sample + i);
		}
	}
	
	if(T == 1 && R == 0){
		fprintf(fp,"%d %d %f\n", n, T, lambda);
		R = 1;
	}
	
	
	if(T < N && T == 2*R ) {/*�ֲ��*/
	    printf("R = %d\n",R) ;
		fprintf(fp,"%d %d %f\n", n, T, lambda);
		R = 2 * R; 
	}
	
	fclose(fp);
	
}

void chaos( double lambda , int n){
	double x; 
	int i;/*ѭ������*/
	double *sample;/*��������*/
	
	sample = (double*)malloc(N * sizeof(double));
	x = (double) (seed%m)/m;
	
	for( i = 0; i < n; i ++ ){/*�Ȼ�*/ 
		x = lambda * sin(3.14159 * x );
	}
	
	for( i = 0; i < N; i ++ ) {/*���ɲ���*/
	    *(sample + i) = x;
	    x = lambda * sin(3.14159 * x );
	}
	
	check(n, lambda, sample);
	
	free(sample);
	
}
int main() {
	double max, min, step = 0.000001;/*lambda����ֵ�Ͳ���*/
	int i, n[4] = {100, 1000, 10000, 100000};/*ѭ���������Ȼ�����*/
	double lambda;/*�����lambda*/
	FILE *fp;/*���ڴ洢ϵͳ״̬�ͱ����ڷֲ�*/
	
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input lambda min.") ;/*����lambda����ֵ*/
	scanf("%lf",&min);
	printf("Please input lambda max.") ;
	scanf("%lf",&max);
	
	printf("Please input the maxim of cycle length.");/*�������������*/
	scanf("%d", &N) ;
	
	fp = fopen("data_0.txt","a+");
	fprintf(fp,"heating_step T lamda\n");/*��ӡ��ͷ*/
	fclose(fp);
	
	for( i = 0; i < 4; i++ ){
		lambda = min;
		do{
	    chaos(lambda, n[i]);
	    lambda += step;
	    }
	    while( lambda < max );
	    R = 0;
	}
	
	return 0;
	
}
