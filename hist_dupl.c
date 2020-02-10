#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define  N   49999
#define  M   50
int *ind;
double *x, *ind1;

int main()
      {   int i,j,NN;
          double bin;
          double histf[M];
          int hist[M];
          FILE *in_file  = fopen("l_0.01.dat", "r"); // read only 
          FILE *out_file = fopen("hist_0.01.dat", "w"); // write only
					ind = (int *)malloc(sizeof(int)*N);
					ind1 = (double *)malloc(sizeof(double)*N);
					x = (double *)malloc(sizeof(double)*N);
					
					
					 int number = 0;
           while ( fscanf(in_file,"%d %lf %lf\n",&(ind[number]),&(ind1[number]),&(x[number])) != EOF ){
                
                
                number++;
          }
          NN=number;
          
          double minval = 0.0005, maxval = 1.5;
          
            bin= maxval-minval;
            bin = bin/M;
            double f= (bin*NN);
            //printf("%lf\n",f);
            //printf("bean is %1.16f\n",bean);


          for(i=0;i<M;i++)
                 hist[i]=0;
          double Y[M];
          //double X[M];
         for (j=0;j<M;j++){
		 for (i=0;i<NN;i++){
         		 if(x[i]>=minval+j*bin && x[i]<minval+(j+1)*bin)
                          hist[j]++;                          
                }
                Y[j]=minval+ ((j+0.5)*bin);
	     }
					
			    //Y[0]=0.0;
			    //fprintf(out_file,"%1.16f\t%d\n",X[0],histf[0]);
          for(i=0;i<M;i++){
                 histf[i]=(hist[i]/f) ;
                 fprintf(out_file,"%1.16f\t%lf\n",Y[i],histf[i]);
                 }
          fclose(in_file);
          fclose(out_file);

}









