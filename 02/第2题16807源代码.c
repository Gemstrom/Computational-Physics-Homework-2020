#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

int main() {
	int a,m,r,q,N,seed;/*Schrage������������*/
	int n, I, S;/*S������������xn�ĸ�����n��ѭ��������ñ�����I��Schrage������ʹ��*/ 
	double x, y, z;/*x,y,z���xn-1,xn,xn+1*/  
    FILE *fp;/*����һ���ļ�����д��N�ͱ��أ����ڷ����������������������������ı���*/ 
    
    printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	    
    a=16807;               /*����Schrage������������*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	I = seed;/*������ֵ����I0��������Schrage��������x0��1��2*/
	x = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������I1*/ 
		if( I < 0 ){
				I = I + m ;
		}
		
	y = (double)I/m;
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������I2*/ 
		if( I < 0 ){
				I = I + m ;
		}
	
	z = (double)I/m;
	
	if( x < z && z < y )/*n=1����xn-1<xn<xn+1�����ļ�����һ*/
	  S ++;
	    
    
	for( n = 2; n <= N; n ++) {/*����ȡֵn��ѭ����ͨ����y,z��ֵ������x,y�Ƚ�xn-1,xn���θ���x,y�������ϸ��������ɵ�In����In+1������z���ж�x,y,z�Ƿ����������������������Ӽ���*/ 
		x = y;
		y = z;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������I1*/ 
		if( I < 0 ){
				I = I + m ;
		}
		
	    z = (double)I/m;
	    
	if( x < z && z < y )/*��xn-1<xn<xn+1�����ļ�����һ*/
	  S ++;
	    
	}
	
    printf("%f", (double)S/N ) ;/*��������������������*/
    
    fp = fopen("OriginData16807.txt","a+") ;/*���治ͬN�ı���*/
    fprintf(fp,"%d %f\n",N, (double)S/N );
    fclose(fp);
    
	return 0;
}
