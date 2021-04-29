#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x) 0.1*exp(-pow((double)(x-3000),2.0)/50)
#define  e 7*pow(10.0,-7.0)  /*���ȿ���ֵ*/


double Romberg(int b) { /*F(x)��2900��b�Ķ�������ֵ*/
	int a = 2899;/*������˵�2899�Ҷ˵�b*/
	int i,j,k;/*ѭ������*/ 
	double *p1, *p2;/*���ڴ洢��k-1�͵�k�еĶ�̬����*/ 
	int N =121 - 1;/*ȡ����ĿN'=121*/
	double h;
	double S;/*S = \sum f(x0+h*0.5*i),i=0,1,������2^(k-1)*/
	
	h = (double)(b - a);
	p1 = (double *) malloc(sizeof(double)*(1));/*Romberg���ֵĵ�0��*/
	*p1 = (F(a)+F(b))*h/2.0;
	if(p1 == NULL){/*����*/ 
    	printf("memory allocation error\n");
    	return;
	}
	
	for( k=1; k <= N; k++ ){/*���㡢�洢Romberg���ֵĵ�k�У��Ƚ�e��|R_k,k-R_k-1,k-1|ֱ��������Ҫ�󣬵�k��ѭ����h=h_k-1=h*2^(-k+1)*/
		p2 = (double*)malloc(sizeof(double)*(k+1));/*Romberg���ֵĵ�k��,k=1,2,������N*/
		if(p2 == NULL){/*����*/ 
    	printf("memory allocation error\n");
    	return;
	    }
		
		S = 0;/*��S��ʼ��*/
		for(i = 1; i <= pow(2.0,(double)(k-1)) ; i++){  /*�������λ���*/ 
			S += F(a + (2*i-1)* h/2);
		}
		*p2 = 0.5*(*p1 + h*S) ;
		for( j = 1; j <= k; j++ ){/*����R_k,1��R_k,k*/
			*(p2+j)=(pow(4.0,(double)j) * ( *(p2+j-1) ) - *(p1 + j - 1))/(pow(4.0,(double)j) - 1);
		}
		
		if ( fabs(*(p2+k) - * (p1 + k-1 )) < e )/*�жϾ����Ƿ����Ҫ��*/
		return *(p2 + k);
		
		free(p1) ;
		p1 = p2 ;
		free(p2);
		h /= 2.0;
	}
	
}

int sample1 (double *z,double X0){/*��z[n]=X0ʱ����ӽ���������x*/
	int n;/*ѭ������*/
	
	for(n = 0; n < 114; n ++){
		if( X0 <= *(z+n) )
		break;
	}
	
	if (n=114) 
	printf("?");
	
	return n+2900;
}


int main(){
	int a,b,m,r,q,Q,seed;/*Schrage������������*/
	int n;/*n��ѭ������õ��ı���*/
	FILE *fp;/*fp�����ڵ������ݣ������ڱ������ɵ�����*/
	double X,Y;/*Schrage�������ɵ��������*/ 
	int I;/*��������ɵ�In*/
	int N = 0;/*N��ʵ�����ݵ�ĸ���*/
	int x,y;/*��ѡ���ķ���*/
	int DATA[114][2];/*������׵�����*/ 
	int J;/*�ɹ���������*/
	double z[114];/*����ֵ*/
	
	/*��������*/ 
	fp = fopen("data.txt","r") ;
	
	if(fp == NULL){/*��ʧ�ܻᱨ��*/
        printf("Failed to open data.txt.\n");
        return -1;
	}
	
	for(n = 0; n <114; n++){/*������ʵ��ֵ�����������*/
		fscanf(fp,"%d %d",DATA[n],(DATA[n]+1));
		N += DATA[n][1] ;/*�����ݵ����*/
		z[n] = Romberg(DATA[n][0]);/*����ֵ*/
	}
	
	fclose(fp);

	/*Schrage��������������ԣ�������ѡ�����������׳���*/ 
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &Q) ;
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    fp=fopen("tune3.txt","a+") ;     /*������ģ���ļ�*/
	fprintf(fp,"E/eV\n");/*��ӡ����*/
		
	I = seed; /*������ֵ����I0*/
	J = 0;
    
    for(n=0;n<Q;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		X = (double)I/m;                    /*����xn*/ 
		else
		X = Y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		Y = (double)I/m;                   /*����x(n+1)=yn*/
		 
		x = sample1(z,X*z[113]);
		y = Y * F(x);
		
		if( y*N <= DATA[x-2900][1]){
			fprintf(fp,"%d\n",x);
			J ++;
		}
		
		
	}
	
	fclose(fp);                          /*�ر��ļ�*/ 
    
    printf("%f",(double)J/Q) ;/*������ͨ��ѡ���ĳ���Ч��*/
    
    return 0;
    
}
