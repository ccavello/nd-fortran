/* Christopher D. Cavello
   CSE 232
   Assignment 4 problem 1
         displacement and velocity of a wheel over a bump   */

#include <stdio.h>
#include <math.h>

main()
{
int i;
double b, f, g, k, m, t, deltat;
double v, vw, w, y, yw,anay, beta, omega;
double ypre,fpre,vpre,fnew,vnew,ynew;
/* assign values to known variables   */
k = 2416.0;
w = 951.7;
yw = .25;
g = 32.2;
m = w / g;
b = sqrt( k * m );
beta = b /(2 * m);
omega = sqrt ( k / m - beta * beta);
deltat=.01;


/* y = 0 and v = 0 when [ t= 0 ]
   f = k * yw when [ t = 0 ]            */
  
f = k * yw;
y = 0;
v = 0;

/* use a loop to get values (time step = .01s ) */
i = 0;
t = 0.0;

/* print header                   */

printf("\nChristopher Cavello\nCSE 232\nSept.30 1992\n\n");
printf(" time   anal. y    num. y  spr. force  velocity");
while ( i <= 200 )
 {
 anay = yw - yw*exp(-beta*t)*(cos(omega*t)+(beta/omega)*sin(omega*t));
 ypre = y + deltat*v;
 fpre = f + deltat*k*(vw - v);
 vpre = v+ deltat * (f + b *(vw - v)) / m; 
 ynew = y + deltat * (v + vpre) / 2;
 fnew = f + deltat * (k * (vw - v) + k *(vw -vpre)) / 2;
 vnew = v + deltat * ((f+b*(vw -v)) / m + (fpre + b*(vw -vpre))/m) / 2;
 if ( (i % 10)== 0) printf("%3.2f %10.6f %10.6f %10.6f %10.6f\n",t,anay,y,f,v);
 y = ynew;
 f = fnew;
 v = vnew;
  
 i=i+1;
 t=t+deltat;
 }
}

 
