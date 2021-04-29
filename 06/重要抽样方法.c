#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x) (double)(3/(sqrt(2.0*3.1415926)*(1+pow(x,(double)4))))
#define p(x) (double)(1/sqrt(2.0*3.1415926))*exp((double)(-pow(x,(double)2)/2))
#define stepwidth1 1 
#define stepwidth2 0.01 
#define g(u)  (-2*atan(1-sqrt(2.0)*u)+2*atan(1+sqrt(2.0)*u)+log(1+sqrt(2.0)*u+pow(u,2.0))-log(1-sqrt(2.0)*u+pow(u,2.0)))/(4*3.1415926)+0.5

double ReverseFunction( double x ) {/*���ַ���u(x)*/
      double min, max;	/*min��u���½�max��u���Ͻ�*/ 
      int n;/*�𲽼�С������ѭ�����ʹ�ã���n��ѭ���в���1E-n*/
      double sw;/*�洢����*/
      
      if( x >= 0.981727 ) {    /*u>3��ȡ��ʼ����stepwidth1,u��(3,66.9511)*/
          min = 3  ;
          max = 66.9511;
          sw = stepwidth1;
      } 
      
      else if ( 0.5 < x && x < 0.981727){    /*u<3��ȡ��ʼ����stepwidth2,u��(0,3)*/
          min = 0  ;
          max = 3;
          sw = stepwidth2;
      } 
      
      else{
      	printf("x = %f.Error.\n",x);/*����*/
		return 0; /*Ϊ�˽������У�û������*/
	  }

	  for(n = (int)log10(sw) ;n < 7; n++ ){
	  	
		  
		  do{                 /*��min���������½硣����minֱ��g(min)>=x�����g(min)=x,u=min,��������u>min�����min����һ����min����min-sw*/
	  		min += sw;
		  }
		  while( g(min) < x); 
		  
		  if( g(min) == x ) 
		  return min; 
		  
		  min -= sw;
		  
		  do{                 /*��max������С�Ͻ硣��Сmaxֱ��g(max)<=x�����g(max)=x,u=max,��������u<max�����max����һ����max����max+sw*/
	  		max -= sw;
		  }
		  while( g(max) > x);
		  
		  if( g(max) == x ) 
		  return max; 
		  
		  max += sw;
		  
		  sw *= 0.1;/*��С����*/
		   
	  }
	  /*��ʱ������������Զ��庯��ReserveFunction˵��u��min,max֮�䣬����ȡu=max(ȡƽ��ֵ��������Ϊmax)*/ 
      return max;	  
}

int RandomNumber( int N,int seed,int a,int m,int r,int q ){/*Schrage�����������������������������Ҫ����*/
    FILE *fp;/*��������*/
    double x,y,u,v;/*x,y���ڣ�0��1���Ͼ��ȷֲ������������1����2��,u��v���ɣ�x,y����Ӧ����Ҫ���������������x, ��y��*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    int S;/*�������ݵ���Ŀ*/
    
    fp = fopen("Sampling1.txt","a+") ;
    fprintf(fp,"seed=%d\nx\n",seed);/*��ͷ*/
    
    I = seed; /*������ֵ����I0*/
    S = 0;/*���S*/  
    
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
		
		if( x >= 0.5 )                      /*���ճ����������г���*/
		u = ReverseFunction(x);          
		else
		u = -ReverseFunction(1 - x);
		
		v = y * F(u) ;
		
		if(v <= p(u)){/*��ѡ����*/	
		   fprintf(fp,"%f\n",u) ;       /*д���ļ�*/ 
		   S += 1;
		}
		
	}
	
	printf("����Ч�� = %f\n",(double)S/N ) ;
	fprintf(fp,"����Ч�� = %f\n",(double)S/N ) ; 
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

int main() {
	int a,m,r,q,N,seed;/*Schrage������������*/
	int n,h;/*n��ѭ������õ��ı�����h�Ǳ����õı���*/ 
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*����������*/
	scanf("%d", &N) ;
	
    a=16807;               /*����Schrage������������*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = RandomNumber(N,seed,a,m,r,q);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to create random number.");
	
	return 0; 
}
