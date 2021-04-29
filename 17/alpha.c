#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#define epsom 0.001 
#define m 2000000/*��������(0��2)�ϵ������*/ 

int seed ;/*��ֵx0��Դ*/
int r = 0;
int N;/*����������*/ 
double *array;

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
int check( double lambda, double *sample){/*�ж�ϵͳ״̬������������*/
	int T = 1;/*������*/
	double sp;/*����ʹ��*/
	int i;/*ѭ������*/ 

	sort(sample);/*����*/
	
	sp = *sample;/*���бȽ�*/ 
	*array = sp;

	for( i = 1; i < N; i++ ) {
		if( fabs(sp - *(sample + i)) >= epsom ){/*�����µĵ������*/
			*(array + T ) = *(sample + i);
			sp = *(sample + i);
			T ++;
		}
	}
	
	return T;
}

int seek( double key, int T){/*�ҵ�arrayǰT��Ԫ�����Ƿ���0.5�����û�з���-1����оͷ���λ��*/
      int low = 0, high = T-1, mid;/*������Χ�����޺��е�*/ 
	  
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
	int i, T, h;/*ѭ�����������ڳ��ȣ�ָʾ����*/
	double *sample;/*��������*/
	FILE *fp;/*���T,m,d_m*/
	
	sample = (double*)malloc(N * sizeof(double));
	x = (double) (seed%m)/m;
	
	for( i = 0; i < n; i ++ ){/*�Ȼ�*/ 
		x = lambda * sin(3.14159 * x );
	}
	
	for( i = 0; i < N; i ++ ) {/*���ɲ���*/
	    *(sample + i) = x;
	    x = lambda * sin(3.14159 * x );
	}
	
	T = check(lambda, sample);
	if( T == (int) pow(2.0, r+1) && T < N ) {/*N�Ƚϴ�ʱT<N������ģ��˴���ֹN����ֵ�Ƚ�С�����*/
		h = seek( 0.5, T ) ;/*���ַ���arrayǰT��Ԫ����û�к�0.5�����0.000001���ڵ�*/
		
		if( h >= 0 ){/*0.5��������*/
			fp = fopen("data_alpha.txt","a+");
			
	        if( h % 2 == 1){/*h������*/
	        	fprintf(fp,"%d %d %f\n", T, r, *(array + h) - *(array + h - 1));
			}
			
			else if( h % 2 == 0){/*h��ż��*/
	        	fprintf(fp,"%d %d %f\n", T, r, *(array + h + 1) - *(array + h));
			}
			
			r++;
			 
	        fclose(fp);
		}
		
	}
	
	free(sample);
	
}
int main() {
	double max, min, step = 0.000001;/*lambda����ֵ�Ͳ���*/
	int n;/*�Ȼ�����*/
	double lambda;/*�����lambda*/
	FILE *fp;/*���ڴ洢ϵͳ״̬�ͱ����ڷֲ�*/
	int r0;/*��ʡ�����������ж�N���ڵı������Ƿ�������*/
	
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
	
	array = (double*)malloc(N*sizeof(double));
	r0 = (int)floor(log( N - 1 )/ log (2.0)) ;
	printf("r0=%d\n",r0);
	
	fp = fopen("data_alpha.txt","a+");
	fprintf(fp,"T m d_m\n");/*��ӡ��ͷ*/
	fclose(fp);
	
	do{
	    chaos(lambda, n);
	    lambda += step;
	}
	while( lambda < max && r < r0);
	
	return 0;
	
}
