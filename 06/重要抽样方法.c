#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define F(x) (double)(3/(sqrt(2.0*3.1415926)*(1+pow(x,(double)4))))
#define p(x) (double)(1/sqrt(2.0*3.1415926))*exp((double)(-pow(x,(double)2)/2))
#define stepwidth1 1 
#define stepwidth2 0.01 
#define g(u)  (-2*atan(1-sqrt(2.0)*u)+2*atan(1+sqrt(2.0)*u)+log(1+sqrt(2.0)*u+pow(u,2.0))-log(1-sqrt(2.0)*u+pow(u,2.0)))/(4*3.1415926)+0.5

double ReverseFunction( double x ) {/*二分法求u(x)*/
      double min, max;	/*min是u的下界max是u的上界*/ 
      int n;/*逐步减小步长的循环语句使用，第n个循环中步长1E-n*/
      double sw;/*存储步长*/
      
      if( x >= 0.981727 ) {    /*u>3，取初始步长stepwidth1,u∈(3,66.9511)*/
          min = 3  ;
          max = 66.9511;
          sw = stepwidth1;
      } 
      
      else if ( 0.5 < x && x < 0.981727){    /*u<3，取初始步长stepwidth2,u∈(0,3)*/
          min = 0  ;
          max = 3;
          sw = stepwidth2;
      } 
      
      else{
      	printf("x = %f.Error.\n",x);/*报错*/
		return 0; /*为了结束运行，没有意义*/
	  }

	  for(n = (int)log10(sw) ;n < 7; n++ ){
	  	
		  
		  do{                 /*求min，即增大下界。增大min直到g(min)>=x，如果g(min)=x,u=min,否则满足u>min的最大min是上一步的min，即min-sw*/
	  		min += sw;
		  }
		  while( g(min) < x); 
		  
		  if( g(min) == x ) 
		  return min; 
		  
		  min -= sw;
		  
		  do{                 /*求max，即减小上界。减小max直到g(max)<=x，如果g(max)=x,u=max,否则满足u<max的最大max是上一步的max，即max+sw*/
	  		max -= sw;
		  }
		  while( g(max) > x);
		  
		  if( g(max) == x ) 
		  return max; 
		  
		  max += sw;
		  
		  sw *= 0.1;/*减小步长*/
		   
	  }
	  /*此时如果仍在运行自定义函数ReserveFunction说明u在min,max之间，近似取u=max(取平均值四舍五入为max)*/ 
      return max;	  
}

int RandomNumber( int N,int seed,int a,int m,int r,int q ){/*Schrage方法生成以连续两个随机数进行重要抽样*/
    FILE *fp;/*存放随机数*/
    double x,y,u,v;/*x,y是在（0，1）上均匀分布的随机数（ξ1，ξ2）,u，v是由（x,y）对应的重要抽样随机变量（ξx, ξy）*/ 
    int n;/*循环变量*/ 
    int I;/*随机数生成的In*/
    int S;/*保留数据的数目*/
    
    fp = fopen("Sampling1.txt","a+") ;
    fprintf(fp,"seed=%d\nx\n",seed);/*表头*/
    
    I = seed; /*将种子值赋给I0*/
    S = 0;/*清空S*/  
    
    for(n=0;n<N;n++) {                      /*用 Schrage方法求I，然后得到x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*生成xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*生成In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*生成x(n+1)=yn*/
		
		if( x >= 0.5 )                      /*依照抽样函数进行抽样*/
		u = ReverseFunction(x);          
		else
		u = -ReverseFunction(1 - x);
		
		v = y * F(u) ;
		
		if(v <= p(u)){/*舍选条件*/	
		   fprintf(fp,"%f\n",u) ;       /*写入文件*/ 
		   S += 1;
		}
		
	}
	
	printf("抽样效率 = %f\n",(double)S/N ) ;
	fprintf(fp,"抽样效率 = %f\n",(double)S/N ) ; 
    
    fclose(fp);                          /*关闭文件*/ 
    
    return 0; 
} 

int main() {
	int a,m,r,q,N,seed;/*Schrage方法所需数据*/
	int n,h;/*n是循环语句用到的变量，h是报错用的变量*/ 
	
	printf("Please input seed value.");/*输入种子值*/
	scanf("%d", &seed) ;
	
	printf("Please input the number of random data.");/*输入数据量*/
	scanf("%d", &N) ;
	
    a=16807;               /*生成Schrage方法所需数据*/
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = RandomNumber(N,seed,a,m,r,q);/*生成N个随机数并保存*/
    if( h != 0 )/*自动报错*/
    printf("Failed to create random number.");
	
	return 0; 
}
