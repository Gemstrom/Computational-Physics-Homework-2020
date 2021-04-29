#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

void arrange( double x, double*p, int l){/*����l>1�Ķ�̬����,��(p+l-2)��p��ָ����������θ���(p+l-1)����p+1����ָ������ݣ�Ȼ��x����p��ַ*/
	int j;/*ѭ������*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}

void lTest( int l, int a, int m, int r, int q, int seed, int N){   /*�Ը�����l��C(l)����2ά������*/ 
    double *p, x, S=0, T=0,test;/*p���ڱ������ڵ�l��xn��x�������,S=N<xnxn+l>,T=x0+x1+����+xN+l-1,test=|C(l)|*/ 
    FILE *fp;/*���l,C(l)*/
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�Ij*/
    
    I = seed;/*������ֵ����I0*/
    
    p = (double*) malloc(l);/*����ͷָ��Ϊp�Ķ�̬���飬���ڱ������ڵ�l��xn*/ 
    if(p == NULL){/*����*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( n = 0 ; n < l ; n++ ){/*��䶯̬����*/
	   x = (double)I/m;/*��xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1��ѭ������ʱI=Il*/ 
		if( I < 0 )
				I = I + m ;
		
	   T = T + x;/*ѭ������ʱT=x0+x1+����+xl-1*/ 
	   *( p + l - 1 - n )=x;/*��x0��xl-1���θ���p+l-1��pָ����ڴ�*/
	}
    /*����Ϊl�Ķ�̬������������S���̿�ʼ*/
    
    for( n = l; n < N + l; n ++){             /*��Schrage��������xl��xN+l-1����S��T*/ 
    	x = (double)I/m;
    	
    	T = T + x;
    	
    	S = S + x*( *( p + l - 1 ));
    	
    	arrange( x, p, l);/*���¶�̬����*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1*/ 
		if( I < 0 )
				I = I + m ;
	}
    
    free(p);/*�ͷŶ�̬�����ڴ�*/
    
    test =  (double)S/N - pow((double)T/(N+l),(double)2) ;       /*����|C(l)|*/
	if( test<0 )
	test = - test;
	
	fp=fopen("l-square test.txt","a+") ;     /*�洢C(l)*/
	fprintf(fp,"%d %f\n", l, test) ;
	fclose(fp);  
    
    
    return; 
} 

void lTest2(int a, int m, int r, int q, int seed, int N){ /*��C(1)����2ά������*/ 
	FILE *fp;/*���|C(l)|*/
    double x,y,S,T,test;/*��x,y�������������,S���ڴ��x0x1+����+xN-1xN,T=x0+����+xN*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    
    S = 0;
    T = 0;
	I = seed; /*������ֵ����I0*/
    
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 ){
				I = I + m ; 
		}
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
		
		S += x*y;                          
		T += x;
	}
    
    T += y; /*ѭ������ʱS=x0x1+����+xN-1xN,T=x0+����+xN-1��y=xN������y*/ 
    
    test = (double)S/N - pow((double)T/(N+1),(double)2);
    if( test<0 )
	test = - test;
	
    fp=fopen("l-square test.txt","a+") ;     /*�洢C(l)*/
	fprintf(fp,"1 %f\n", test) ;
	fclose(fp);  
    
    
    return; 
}

int main() {
	int a,b,m,r,q,N,seed;/*Schrage������������*/
	int l[5];/*C(l)֧������5�������Ե�l*/ 
	char string[] = "data000";/*�����ļ�������*/ 
	int n,h;/*n��ѭ������õ��ı���*/
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
	printf("Please input 5 l-values you would like to test.\n");/*����5��l*/ 
	for( n=0; n<5; n++) {
	   scanf( "%d" , l+n );
	}
    
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	 
	for( n = 0; n < 5; n++ ){/*���ν���5��l��C(l)����*/  
	    if( l[n] < N && l[n] > 1  )
		lTest(l[n],a,m,r,q,seed,N);
    
        else if(l[n] == 1)
        lTest2(a,m,r,q,seed,N);
        
        else
        printf("Illegal l-value.");
	}
	return 0; 
}
