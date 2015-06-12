/* Christopher Cavello
   CSE 232
   November 6, 1992

   A program to decipher messages encoded with a Caesar shift   */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXMESSAGE 50
#define MAXWORD 20

/* Declare function prototypes.  */

char shift(char letter, int amount);
int search(int position, int map[]);

main()
{
  char a, b, c;			/* Declare variables, although         */
  int numofmessages;		/* I might not use all of them       */
  int position;
  char bigarray[MAXMESSAGE][MAXWORD];
  int i, j, k, amt, numofwords;
  int scramblemap[MAXMESSAGE];

  scanf("%d", &numofmessages);

/* Here is the while loop which is the chief part
     in my program.                               */

  while (numofmessages > 0)
  {
    scanf("%d", &amt);		/* Caesar shift */
    scanf("%d", &numofwords);	/* number of words in the message */

    for (i = 0; i < numofwords; i++)
    {
      scanf("%d", &scramblemap[i]);	/* Store the scramble map */
    }

    for (j = 0; j < numofwords; j++)
    {
      scanf("%s", bigarray[j]);

      /*
       * Another loop nested inside Caesar shifts the whole `bigarray` letter
       * by letter
       */

      for (k = 0; k < strlen(bigarray[j]); k++)
      {
	a = bigarray[j][k];
	b = shift(a, amt);
	bigarray[j][k] = b;
      }				/* Close inner for loop */
    }				/* Close outer for loop */

    j = 0;

    for (k = 0; k < numofwords; k++)
    {
      i = search(k, scramblemap);
      printf("%s ", bigarray[i]);
      if (j == 5)
      {
	printf("\n");		/* New line every five words */
	j = 0;
      }
      j++;
    }

    printf("\n\n");		/* New line after each message */

    numofmessages = numofmessages - 1;

  }				/* ............................. End of while
				 * loop  */

}				/* ..........................End of main          */

char shift(char letter, int amount)
{
  char temp;			/* The ASCII value for   */
  if (isupper(letter))		/* 'A' is 65, 'a' is 97  */
  {
    temp = (letter - 65 + amount) % 26 + 65;
    return temp;
  }
  else if (islower(letter))
  {
    temp = (letter - 97 + amount) % 26 + 97;
    return temp;
  }
  else
    return letter;
}

int search(int position, int scramblemap[])
{
  int i = 0;

  while (scramblemap[i] != position)
    ++i;
  return i;

}
