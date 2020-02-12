#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#define N 216
#define rho 0.8442
double *x, *y, *z,l;

int main ()
{
  x = (double *) malloc (N * sizeof (double));
  y = (double *) malloc (N * sizeof (double));
  z = (double *) malloc (N * sizeof (double));


  l = 1.0*pow ((N / rho), 1.0 / 3.0);

  int i,j,k;
  double lc=0.0;
  FILE *fp_conf;
  fp_conf = fopen ("configuration_scc.dat", "w");
  lc= (l/pow(N,1.0/3));
  
  for (i=0;i<(l-lc);i++){
    for (j=0;j<(l-lc);j++){
      for (k=0;k<(l-lc);k++){
        x[i]=i*lc;
        y[i]=j*lc;
        z[i]=k*lc;
        fprintf (fp_conf, "%f\t%f\t%f\n", x[i],y[i],z[i]);
      }
    }
  }
 fclose(fp_conf);
}
