# include <stdio.h>
# include <math.h>

double totalpay(double, double ,double *, int );/*PROTOTYPE*/

main()
{
   double apr = 10.0;
   double amount = 20000.0;
   int m = 36;
   double payment;

   printf ( "Total paid over 36 months = $%.2f\n\n" , totalpay ( apr, 
       amount , &payment , m)  );
   printf("Amount of monthly payment = $%.2f\n", payment);
}

double totalpay(double apr,double amount,double *payment, int m ) 

{
*payment = (apr / 1200.0) * pow ( (1.0 + apr / 1200.0), (m * 1.0) ) * amount /
            (pow ( (1.0 + apr / 1200.0), (m * 1.0) ) - 1.0);

return ( 36 * (*payment) );

}
