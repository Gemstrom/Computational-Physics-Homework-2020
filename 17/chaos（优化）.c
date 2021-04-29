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
void check( double lambda, double *sample){/*�ж�ϵͳ״̬�������ļ�*/
	int T = 1;/*������*/
	FILE *fp1, *fp2;/*���ڴ洢ϵͳ״̬�ͱ����ڷֲ�*/ 
	double sp;/*����ʹ��*/
	int i;/*ѭ������*/ 
	
	fp1 = fopen("data_lamda_new.txt","a+");
	fp2 = fopen("data_delta_new.txt","a+");
		
	sort(sample);/*����*/
	
	sp = *sample;/*���бȽ�*/ 
	fprintf(fp1,"%f %f\n",lambda, sp);
	
	for( i = 1; i < N; i++ ) {
		if( sp != *(sample + i) ){/*�����µĵ������*/
			T ++;
			fprintf(fp1,"%f %f\n",lambda, *(sample + i));
			sp = *(sample + i);
		}
	}
	
	if(T == 1 && R == 0){
		fprintf(fp2,"%d %f\n", T, lambda);
		R = 1;
	}
	
	
	if(T < N && T == 2*R ) {/*�ֲ��*/
	    printf("R = %d\n",R) ;
		fprintf(fp2,"%d %f\n", T, lambda);
		R = 2 * R; 
	}
	
	fclose(fp1);
	fclose(fp2);
	
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
	
	check(lambda, sample);
	
	free(sample);
	
}
int main() {
	double max, min, step = 0.000001;/*lambda����ֵ�Ͳ���*/
	int n;/*�Ȼ�����*/
	double lambda;/*�����lambda*/
	FILE *fp1, *fp2;/*���ڴ洢ϵͳ״̬�ͱ����ڷֲ�*/
	
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input lambda min.") ;/*����lambda����ֵ*/
	scanf("%lf",&min);
	printf("Please input lambda max.") ;
	scanf("%lf",&max);
	
	lambda = min;
	
	printf("Please input the step of heating process.");/*�����Ȼ�������Ŀ*/
	scanf("%d", &n) ;
	printf("Please input the maxim of cycle length.");/*�������������*/
	scanf("%d", &N) ;
	
	fp1 = fopen("data_lamda_new.txt","a+");
	fp2 = fopen("data_delta_new.txt","a+");
	fprintf(fp1,"lamda x\n");/*��ӡ��ͷ*/
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
