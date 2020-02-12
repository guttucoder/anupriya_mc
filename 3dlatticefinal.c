#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#define N 216
#define rho 0.8442
double *x, *y, *z,l;

// lattice_length



//pbc function
double pbc (double dx,double l)
{
  return dx - l * rint (dx / l);
}

int main ()
{
  x = (double *) malloc (N * sizeof (double));
  y = (double *) malloc (N * sizeof (double));
  z = (double *) malloc (N * sizeof (double));


  l = 1.0*pow ((N / rho), 1.0 / 3.0);

  int i, count, boolean;
  double dr, dx, dy, dz, a, b, c;
  FILE *fp_conf;
  fp_conf = fopen ("configuration1.dat", "w");

//  srand48 ((long) time (NULL));
  x[0] = drand48 () * l;
  y[0] = drand48 () * l;
  z[0] = drand48 () * l;

 count = 1;
  do
    {
      boolean = 0;
//      printf("do loop");
//      printf("%d\n",count);

      a = drand48 () * l;
      b = drand48 () * l;
      c = drand48 () * l;
      for (i = 0; i < count; i++)
        {
          dx = pbc ((x[i] - a),l);
          dy = pbc ((y[i] - b),l);
          dz = pbc ((z[i] - c),l);
          dr = sqrt (dx * dx + dy * dy + dz * dz);
          if (dr < 1.0)
            {
              boolean = 1;
              break;
            }
        }
      if (boolean == 0)
        {
          x[count] = a;
          y[count] = b;
          z[count] = c;
          count = count + 1;
          fprintf (fp_conf, "%g\t%g\t%g\n", a, b, c);
        }
    }
  while (count < N);
fclose(fp_conf);

}

