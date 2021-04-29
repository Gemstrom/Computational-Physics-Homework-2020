#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
double w;/*��������Ƶ��*/
double E;/*������߸����г���Ӱ���С*/

int OnedimensionRW( int a, int m, int r, int q, int seed, int N){   /*���ӵ�һά�������*/ 
	double x;/*x�������*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    FILE *fp;/*�������ɵ�����λ��*/
    int S;/*�������������߲���*/ 
    
	fp=fopen("1D RW.txt","a+") ;
	fprintf(fp,"x t(N)\n");
	
	S = 0;/*��ʼ��S*/
    I = seed;/*������ֵ����I0*/
    
    for( n = 0; n < N; n ++) {                   /*��In���xn�����߷���,Ȼ���� Schrage������In+1*/ 
	
	x = (double)I/m;
	
	if(0 < x && x < (1-E*sin(w*n))*0.5)            /*�ж����߷���,����λ�ã�����*/
	S --;
	else if(x > (1-E*sin(w*n))*0.5 && x<1 )
	S++;
	else{
		printf("Error.\n");
		return -1;
	}
	
	fprintf(fp,"%d %d\n",S,n+1);
	
	I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
	
	}

	fclose(fp);  
	
	return 0;
}

int TwodimensionRW( int a,int m,int r,int q,int seed,int N){/*Schrage�����������������������ʵ�ֵ�Ķ�ά�������*/
    FILE *fp;/*��������*/
    double x,y;/*��x,y�������������*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    int X,Y;/*�ᡢ����λ��*/
    
    fp = fopen("2D RW.txt","a+") ;
    fprintf(fp,"X Y N\n");/*��ͷ*/
    
    X = 0;/*��ʼ��λ��*/ 
    Y = 0;
    I = seed; /*������ֵ����I0*/
    
    for(n=0;n<N;n++) {                      /*�� Schrage������I��Ȼ��õ�x,y*/ 
		
		if(n == 0) 
		x = (double)I/m;                    /*����xn*/ 
		else
		x = y;
		
		I= a * (I%q)- r*((I-(I%q))/q);      /*����In+1*/ 
		if( I < 0 )
		I = I + m ;
		
		y = (double)I/m;                   /*����x(n+1)=yn*/
		
		if(0 < x && x < (1-E*sin(w*n))*0.5)            /*�ж�X���߷���,����λ�ã�����*/
	    X --;
	    else if(x > (1-E*sin(w*n))*0.5 && x<1 )
	    X ++;
	    else{
		    printf("Error.\n");
		    return -1;
	    }
	    
	    if(0 < y && y < 0.5)            /*�ж�Y���߷���,����λ�ã�����*/
	    Y --;
	    else if( y > 0.5 && y < 1 )
	    Y ++;
	    else{
		    printf("Error.\n");
		    return -1;
	    }
		
		fprintf(fp,"%d %d %d\n",X,Y,n+1) ;       /*д���ļ�*/ 
		
	}
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

void arrange( double x, double*p, int l){/*����l>1�Ķ�̬����,��(p+l-2)��p��ָ����������θ���(p+l-1)����p+1����ָ������ݣ�Ȼ��x����p��ַ*/
	int j;/*ѭ������*/
	
	for( j = l-1; j > 0; j--) {
		* (p + j) = *(p + j - 1);
	}
	
	*p = x ; 
	
	return;
}
int ThreedimensionRW( int a,int m,int r,int q,int seed,int N){/*Schrage�����������������������ʵ�ֵ����ά�������*/
    FILE *fp;/*��������*/
    double x;/*x�������*/ 
    int n;/*ѭ������*/ 
    int I;/*��������ɵ�In*/
    double X,Y,Z;/*��������λ��*/
    double *p;/*p�ǳ�Ϊ3���ڱ����������������������ͷָ��*/
    
    p = (double*) malloc(3*sizeof(double));/*����ͷָ��Ϊp�Ķ�̬���飬���ڱ������ڵ�3��xn*/ 
    if(p == NULL){/*����*/ 
    	printf("memory allocation error\n");
    	return;
	}
    
    fp = fopen("3D RW.txt","a+") ;
    fprintf(fp,"X Y Z N\n");/*��ͷ*/
    
    X = 0;/*��ʼ��λ��*/ 
    Y = 0;
    Z = 0;
    I = seed; /*������ֵ����I0*/
    
    for( n = 0 ; n < 3 ; n++ ){/*��䶯̬����*/
	   x = (double)I/m;/*��xn*/ 
	
	   I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1��ѭ������ʱI=Il*/ 
		if( I < 0 )
				I = I + m ;
		
	   *( p + 2 - n )=x;/*��x0��xl-1���θ���p+l-1��pָ����ڴ�*/
	}
    /*����Ϊl�Ķ�̬������������S���̿�ʼ*/
    
    for( n = 3; n < N + 3; n ++){             /*��Schrage��������xl��xN+2,��λ�������*/ 
    	if(0 < *(p+2) && *(p+2) < (1-E*sin(w*n))*0.5)            /*�ж�X���߷���,����λ�ã�����*/
	    X --;
	    else if(*(p+2) > (1-E*sin(w*n))*0.5 && *(p+2)<1 )
	    X ++;
	    else{
		    printf("Error.\n");
		    return -1;
	    }
	    
	    Y += (*(p+1)) * cos(2.0*3.14*(*p));
	    Z += (*(p+1)) * sin(2.0*3.14*(*p));
    	
    	fprintf(fp,"%f %f %f %d\n",X,Y,Z,n-2);
    	
		x = (double)I/m;
    
    	arrange( x, p, 3);/*���¶�̬����*/
    	
    	I= a * (I%q)- r*((I-(I%q))/q);      /*��Schrage��������In+1*/ 
		if( I < 0 )
				I = I + m ;
	}
    
    free(p);/*�ͷŶ�̬�����ڴ�*/
    
    fclose(fp);                          /*�ر��ļ�*/ 
    
    return 0; 
} 

int main() {
	int a,b,m,r,q,N,seed;/*Schrage������������*/
	int n,h;/*n��ѭ������õ��ı�����h�Ǳ����õı���*/
	
	printf("Please input seed value.");/*��������ֵ*/
	scanf("%d", &seed) ;
	
	printf("Please input the step.");/*����������*/
	scanf("%d", &N) ;
	
	printf("Please input frequency.");/*��������Ƶ��*/
	scanf("%f", &w) ;
	
	printf("Please input the value of e.");/*��������Ƶ��*/
	scanf("%f", &E) ;
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
    h = OnedimensionRW(a,m,r,q,seed,N);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to render 1D RW.");
    
    h = TwodimensionRW(a,m,r,q,seed,N);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to render 2D RW.");
	
	h = ThreedimensionRW(a,m,r,q,seed,N);/*����N�������������*/
    if( h != 0 )/*�Զ�����*/
    printf("Failed to render 3D RW.");
    
	return 0; 
}
