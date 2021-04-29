#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

# define render +/*需要改变Fibonacci生成器运算类型时改变此声明中的render即可*/
# define m 2147483647

void arrange( int x, int *p, int l){/*更新长为l的动态数组,用(p+l-2)到p所指向的数据依次覆盖(p+l-1)到（p+1）所指向的数据，然后将x存入p地址*/
	int j;/*循环变量*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

int Fibonacci( int p, int q, int*a ){/*用In-p,In-q生成In，利用整数的区间对（m+1）进行取模，然后返回给主调函数*/
	int I; 
	I = *( a + p - 1 ) render *( a + q - 1 );/*In=In-p render In-q mod m*/
	if( I < 0 ){
		I += m;
		I ++ ;
	}
	return I;
}

int main(){
	int p, q, L;/*p,q是Fibonacci产生器的数对p,q，L=max{p,q}+1是数组长，用来保存In+1-l到In*/ 
	int I;/*用于保存随机数*/
	int n;/*循环语句所用变量*/
	int S = 0;/*满足Xn-1<Xn+1<Xn即In-1<In+1<In的n的计数*/ 
	int *a;/*长为L的数组，用于储存In+1-l到In*/ 
	int N;/*随机数的数量*/ 
	FILE *fp;/*创建一个文件用于写入N和比重，用于分析无穷多随机数中满足条件的数的比重*/ 
    
	printf("N=") ;/*输入生成的数的数目*/
	scanf("%d",&N);
	
	printf("p=");/*输入p,q,生成数组长度L*/
	scanf("%d" , &p) ;
	printf("q=");
	scanf("%d" , &q) ;
	
	if( p > q ) 
	L = p + 1;
	else
	L = q + 1;
	
	a = (int*)malloc(L);/*创建长为L的数组*/
	
	printf("输入I0~I%d共%d个数.\n",L-2,L-1) ;/*自定义填充前L-2个数*/
	for( n = 0; n < L - 1 ; n++ ) {
		scanf("%d",a-L+1+n);
	}
	
	I = *( a - p ) render *( a - q ) ;/*由I0,I|p-q|生成IL-1*/
	if( I < 0 ){
		I += m;
		I ++ ;
	}

	*a = I; 
	
	for( n = 0; n < N; n ++ ){/*从IL-1到IL+N-2 N个数中满足In-1<In+1<In的进行计数*/
		I = Fibonacci(p,q,a) ;
		
		if( *(a-1)<I && I < *a )/*对In-1<In+1<In的条件进行判断*/
		S++; 
		
		arrange( I, a, L );/*移动数组元素，更新数组*/
		
	}
	
	printf("%f", (double)S/N ) ;/*输出满足条件随机数比重*/
    
    fp = fopen("OriginDataFibonacci.txt","a+") ;/*保存不同N的比重*/
    fprintf(fp,"%d %f\n",N, (double)S/N );
    fclose(fp);
	
	return 0; 
}
