#include<stdio.h> 
#include<math.h>

int main(){
	double x,y;
	int n;
	FILE *fp;
	fp = fopen("data.txt","a+");
	
	for( n = -5; n < 6; n++){/*计算x=-5到x=5步长1的插值点的ξ值*/
		x = (double)n;
		y = (double)(pow(x,(double)3) + 3 * pow(x,(double)2) +6 * x+80)/310;
		fprintf(fp,"%f %f\n",x,y);
		
	}
    
    fclose(fp);
    
	return 0;
}
