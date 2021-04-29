#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

# define render +/*��Ҫ�ı�Fibonacci��������������ʱ�ı�������е�render����*/
# define m 2147483647

void arrange( int x, int *p, int l){/*���³�Ϊl�Ķ�̬����,��(p+l-2)��p��ָ����������θ���(p+l-1)����p+1����ָ������ݣ�Ȼ��x����p��ַ*/
	int j;/*ѭ������*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

int Fibonacci( int p, int q, int*a ){/*��In-p,In-q����In����������������ԣ�m+1������ȡģ��Ȼ�󷵻ظ���������*/
	int I; 
	I = *( a + p - 1 ) render *( a + q - 1 );/*In=In-p render In-q mod m*/
	if( I < 0 ){
		I += m;
		I ++ ;
	}
	return I;
}

int main(){
	int p, q, L;/*p,q��Fibonacci������������p,q��L=max{p,q}+1�����鳤����������In+1-l��In*/ 
	int I;/*���ڱ��������*/
	int n;/*ѭ��������ñ���*/
	int S = 0;/*����Xn-1<Xn+1<Xn��In-1<In+1<In��n�ļ���*/ 
	int *a;/*��ΪL�����飬���ڴ���In+1-l��In*/ 
	int N;/*�����������*/ 
	FILE *fp;/*����һ���ļ�����д��N�ͱ��أ����ڷ����������������������������ı���*/ 
    
	printf("N=") ;/*�������ɵ�������Ŀ*/
	scanf("%d",&N);
	
	printf("p=");/*����p,q,�������鳤��L*/
	scanf("%d" , &p) ;
	printf("q=");
	scanf("%d" , &q) ;
	
	if( p > q ) 
	L = p + 1;
	else
	L = q + 1;
	
	a = (int*)malloc(L);/*������ΪL������*/
	
	printf("����I0~I%d��%d����.\n",L-2,L-1) ;/*�Զ������ǰL-2����*/
	for( n = 0; n < L - 1 ; n++ ) {
		scanf("%d",a-L+1+n);
	}
	
	I = *( a - p ) render *( a - q ) ;/*��I0,I|p-q|����IL-1*/
	if( I < 0 ){
		I += m;
		I ++ ;
	}

	*a = I; 
	
	for( n = 0; n < N; n ++ ){/*��IL-1��IL+N-2 N����������In-1<In+1<In�Ľ��м���*/
		I = Fibonacci(p,q,a) ;
		
		if( *(a-1)<I && I < *a )/*��In-1<In+1<In�����������ж�*/
		S++; 
		
		arrange( I, a, L );/*�ƶ�����Ԫ�أ���������*/
		
	}
	
	printf("%f", (double)S/N ) ;/*��������������������*/
    
    fp = fopen("OriginDataFibonacci.txt","a+") ;/*���治ͬN�ı���*/
    fprintf(fp,"%d %f\n",N, (double)S/N );
    fclose(fp);
	
	return 0; 
}
