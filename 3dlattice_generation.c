#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#define N 216
#define rho 0.8442
double *x, *y, *z, *dx, *dy, *dz;

// lattice_length
double l, dr;
l = pow((N/rho),1.0/3.0);

//pbc function
double pbc(double dx) {
  return dx-l*rint(dx/l);
}

int main() {
 x = (double*) malloc(N*sizeof(double));
 y = (double*) malloc(N*sizeof(double));
 z = (double*) malloc(N*sizeof(double));
 dx= (double*) malloc(N*sizeof(double));
 dy= (double*) malloc(N*sizeof(double));
 dz= (double*) malloc(N*sizeof(double));
 int i, count;
 FILE *fp_conf;
 fp_conf = fopen("configuration.dat", "w");

srand48((long) time(NULL));
x[0]=drand48()*l;
y[0]=drand48()*l;
z[0]=drand48()*l;

count= 1;
do{
boolean = 0;
a = drand48()*l;
b = drand48()*l;
c = drand48()*l;
for(i=0;i<count;i++){
    dx=pbc(x[i]-a);
    dy=pbc(y[i]-b);
    dz=pbc(z[i]-c);
dr = sqrt(dx*dx + dy*dy + dz*dz);
if(dr<1.0){
boolean = 1;
break;
}
}
if(boolean == 0){
x[count] = a; y[count] = b; z[count] = c;
count = count+1;
}
}while (count<N);
 fprintf(fp_conf, "x%g\ty%g\tz%g\n",a,b,c);
  
}






