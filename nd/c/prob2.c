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
double b02,bx2,bd2, rg1, rg2, arg3, arg4, arg5 , arg6, x, y;
double f, omega, by0, byd, bz, bz0, bzd ;
double pi=3.14159265358979;

/* assign values to known variables   */

a=.02286;       // in meters
b=.01016;
h=b/3;
er=2.56; 
mu=4*pi*1e-7;		// Henrys/meter
eps0=8.854185e-12;		// Farads/meter
i3=0;
i2=0;
printf("\t  omega \t by0 \t byd \t  x  \t y  \n");


for (omega=13.68e9; omega<= 2*13.68e9; omega+=5e4)
{	
	f=2.0*pi*omega;
	x=10;
	y=0;
	b02=pow(omega,2)*mu*eps0;
	bx2=pow((pi/a),2);
	bd2=b02*er;
	bz=1;
	while ( fabs(x-y) > -5 )
	{	
		rg1=b02-pow(bz,2)-bx2;
		rg2=bd2-pow(bz,2)-bx2;
		x=sqrt(rg1)*tan((sqrt(rg1)*(b-h)));
		y=sqrt(fabs(rg2))*tan(sqrt(fabs(rg2))*h);
		bz+=.1;
		i3+=1;
	}	// end of while
	

	i2+=1;	

//	printf("%e %e %2.1e %e %3.2e %d %d\n",omega,  rg1,rg2, x, y,i3,i2 );
	
}   // end of for loop
	

printf("\nChristopher D. Cavello\nEE 810\nJan 17, 1996\n\n");
printf("place header here\n ");
while ( i <= 200 )
 {
 if ( (i % 10)== 0) printf("%3.2f %10.6f %10.6f %10.6f %10.6f\n",f,omega,bz, by0, byd);
 }
}   // end of main

 
