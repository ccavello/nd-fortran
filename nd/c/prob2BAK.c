//   Christopher D. Cavello
//   EE 810 
//   Assignment 1  Special problem 1
//
//   written in C++    use 'CC prob2.c -o prob2 -lm -ansi' to compile
//

#include <stdio.h>
#include <math.h>

main()
{
int i, i1, i2, i3;
double b, a, h, mu, eps0, er ;
double arg1, arg2, arg3, arg4, arg5 , arg6;
double f, omega, by0, byd, bz, bz0, bzd ;
double pi=3.14159265358979;

/* assign values to known variables   */

a=.02286;       // in meters
b=.01016;
h=b/3;
er=2.56; 
mu=4*pi*1e-7;		// Henrys/meter
eps0=8.854185e-12;		// Farads/meter

printf("\tomega\t omega sq.\t mu\teps0\t\n");


for (omega=13.68e9; omega<= 2*13.68e9; omega+=5e8)
{
	for (bz=1;bz<=6;bz++)
	{
	arg1=pow(omega,2);
	arg2=arg1*mu*eps0;
	arg3=pow(bz,2);
	arg4=pow((pi/a),2);
	arg5=arg2-(arg3+arg4);
//	arg3=1/sqrt(mu*eps0); // the speed of light
	

	

	printf("%e %e %2.1e %e %3.2e  \n",omega,  arg2,arg3, arg4, arg5 );
	}
	
}
	

printf("\nChristopher D. Cavello\nEE 810\nJan 17, 1996\n\n");
printf("place header here\n ");
while ( i <= 200 )
 {
 if ( (i % 10)== 0) printf("%3.2f %10.6f %10.6f %10.6f %10.6f\n",f,omega,bz, by0, byd);
 }
}

 
