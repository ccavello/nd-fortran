/*  Christopher Cavello       CSE 232
    A program to generate a circle on the screen using
    Bresenham's algorithm                            */

# include <math.h>
# include <stdio.h>
main()
{
int xc, yc, radius;
int xi, yi, pti, pti1, i, j;

/* initialize the really big array for the program   */
int n[32][32];

/* prompt user for values of center and radius */
printf("Enter a pair of integers for the circle's center.\n");
scanf("%d%d",&xc, &yc);
printf("Enter an integer value for the radius.\n");
scanf("%d", &radius);

/* set all the numbers in the array equal to zero */
for (i = 0; i<= 31; i = i + 1)
for (j = 0; j<= 31; j = j + 1)
 n[i][j]=0; 

/* set first position */
xi = 0;
yi = radius;

pti = 3-2*radius;

/* use a while loop to plot eight symmetric points
   for every point "pti"  */
while (xi <= yi)
 {
 /* Condition : as long as all points fit within the 32 X 32 array,
     go ahead and plot them.                                 */
 
 if ((xc+xi) <= 31 && (yc+yi) <= 31)   n[xc+xi][yc+yi]=1;
 if ((xc+xi) <= 31 && (yc-yi) >= 0)    n[xc+xi][yc-yi]=1;
 if ((xc-xi) >= 0 && (yc+yi) <= 31)    n[xc-xi][yc+yi]=1;
 if ((xc-xi) >= 0 && (yc-yi) >= 0)     n[xc-xi][yc-yi]=1;
 if ((xc+yi) <= 31 && (yc+xi) <= 31)   n[xc+yi][yc+xi]=1;
 if ((xc+yi) <= 31 && (yc-xi) >= 0)    n[xc+yi][yc-xi]=1;
 if ((xc-yi) >= 0 && (yc+xi) <= 31)    n[xc-yi][yc+xi]=1;
 if ((xc-yi) >= 0 && (yc-xi) >= 0)     n[xc-yi][yc-xi]=1;
  

 /* calculate the next value for pti from the current one. If
   pti < 0, pti1=pti+4xi+6.
   Otherwise pti1=pti + 4(xi-yi) +10 and y=y-1  */

 if (pti < 0)
  pti1 = pti+4*xi+6;
 else 
  {
  pti1=pti+4*(xi-yi)+10;
  yi = yi-1;
  }
 pti = pti1;
 xi = xi+1;
 }

/* plot points onto screen */
j = 31;
i = 0;
while (j >= 0)
 {
 while (i <= 31)
  {
  if (n[i][j] == 0) printf(". ");
  if (n[i][j] == 1) printf("* ");
  if (i == 31) printf("\n");  
  i = i+1;
  }
 i = 0;
 j = j-1;
 }

}
