#include<stdio.h> 
#include<math.h>

#define L(x) -4.999999999999999-1679.414511925006*x+1306.604336498538*pow(x,2.0)+718483.6883936822*pow(x,3.0)-11057257.78954862*pow(x,4.0)+77264158.80698961*pow(x,5.0)-302904372.690824*pow(x,6.0)+702521844.3357706*pow(x,7.0)-950240462.1130562*pow(x,8.0)+687294971.9494734*pow(x,9.0)-203596983.3770245*pow(x,10.0)
int main(){
	/*ȡ��*/
	int n;/*ѭ������*/
	double z;/*����p(x)�������ʵ������x*/
	/*Schrage�������������*/ 
	FILE *fp;/*��������*/
	int I;/*��������ɵ�In*/
	int a,m,r,q,N,seed;/*Schrage������������*/
	double y;/*������ɵĦ�*/
	double test;/*��(L(x)),��x�Աȿ��Եõ���ֵ��׼ȷ��*/ 
	
	a=16807;               /*����Schrage������������*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	/*�����������*/ 
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
	/*���ļ�*/ 
	fp = fopen("sample1.txt","a+") ;
    fprintf(fp,"seed=%d\n�� x ��(x)\n",seed);/*��ͷ*/
    
    I = seed; /*������ֵ����I0*/
    
    for( n = 0; n < N; n ++) {                   /*��In�����n,Ȼ���� Schrage������In+1,�ɦ�n��xn���Σ�xn)��������ļ�"sample1.txt"*/ 
	
	y = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	z =  L(y);
	
	test =(double) ( pow(z,3) +3*pow(z,2) +6 * z +80 )/310;
	fprintf(fp,"%f %f %f\n",y,z,test);
	}
	fclose(fp);
	
	return 0;
}
