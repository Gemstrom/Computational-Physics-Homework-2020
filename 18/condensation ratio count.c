#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

#define a 16807/*Schrage��������*/
#define m 2147483647
#define r 2836
#define q 127773
#define N 2050/*��������߳�*/ 
#define center 1025/*��������*/

int field[N][N]={};/*��ʼ��,����������*/
int I;/*Schrage ���������*/
int x,y;/*������ߵ���������*/

int dla( int inf ) {/*�������ӴӾ���center>inf������ʼ��dlaģ��*/
	int Q;/*�����洢���������жϣ�������������˷�����*/
	
	/*���ɲ���ռ�ݵ����ӳ�ʼλ��x,y*/
	
	do{
		do{
		Q = I % (N - 1 - 2*inf) ;

	    I= a * (I%q)- r*((I-(I%q))/q);      /*����Schrage�������ɵ������*/ 
	    if( I < 0 )
     	I = I + m ;
	
	    }
	    while( Q == 0 || Q == N - 2 - 2 * inf );           /*Q����������������ȥ������Schrage�������ɵ������,��������Qֱ����������Ϊֹ*/ 
		
    	if( Q < center - inf ){
		    x = Q;
	    }
	    else
	        x = Q + 1 + 2*inf;
	    
	    do{
		    Q = I % (N - 1 - 2*inf) ;

	        I= a * (I%q)- r*((I-(I%q))/q);      /*����Schrage�������ɵ������*/ 
	        if( I < 0 )
     	    I = I + m ;
	
	    }
	    while( Q == 0 || Q == N - 2 - 2 * inf );            /*Q����������������ȥ������Schrage�������ɵ������,��������Qֱ����������Ϊֹ*/ 
		
	    if( Q < center - inf ){
	    	y = Q;
	    }
	    else
	        y = Q + 1 + 2*inf;
	    
	} 
	while( field[y][x] == 1 );
	
	/*û�б�ճס��ʱ������������*/   
	while(field[y+1][x] == 0 && field[y-1][x] == 0 && field[y][x+1] == 0 && field[y][x-1] == 0 ){
		
		switch(I%4) {/*random walk*/
			case 0: x++; break;
			case 1: x--; break;
			case 2: y++; break;
			case 3: y--; break;
		}
	
		I= a * (I%q)- r*((I-(I%q))/q);      /*����Schrage�������ɵ������*/ 
	    if( I < 0 )
	    I = I + m ;	
	    
		if( x < 1 || x > N - 2 || y < 1 || y > N - 2 ) {/*��������*/
			return 0;
		}
	}
	
	/*��ճס�˾��˳�ѭ������ʱ���ӵ�������field[x][y]*/ 
    field[y][x] = 1;/*ռ��*/
    return 1; 
}
int main() {
	int seed;/*����ֵ*/
	int i, j = 10;/*ѭ������*/
	FILE *fp;/*�����������λ��*/
	int count = 1;/*����������������ڽ��з�ά����*/ 
	int inf = 0;/*�Ŵصı߽磬���ڱ�֤��������λ��Զ������*/
	int S = 0;/*���ӵ�����֮��ƽ���ͣ����ڼ����ת�뾶*/
	double Rg;/*��ת�뾶*/
	
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &seed) ;
	I = seed;
	
	fp = fopen("condensation ratio count.txt","a+") ;/*�������۵�����λ��*/
	
	field[center][center]=1;/*��������*/
	
	fprintf(fp, "n condensation_ratio\n");/*��ӡ��ͷ*/ 
	
	for(i = 0; i < 419430; i++) {/*����n�����ӵ�DLAģ��*/
	    printf("i=%d\n",i);
	    
		if( dla( inf ) ){/*����*/
		
			if(abs(x - center) < inf)/*����������������*/
			inf = abs(x - center);
			if(abs(y - center) < inf)
			inf = abs(y - center);
			
			count ++;/*�������Ӽ���*/ 
		}
	
	    if( i == 10*j -1 ){/*ÿ��10�����ӽ���һ��ȡ������������*/
	        printf("j = %d\n", j);
	    	fprintf(fp, "%d %f\n", i+1, (double)count/(i+1) );/*���������Ŀ��������*/ 
	    	j ++;
		}
		
	}
	
	printf("j=%d\n",j);
	
	fclose(fp) ;
	
	return 0 ;
}

