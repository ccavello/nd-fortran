/* Christopher D. Cavello
	29 February 1996   

      Try to find prime numbers   */

#include <stdio.h>
#include <math.h>

main()

{

	int b, i, k ;

	/* use a loop to get values (time step = .01s ) */
	i = 3;
	b=1;
	k=0;
	/* print header                   */

	printf("\nChristopher Cavello\nFeb. 29, 1996\n\n");
	printf(" Prime Numbers\n");


	while  (b <= i)
	{
		if ( (i % b) != 0)   b=b+1;
		if ( (i %b) ==0)
		{ 
			b=2;
			i=i+1;
		}
		if ( (i-b) == 1 )
		{
			printf("%d\t", i);
			k=k+1;
			if ( (k % 8) == 0 )  printf("\n");
		}
	}


	printf("\n ");

}
