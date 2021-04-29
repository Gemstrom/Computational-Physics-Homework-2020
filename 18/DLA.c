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

void sandbox(double Rg){/*sandbox�������ά*/
	int R;/*���뾶*/
	int r0;/*�����뾶*/ 
	int count = 1;/*ռ�ݸ����*/
	int i;/*ѭ������*/
	FILE *fp;/*���r,N����*/ 
	
	fp = fopen("sandbox_count.txt" , "a+");
	fprintf(fp, "lnN lnr\n");/*��ӡ��ͷ*/
	
	R = floor( Rg ) ;
	
	for( r0 = 1; r0 <= R; r0++ ){/*��ռ�ݸ����м��������*/
	
		for( i = center - r0; i <= center + r0; i++ ){
			count += field[center - r0][i] + field[center + r0][i];
		}
		for( i = center - r0 + 1; i <= center + r0 -1; i ++){
			count += field[i][center -r0] + field[i][center + r0];
		}
		
		fprintf(fp,"%f %f\n", log((double)count),log((double)r0));
	}
	
	fclose(fp) ;
	
}
int check( int step, int j, int k ) {/*���j��k�е��������������ռ��Ԫ����ô����1�����򷵻�0*/
    int l,n;/*ѭ������*/ 
    
	for( l = j * step + 1 ; l < (j + 1) * step + 1; l ++ ){ /*�������������ĸ���*/
		for( n = k * step + 1 ; n < (k+1) * step + 1 ; n ++){ /*����ѡ�����еĸ���Ԫ��*/ 
			if( field[l][n] == 1 ) 
			return 1;/*����ռ��Ԫ�ط���1*/ 
		}
	}

    return 0;/*���û�ҵ��ͷ���0*/
}
void boxcount() {/*�м�����*/
	int i, j, k;/*ѭ������*/
	FILE *fp; /*����м����������lnN��ln(1/epsilon)*/
	int step = 2 * N;/*����Ĳ���*/
	int n;/*N(epsilon)*/
	 
	fp = fopen("boxcount.txt","a+") ;
	fprintf(fp, "lnN ln(1/epsioln)\n");/*��ӡ��ͷ*/
	
	for( i = 0; i <= 11; i++ ) {
		
		n = 0;/*Ԥ��n*/ 
		step /= 2;/*�󲽳�*/
		
		/*��ռ��������N*/ 
		for( j = 0; j < pow(2.0, i); j ++ ){  /*��������*/
			for( k = 0; k < pow(2.0, i); k ++){/*�������ڸ���Ԫ��*/ 
				n += check(step,j,k) ;/*�����������j��k�еķ����������ռ������,n��һ*/
			}
		}
		
		fprintf(fp, "%f %f\n",log((double)n), i*log(2.0)) ;/*�����������ļ�*/
	}
	
	fclose(fp) ;/*�ر��ļ�*/
	
}
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
	int seed, n;/*����ֵ��������*/
	int i;/*ѭ������*/
	FILE *fp;/*�����������λ��*/
	int count = 1;/*����������������ڽ��з�ά����*/ 
	int inf = 0;/*�Ŵصı߽磬���ڱ�֤��������λ��Զ������*/
	int S = 0;/*���ӵ�����֮��ƽ���ͣ����ڼ����ת�뾶*/
	double Rg;/*��ת�뾶*/
	
	printf("Please input seed.");/*��������ֵ*/
	scanf("%d", &seed) ;
	I = seed;
	
	printf("Please input the number of particles.(1 to 419430)");/*����������*/
	scanf("%d", &n) ;
	
	if( n <= 0 || n > 419430 ){ /*������̫�����̫С����*/
	    printf("Inapropriate particle number.\n");
	    return 0;
	}
	
	fp = fopen("location.txt","a+") ;/*�������۵�����λ��*/
	
	field[center][center]=1;/*��������*/
	
	fprintf(fp, "x y\n");/*��ӡ��ͷ*/ 
	fprintf(fp, "%d %d\n", center,center);/*�����ʼ��������*/
	
	for(i = 0; i < n; i++) {/*����n�����ӵ�DLAģ��*/
	
		if( dla( inf ) ){/*����*/
			printf("Particle No.%d successfully aggregated.\n",i);
			
			if(abs(x - center) < inf)/*����������������*/
			inf = abs(x - center);
			if(abs(y - center) < inf)
			inf = abs(y - center);
			
			fprintf(fp, "%d %d\n", x,y);/*���۳ɹ�ʱ�����������*/
			count ++;/*�������Ӽ���*/ 
			S += (x - center) * (x - center) + (y - center) * (y - center);
			continue;
		}
		
		printf("Particle No.%d escaped.\n",i);
		
	}
	
	fclose(fp) ;
	Rg = sqrt( (double) S / count ) ;
	printf("Rg = %f\ncount=%d\n", Rg, count) ;
	
	boxcount();
	sandbox(Rg);
	
	return 0 ;
}

