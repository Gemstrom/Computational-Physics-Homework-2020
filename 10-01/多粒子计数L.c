#include<stdio.h> 
#include<math.h>
#include<stdlib.h>
#define f(N) F0/M/(1+1/(pow(M*w*B,2.0)))*((1-cos((double)N))/(pow(w,3.0)*M*B)-sin((double)N*w)/pow(w,2.0)-(exp(-(double)N/M/B)-1)/(w*M*B))
double M,B,w,F0,Fr;/*����������ճ��ϵ����صĳ�������������Ƶ�ʣ�������������������������*/

int seedx,seedy;/*x,y����ֵ*/

float Langevin( int a, int m, int r, int q, int N){   /*���ӵ�һά�������*/ 
    double x,y,X,Y,xx;/*����Box-Muller��������*/ 
    int n;/*ѭ������*/ 
    int Ix, Iy;/*��������ɵ�In*/
    float S,v;/*λ��,�ٶ�*/
    
    S = 0;/*��ʼ��λ��*/ 
    v = 0;/*��ʼ���ٶ�*/
    Ix = seedx; /*������ֵ����I0*/
    Iy = seedy;
    
    for(n=0;n<N;n++) {                      /*�� Schrage������Ix,Iy��Ȼ��õ�x,y*/ 
		
		x = (double)Ix/m;                    /*����xn*/ 
		y = (double)Iy/m;                   /*����yn*/
		
		Ix= a * (Ix%q)- r*((Ix-(Ix%q))/q);      /*����In+1*/ 
		if( Ix < 0 )
		Ix += m ;
		
		Iy= a * (Iy%q)- r*((Iy-(Iy%q))/q);      /*����In+1*/ 
		if( Iy < 0 )
		Iy += m ;
		
		X = 2*x -1;/*Box-Muller����*/
		Y = 2*y -1;
		
		if(pow(X,2.0)+pow(Y,2.0) > 1){
			n--;
			continue;
		}
		
		xx = X * sqrt(-2*log(pow(X,2.0)+pow(Y,2.0))/(pow(X,2.0)+pow(Y,2.0)));
		
		S += v; /*����λ��*/
		v = (1-1.0/M/B)*v + Fr * xx /M;/*�����ٶ�*/ 
		
	}
    
    return S; 
}
int main() {
	int a,b,m,r,q,N,NN;/*Schrage������������;*N�����Ӳ�����NN������*/ 
	int n;/*n��ѭ������õ��ı���*/
	float x,S,T;/*x��һ��������ߵ�λ������S�Ƕ�����ӵ�x֮�ͣ�T�����ӵ�λ��ƽ��֮��*/ 
	
	printf("Please input seed x.");/*��������ֵ*/
	scanf("%d", &seedx) ;
	printf("Please input seed y.");
	scanf("%d", &seedy) ;
	
	printf("Please input the step.");/*����������*/
	scanf("%d", &N) ;
	
	printf("Please input frequency.");/*��������Ƶ��*/
	scanf("%lf", &w) ;
	
	printf("Please input m.");/*������������*/
	scanf("%lf", &M) ;
	
	printf("Please input F0��force field��.");/*������������С*/
	scanf("%lf", &F0) ;
	
	printf("Please input Fr��random force��.");/*�����������С*/
	scanf("%lf", &Fr) ;
	
	printf("Please input B.");/*����ճ��ϵ����*/
	scanf("%lf", &B) ;
	
	printf("Please input the number of particle.");/*���뵥���Ӳ���*/
	scanf("%d", &NN) ;
	
	
    a=16807;               /*����Schrage������������*/
	b=0;
	m=2147483647;
	r=m%a;
	q=(m-r)/a;
	
	
    for(n=0; n < NN; n ++) {
		x = Langevin(a,m,r,q,N);/*����NN�����ӵ�N��һά�������*/
		S += x;
		T += x*x;
	}
	
	printf("<x>=%f\n<x^2>=%f\n<��x^2>=%f\n",S/NN,T/NN,T/NN-pow((double)S/NN,2.0));
	
	return 0; 
}
