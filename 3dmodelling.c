#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define N 1000
#define T 5000
/* int main(){
double r;
r = drand48();
printf("%g\n",drand48());*/
int main() {
int i,j,m,n,k;
double x[N], y[N],dx,dy,r1;
double a,b,kx,ky,*sum[300],sum1,sum2,sum3;
int count,count_rand,boolean;
FILE *fp;
fp = fopen("rand.dat","w");
for(i=0;i<300;i++){
sum[i] = malloc(sizeof(double)*T);
}

for(n=0;n<T;n++){
srand((long)time(NULL)); /* initialize rand() */
x[0] = drand48(); x[0] = 40*x[i];
y[0] = drand48(); y[0] = 40*y[i];

count_rand = 1;
do{
boolean = 0;
a = 40*drand48();
b = 40*drand48();
for(j=0;j<count_rand;j++){
dx = fabs(x[j] - a);
dy = fabs(y[j] - b);
if(dx > 20.0) dx = 40 - dx;
if(dy > 20.0) dy = 40 - dy;
r1 = sqrt(dx*dx + dy*dy);
if(r1<1.0){
boolean = 1;
break;
}
}
if(boolean == 0){
x[count_rand] = a; y[count_rand] = b;
count_rand = count_rand+1;
// printf("%d\n",count_rand);
}
}while (count_rand<N);
// printf("%g\n",r[1][i]);
k = 0;
for (kx=0;kx<=40;kx=kx+0.2){
// for (ky=0.196;ky<=4;ky=ky+0.2){
ky = 1.196;
sum1 = 0;
sum2 = 0;
for(i=0;i<N;i++){
for(j=i+1;j<N;j++){
dx = (x[i] - x[j]);
dy = (y[i] - y[j]);
sum1 = sum1 + cos(kx*dx + ky*dy);
sum2 = sum2 - sin(kx*dx + ky*dy);
}
}
sum[k][n] = sqrt(sum1*sum1 + sum2*sum2)/(N);
k = k+1;
}
printf("%d\n",n);
 }
for(i=0;i<200;i++){
sum3 = 0;
for(j=0;j<T;j++){
sum3 = sum3 + sum[i][j];
}
printf("%g\n",sum3/T);
}

return 0;
}
