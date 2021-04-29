#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

double h = 0.00001;/*step*/
int N = 314161;/*数组长*/
double psi[314161];/*保存正半轴WF值*/
int n = 1;/*本征值编号*/
 
void check(double f){
	int j;/*循环变量*/ 
	FILE *fp;
	fp = fopen("even.txt","a+");
	double A = 0;
	
	for(j = 2; j < N; j++){
		psi[j] = (24 + 10*pow(h,2.0)*f)/(12 - pow(h,2.0)*f) * psi[j-1] - psi[j-2];
	}
		
	for(j = 0; j < N-1 ; j ++) {
		A += pow(psi[j], 2.0);
	}
	A *= 2*h;
	A = sqrt(A);
	printf("%f",psi[N-1]/A);
	for( j = 0; j < N; j ++ ){
		fprintf(fp,"%f %f\n",h*j,psi[j]/A);
	}
	
	fclose(fp);
}

int main(){
	psi[0]=1;
	psi[1]=1;
	check(-4.0);
}
