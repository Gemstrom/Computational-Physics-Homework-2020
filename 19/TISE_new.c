#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

double h = 0.00001;/*step*/
int N = 314161;/*数组长*/
double psi[314161];/*保存正半轴WF值*/
int n = 1;/*本征值编号*/
double A;/*归一化常数*/
double epsilon = 0.01;

void check(double f){
	int j;/*循环变量*/ 
	
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
	char even[] = "0_even";/*保存文件的名字*/ 
	char odd[] = "0_odd";/*保存文件的名字*/ 
	FILE *fp;
	int i;/*循环变量*/
	int H =0;/*指示是否是本征值*/
	
	psi[0] = 1;/*计算偶宇称初值下的定态薛定谔方程*/
	psi[1] = 1;
	check(f);
	
	if( fabs(psi[N-1]/A) < epsilon ) {    /*确认是本征态*/
		H = 1; 
		printf("even %f\n",psi[N-1]/A);
		printf("E%d=%fh_bar/^2m_e\n",n,-f);
		even[0] = (char)(n+48);/*输出偶宇称波函数数值*/
		fp = fopen(even, "a+");
		fprintf(fp,"x psi\n");/*打印表头*/
		for(i = 1-N; i < 0; i ++) {
			fprintf(fp,"%f %f\n",i*h, psi[-i]/A);
		}
		for(i = 0; i < N; i ++) {
			fprintf(fp,"%f %f\n",i*h, psi[i]/A);
		}
		fclose(fp);
	}
   
    psi[0] = 0;/*计算奇宇称初值下的定态薛定谔方程*/
    psi[1] = 1;
	check(f);
		    
	if( fabs(psi[N-1]/A) < epsilon ) {    /*确认是本征态*/
		H = 1; 
		printf("odd %f\n",psi[N-1]/A);
		printf("E%d=%fh_bar/^2m_e\n",n,-f);
		odd[0] = (char)(n+48);/*输出奇宇称波函数数值*/
		fp = fopen(odd, "a+");
		fprintf(fp,"x psi\n");/*打印表头*/
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
	double min = -10, max = 0;/*无量纲能量的最值*/
	double step = 0.05; 
	int i; /*循环变量*/ 
    int nn = (max - min)/step;
    
	for(i = 0; i <= nn; i++) {/*求不同能量的定态薛定谔方程*/
		/*printf("f=%f\n",min + i*step);*/
		TISE(min + i*step) ;
	}
	
	return 0;
}
