#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>


double *x, l, a, r0, k;
double *X; //reference config 
double *chi,*chisq; //holds per particle non-affine parameter
int N;

double pbc(double dx) {
  return dx-l*rint(dx/l);
}

double calc_en() {
  double en=0,dr=0.0,e=0.0;
  int i=0,j=0;

  // will traverse in forward dir
  for(i=0; i<N; i++) {
    int j = (i+1==N)?0:(i+1);
    //if( i+1==N ) j=0;

    double dr = pbc( x[j] - x[i] );
    double e= 0.5*k* pow( (dr - r0), 2.0 );
    en += e;
  }

  return en;
}

double calc_X_full() {
  double global_chi = 0.0; // mean of perparticle chi
  double global_chisq=0.0;
  
  for(int i=0; i<N; i++) {
    
    int nplus = (i==N-1) ? 0 : i+1;
    int nminus = (i==0) ? N-1 : i-1;
    
    double dxp = pbc (x[nplus] - x[i]);
    double dXp = pbc (X[nplus] - X[i]);
    double dxm = pbc (x[nminus] - x[i]);
    double dXm = pbc (X[nminus] - X[i]);

    double xterm1 = dxp * dXp + dxm * dXm;
    double xterm2 = pbc (X[nplus] - X[i]) * pbc (X[nplus] - X[i]) + pbc (X[nminus] - X[i]) * pbc (X[nminus] - X[i]);
    double eps = xterm1 / xterm2;
    
    chi[i] = pow (pbc (x[nplus] - x[i]) - eps * (pbc (X[nplus] - X[i])), 2) + pow (pbc (x[nminus] - x[i]) - eps * (pbc (X[nminus] - X[i])), 2);
   // chisq[i]=pow(chi[i],2);
    global_chi += chi[i];
   // global_chisq += chisq[i];
  }
  
  return global_chi/(double)N;
  //return global_chisq/(double)N;
}

int main() {
  N =10000; // how many particles
  int i;
  char str[210], intoa[210];
  
  // Allocate the particle array reference and instantenous
  x = (double*) malloc(N*sizeof(double));
  X = (double*) malloc(N*sizeof(double));
  chi = (double*) malloc(N*sizeof(double));
 // chisq = (double*) malloc(N*sizeof(double));
  
  // File I/O stuffs
	char prefix[64] = "mc1";
	char thermo_filename[64];
	char conf_filename[64];
	
	sprintf(thermo_filename, "%s_thermo.txt", prefix);
	sprintf(conf_filename, "%s_conf.txt", prefix);
	
	FILE *fp_thermo, *fp_conf;
        
	fp_thermo = fopen(thermo_filename, "w");
  fp_conf = fopen(conf_filename, "w");      
  
	// nplusnput parameters
  a = 1.0; // lattice param
  r0 = 1.0;
  k = 1.0;
  l = N*a; // linear length of the chain

  //printf("l = %f\n", l);

  // initialise the lattice
  for(i=0; i<N; i++) {
    x[i] = -0.5*l + i*a;
    X[i] = x[i]; 
  }

  // compute total energy of the chain;
  double en = calc_en();
  printf("initial energy = %f\n", en);

  // input variable for MC
  unsigned long mcs_max = 1e7;
  double T = 0.02;
  double beta = 1/T;
  double dr_max = 0.5;
  unsigned long mcs;
  unsigned long conf_write_interval = 10000;
  unsigned long thermo_write_interval = 100;
  
  //printf("a=%lf r0=%lf beta=%lf\n", a,r0,beta);
  
  // init rng
  srand48((long) time(NULL));

  double rnew,Eold,Enew,dE,dr;
  
  double global_X = calc_X_full(); 
  unsigned long nacc = 0;
  
  // lets do MC
  for(mcs=0; mcs < mcs_max; mcs++) {
    
    if( mcs%conf_write_interval == 0 ) {
      fprintf(fp_conf, "# mcs=%ld\n", mcs); // a header line for the conf
      
      for(int i=0; i<N; i++) {
        fprintf(fp_conf, "%d %lf %lf\n", i, x[i], chi[i]);
      }
      
      fprintf(fp_conf, "\n\n"); // for gnuplot indexing
      
    }
    
    if( mcs%thermo_write_interval == 0 ) {
      double nacc_percent = 100*nacc/(double)mcs;
      fprintf(fp_thermo, "%ld %lf %lf \n", mcs, en, global_X);
      printf("%ld %f %lf\r", mcs, mcs/(float)mcs_max*100, nacc_percent );
    }
    
    global_X = calc_X_full(); 
    
    // MC cycle
    //for (i=0; i<N; i++) {
      int nplus=0,nminus=0,rpos=0;

      rpos = (int)(drand48()*(N));
      dr = ((2.0*(drand48()-0.5))*a*dr_max);
      rnew = pbc(x[rpos]+dr);

      // calculate dE
      nplus = (rpos==N-1) ? 0 : rpos+1;
      nminus = (rpos==0) ? N-1 : rpos-1;

      Eold = 0.5*k*( pow( pbc(x[nplus]-x[rpos]) -r0 ,2) + pow( pbc(x[rpos]-x[nminus]) -r0 ,2) );
      Enew = 0.5*k*( pow( pbc(x[nplus]-rnew) -r0 ,2) + pow( pbc(rnew-x[nminus]) -r0 ,2) );
      dE = Enew-Eold;

      // calculate X 
      

      if( drand48() < exp(-beta * dE) ) {
        x[rpos] = rnew;
        en += dE;
        nacc++;
      }
      
    //} // <<--- MC cycle ends
  } // <<--- MC loop ends

  // close the file pointers
  fclose(fp_thermo);
  fclose(fp_conf);  

  return 0;
}

