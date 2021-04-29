#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

double h = 0.00001;/*step*/
int N = 314161;/*���鳤*/
double psi[314161];/*����������WFֵ*/
int n = 1;/*����ֵ���*/
double A;/*��һ������*/
double epsilon = 0.01;

void check(double f){
	int j;/*ѭ������*/ 
	
	A = 0;
	
	for(j = 2; j < N; j++){
		psi[j] = (24 + 10*pow(h,2.0)*f)/(12 - pow(h,2.0)*f) * psi[j-1] - psi[j-2];
	}
		
	for(j = 0; j < N-1 ; j ++) {
		A += pow(psi[j], 2.0);
	}
	A *= 2*h;
	A = sqrt(A);
		
}
void TISE(double f){
	char even[] = "0_even";/*�����ļ�������*/ 
	char odd[] = "0_odd";/*�����ļ�������*/ 
	FILE *fp;
	int i;/*ѭ������*/
	int H =0;/*ָʾ�Ƿ��Ǳ���ֵ*/
	
	psi[0] = 1;/*����ż��Ƴ�ֵ�µĶ�̬Ѧ���̷���*/
	psi[1] = 1;
	check(f);
	
	if( fabs(psi[N-1]/A) < epsilon ) {    /*ȷ���Ǳ���̬*/
		H = 1; 
		printf("even %f\n",psi[N-1]/A);
		printf("E%d=%fh_bar/^2m_e\n",n,-f);
		even[0] = (char)(n+48);/*���ż��Ʋ�������ֵ*/
		fp = fopen(even, "a+");
		fprintf(fp,"x psi\n");/*��ӡ��ͷ*/
		for(i = 1-N; i < 0; i ++) {
			fprintf(fp,"%f %f\n",i*h, psi[-i]/A);
		}
		for(i = 0; i < N; i ++) {
			fprintf(fp,"%f %f\n",i*h, psi[i]/A);
		}
		fclose(fp);
	}
   
    psi[0] = 0;/*��������Ƴ�ֵ�µĶ�̬Ѧ���̷���*/
    psi[1] = 1;
	check(f);
		    
	if( fabs(psi[N-1]/A) < epsilon ) {    /*ȷ���Ǳ���̬*/
		H = 1; 
		printf("odd %f\n",psi[N-1]/A);
		printf("E%d=%fh_bar/^2m_e\n",n,-f);
		odd[0] = (char)(n+48);/*�������Ʋ�������ֵ*/
		fp = fopen(odd, "a+");
		fprintf(fp,"x psi\n");/*��ӡ��ͷ*/
		for(i = 1-N; i < 0; i ++) {
			fprintf(fp,"%f %f\n",i*h, -psi[-i]/A);
		}
		for(i = 0; i < N; i ++) {
			fprintf(fp,"%f %f\n",i*h, psi[i]/A);
		}
		fclose(fp);
   }
   
   if(H == 1){
   	    n++;
   }
}
int main(){
	double min = -10, max = 0;/*��������������ֵ*/
	double step = 0.05; 
	int i; /*ѭ������*/ 
    int nn = (max - min)/step;
    
	for(i = 0; i <= nn; i++) {/*��ͬ�����Ķ�̬Ѧ���̷���*/
		/*printf("f=%f\n",min + i*step);*/
		TISE(min + i*step) ;
	}
	
	return 0;
}
