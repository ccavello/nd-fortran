/* =============================================================== */
/*
 * Christopher Cavello CSE 232 December 1992   FINAL PROJECT
 */



#define SIZE 32
#define SIZE1 33
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* Structures, which allow the linked lists in my program.  */

typedef struct shape
{
  char polygon[SIZE1];		/* circle, rectangle, triangle */
  char nameofpoly[SIZE1];	/* 'fred', 'wilma', 'theodore', etc. */
  int xinit, yinit;		/* initial coordinates */
  int radius;
  double amount;
  int x2, y2;
  int w, h;
  char direction[SIZE];
  struct shape *next;		/* next enables linked lists */
} Shape;

typedef Shape *shapeptr;

/*  all the function prototypes immediately follow,           */
/*     i.e. there are no external functions                   */

void drawCircle(int xCtr, int yCtr, int radius, int array[SIZE][SIZE]);

void plotCirclePoints(int xCtr, int yCtr, int x, int y,
		        int array[SIZE][SIZE]);

void checkAndPlot(int x, int y, int grid[SIZE][SIZE]);

void printScreen(int array[SIZE][SIZE]);

void drawRectangle(int xcorn, int ycorn, int rw, int rh, int screen[SIZE][SIZE]);

void drawTriangle(int xcorn, int ycorn, int tw, int th, int screen[SIZE][SIZE]);

void movefunct(shapeptr *, char *, int);	/* movefunct doesn't work */

void scalefunct(shapeptr, double);

void createfunct(Shape, shapeptr *);

void deletefunct(shapeptr *, char[]);

Shape *find(Shape *, char[]);

void helpfunct(void);

void listfunct(void);

void soundfunct(void);

FILE *openfile(char *, char *);	/* prototype to open file */

void readfunct(shapeptr *, char[]);

void writefunct(shapeptr, char[]);

void drawfunct(shapeptr, int[SIZE][SIZE]);

void erasefunct(shapeptr *, int[32][32]);

main()
{
  int array[SIZE][SIZE] = {0};
  shapeptr thisshapeptr = NULL;
  Shape *p, shapeinfo, q;
  shapeptr startptr = NULL;
  shapeptr found;
  char command[SIZE1], command2[SIZE1], fileName[SIZE];
  int i, j, k;			/* Various counters  */
  int aNumber = 0;
  int notDone = 1;
  printf("\nA program by Christopher Cavello.\n");

  p = &shapeinfo;

/* the main while loop controls what action is taken based   */
/*   on the first word of input                              */

  while (notDone)
  {

    printf("Staubach_shapes> ");
    scanf("%s", command);

    /* Use "strcmp" to find what the command is .      */
    /* NOTE: strcmp returns 0 if strings are equal!!!  */

    if (!strcmp(command, "move"))	/* move doesn't work, I tried many
					 * forms */
    {
      scanf("%s %s %d", p->nameofpoly, p->direction, &(p->amount));
      found = find(startptr, p->nameofpoly);
      movefunct(&found, p->direction, p->amount);

    }
    else if (!strcmp(command, "scale"))
    {
      scanf("%s %lf", q.nameofpoly, &(q.amount));
      found = find(startptr, q.nameofpoly);
      scalefunct(found, q.amount);
    }
    else if (!strcmp(command, "create"))
    {
      scanf("%s", shapeinfo.polygon);
      if (!strcmp(shapeinfo.polygon, "c"))
      {
	scanf("%s %d %d %d", shapeinfo.nameofpoly, &shapeinfo.xinit,
	      &shapeinfo.yinit, &shapeinfo.radius);
	createfunct(shapeinfo, &startptr);
      }
      if (!strcmp(shapeinfo.polygon, "r"))
      {
	scanf("%s %d %d %d %d", shapeinfo.nameofpoly, &shapeinfo.xinit,
	      &shapeinfo.yinit, &shapeinfo.w, &shapeinfo.h);
	createfunct(shapeinfo, &startptr);
      }
      if (!strcmp(shapeinfo.polygon, "t"))
      {
	scanf("%s %d %d %d %d", shapeinfo.nameofpoly, &shapeinfo.xinit,
	      &shapeinfo.yinit, &shapeinfo.w, &shapeinfo.h);
	createfunct(shapeinfo, &startptr);
      }

    }

    else if (!strcmp(command, "delete"))
    {
      scanf("%s", command2);
      deletefunct(&startptr, command2);
    }

    else if (!strcmp(command, "help") || !strcmp(command, "relp_Raggy!"))
    {
      helpfunct();
    }
    else if (!strcmp(command, "quit") || !strcmp(command, "bye") ||
	     !strcmp(command, "ciao"))
    {
      printf("Program exited. All linked lists are lost.\n");
      system("play -v50 flush.au");
      printf("Until next time, America, Goodbye!\n\n");
      notDone = 0;
    }

    else if (!strcmp(command, "bells&whistles"))
    {
      soundfunct();
    }
    else if (!strcmp(command, "list"))
    {
      listfunct();
    }

    else if (!strcmp(command, "read"))
    {
      scanf("%s", fileName);
      readfunct(&startptr, fileName);
    }
    else if (!strcmp(command, "write"))
    {
      scanf("%s", fileName);
      writefunct(startptr, fileName);
    }
    else if (!strcmp(command, "draw"))
    {
      drawfunct(startptr, array);
    }
    else if (!strcmp(command, "erase"))
    {
      erasefunct(&startptr, array);
    }


    else
      printf("\a  NO SUCH ANIMAL. Please try again.\n\n ");

  }				/* _______________end of while loop_________ */

}				/* ~~~~~~~~~~~~~~ end of MAIN
				 * ~~~~~~~~~~~~~~~~~ */



/* What follows are the functions.     */



Shape *find(Shape * start, char *name)	/* this takes a shape's name and   */
{				/* traverses the list until the shape is
				 * found  */
  shapeptr pointer;

  if (start == NULL)
    return NULL;

  pointer = start;
  while (pointer != NULL)
  {
    if (strcmp(pointer->nameofpoly, name) == 0)
      return pointer;

    else
      pointer = pointer->next;
  }
  return pointer;
}


void movefunct(shapeptr * sptr, char *direction, int distance)
{

  shapeptr name;
  name = *sptr;

  if (!strcmp(direction, "left"))
    name->xinit -= distance;

  if (!strcmp(direction, "right"))
    name->xinit += distance;

  if (!strcmp(direction, "up"))
    name->yinit = distance + name->yinit;

  if (!strcmp(direction, "down"))
    name->yinit -= distance;
}




void
  createfunct(Shape this, shapeptr * sptr)
{

  shapeptr newptr, previousptr, currentptr;

  newptr = (shapeptr) malloc(sizeof(Shape));	/* Allocate memory space */
  /* and use a typecast to avoid errors */

  if (newptr)			/* This is false if lists are empty. */
  {
    strcpy(newptr->polygon, this.polygon);	/* copy values into the list */
    strcpy(newptr->nameofpoly, this.nameofpoly);
    (newptr->xinit) = this.xinit;
    (newptr->yinit) = this.yinit;
    (newptr->w) = this.w;
    (newptr->h) = this.h;
    (newptr->radius) = this.radius;

    previousptr = NULL;
    currentptr = *sptr;

    while (currentptr != NULL)

      if ((strcmp(currentptr->nameofpoly, this.nameofpoly)) > 0)
	/* algorithm for   */
      {				/* alphabetical insertion */
	previousptr = currentptr;	/* before current node */
	currentptr = currentptr->next;
      }
      else
	break;			/* Must use "break" to avoid infinite loop. */


    if (previousptr == NULL)	/* Case for beginning of list */
    {
      newptr->next = *sptr;
      *sptr = newptr;
    }
/* Normal insertion if new shape comes after present shape */

    else
    {
      previousptr->next = newptr;
      newptr->next = currentptr;
    }
  }
}
/*--------------- end of createfunct---------------------------------*/

/*------------------DELETEFUNCT--------------------------------------*/

void deletefunct(shapeptr * init, char shapenm[])
{
  shapeptr currentptr, prevptr, tempptr;
  if (!strcmp((*init)->nameofpoly, shapenm))
  {
    tempptr = *init;
    *init = (*init)->next;	/* if deleted node is first in list  */
    free(tempptr);
  }

  /* if deleted node isn't first, this traverses list    */
  else
  {
    prevptr = *init;
    currentptr = (*init)->next;
    while (currentptr != NULL &&
	   strcmp(currentptr->nameofpoly, shapenm) != 0)
    {
      prevptr = currentptr;
      currentptr = currentptr->next;
    }
    if (currentptr != NULL)
    {
      tempptr = currentptr;
      prevptr->next = currentptr->next;	/* May the node be free!  */
      free(tempptr);
    }
  }
}
/*---------------end of deletefunct-------------------------------*/


/*--------------SCALEFUNCT----------------------------------------*/

void scalefunct(shapeptr found, double amount)
{

  if (strcmp(found->polygon, "c"))
  {
    found->w = rint((found->w) * amount);
    found->h = rint((found->h) * amount);
  }
  else if (!strcmp(found->polygon, "c"))
  {
    found->radius = rint((found->radius) * amount);
  }
}

/* ~~~~~~~~~~~~~~ end of scalefunct~~~~~~~~~~~~~~~~~ */


/*_____________________________________________________________________*/
/* the following three draw functions are taken verbatim from          */
/*    previous homeworks, such as assignment 5.                        */


void drawTriangle(int xcorn, int ycorn, int tw, int th, int screen[SIZE][SIZE])

{
  int countrow, countcol, bc, signw, signh;
  float ab, ad, de;

  /*
   * signw and signh tell if height and width are positive or negative, and
   * therefore which direction to count the loops
   */

  signw = tw / abs(tw);
  signh = th / abs(th);

  ad = th * signh;
  de = tw * signw;

  for (countrow = 0; countrow < abs(th); countrow++)
  {
    ab = ad - countrow;
    bc = rint(de * ab / ad);

    for (countcol = 0; countcol < bc; countcol++)
      checkAndPlot(xcorn + countcol * signw, ycorn + countrow * signh, screen);

  }				/* close outer for loop  */

}				/* close drawTriangle   */


/* The function drawRectangle is much like drawTriangle, but it is
    a bit less complicated  */

void drawRectangle(int xcorn, int ycorn, int rw, int rh, int screen[SIZE][SIZE])
{
  int xincr = 1;
  int yincr = 1;
  int countcol, countrow;

  /* If the height or width is negative, reverse the increment.  */

  if (rw < 0)
    xincr = -1;
  if (rh < 0)
    yincr = -1;

  for (countcol = 0; countcol != rw; countcol = countcol + xincr)
  {
    for (countrow = 0; countrow != rh; countrow = countrow + yincr)
      checkAndPlot(countcol + xcorn, countrow + ycorn, screen);

  }				/* close outer for loop   */

}				/* close rectangle function  */




/*--------------------------------------------------------------------------
 * This function draws a circle with center (xCtr, yCtr) and radius "radius"
 * using Bresenham's algorithm.  Points on the perimeter of the circle are
 * stored in "array" as 1's.  Points outside the bounds of "array" are
 * clipped.  This function is from "~jbrockma/circle.c."
 */

void drawCircle(int xCtr, int yCtr, int radius,
		  int array[SIZE][SIZE])
{
  int x, y;			/* current x,y during scan */
  int p;			/* Bresenham decision parameter */

  y = radius;
  p = 3 - 2 * radius;

  for (x = 0; x <= y; ++x)
  {
    plotCirclePoints(xCtr, yCtr, x, y, array);

    if (p < 0)
      p = p + 4 * x + 6;	/* row does not change for next point */
    else
    {
      p = p + 4 * (x - y) + 10;
      --y;			/* down 1 row for next point */
    }
  }
}


/*--------------------------------------------------------------------------
 * This function plots the eight symmetric points of a circle with center
 * (xCtr, yCtr) to array for Bresenham's algorithm, where (x, y) is assumed
 * to be the corresponding point on a circle with the same radius that is
 * centered at (0, 0).  The function calls checkAndPlot to make sure that the
 * plotted point is within the bounds of "array", and to set the appropriate
 * location in "array" to 1. This function is from "~jbrockma/circle.c."
 */

void plotCirclePoints(int xCtr, int yCtr, int x, int y,
		        int array[SIZE][SIZE])
{
  checkAndPlot(xCtr + x, yCtr + y, array);
  checkAndPlot(xCtr + x, yCtr - y, array);
  checkAndPlot(xCtr - x, yCtr + y, array);
  checkAndPlot(xCtr - x, yCtr - y, array);
  checkAndPlot(xCtr + y, yCtr + x, array);
  checkAndPlot(xCtr + y, yCtr - x, array);
  checkAndPlot(xCtr - y, yCtr + x, array);
  checkAndPlot(xCtr - y, yCtr - x, array);
}



/*--------------------------------------------------------------------------
 * This function checks if a point (x, y) lies within the bounds of a two-
 * dimensional array "grid", and if so, sets location (x, y) to 1.
 *   This function is from "~jbrockma/circle.c"                       */

void checkAndPlot(int x, int y, int grid[SIZE][SIZE])
{
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
    grid[x][y] = 1;
}

/*--------------------------------------------------------------------------
 * This function prints a two-dimensional array "array" to standard out.
 * Non-zero entries of "array" appear as a "*", while zero entries appear
 * as a ".".  The function adds an extra space before printing a character
 * to account for the fact that columns are denser than rows on the screen.
 * Location (0, 0) will appear in the lower-left corner of the screen.
 *   This function is of course from "~jbrockma/circle.c"            */

void printScreen(int array[SIZE][SIZE])
{
  int row, col;			/* display coordinates */

  for (row = SIZE - 1; row >= 0; --row)
  {
    for (col = 0; col < SIZE; ++col)
    {
      if (array[col][row] == 0)
	printf(" .");
      else
	printf(" *");
    }
    printf("\n");
  }
}

/*-----------------------------------------------------------------*/
void helpfunct(void)
{
  system("clear");
  printf("Welcome to 'Staubach_shapes' by Chris Cavello.\n");
  printf("Here are your optional commands:\n");
  printf("\t\tcreate ('c', 't', 'r') x, y, width, height \n");
  printf("\t\tmove (shapename) (direction) \n");
  printf("\t\tscale (shapename) (amount) \n");
  printf("\t\tread (filename) \n");
  printf("\t\twrite (filename) \n");
  printf("\t\tdelete (shapename) \n");
  printf("\t\terase \n");
  printf("\t\tdraw \n");
  printf("\t\tlabel on/off \n");




}
/*______________________________________________________________*/

void soundfunct(void)
{
  system("play -v 30 cowbell.au");
  system("play -v 30 bong.au");
  system("play -v 30 whistle.au");
}


/*_______________________________________________________________*/

void listfunct(void)
{
  system("more shape_file");
}



/*------   from akai/cse232/filxmpl.c    -------------------*/

FILE *openfile(char *filename, char *mode)
{
  FILE *fileptr;

  if ((fileptr = fopen(filename, mode)) == NULL)
  {
    fprintf(stderr, "Can not open %s; exiting program\n", filename);
    exit(1);
  }
  return fileptr;
}

/*----------------READFUNCT---------------------------------*/
/*-----------much of this format is from ~akai/filxmpl------*/

void readfunct(shapeptr * head, char fileName[])
{
  Shape data;
  int array[32][32];
  FILE *ifp;
  ifp = openfile(fileName, "r");

/*Before a new scene is read in, we erase the old one for you,  */
/*   because that's what we're here for: to help you.            */

  erasefunct(head, array);

  if (ifp)
  {
    while (strcmp(data.polygon, "x"))
    {
      fscanf(ifp, "%s", data.polygon);
      if (!strcmp(data.polygon, "c"))
      {
	fscanf(ifp, "%s %d %d %d", data.nameofpoly, &data.xinit,
	       &data.yinit, &data.radius);
	createfunct(data, head);
      }
      else if (!strcmp(data.polygon, "r"))
      {
	fscanf(ifp, "%s %d %d %d %d", data.nameofpoly, &data.xinit,
	       &data.yinit, &data.w, &data.h);
	createfunct(data, head);
      }
      else if (!strcmp(data.polygon, "t"))
      {
	fscanf(ifp, "%s %d %d %d %d", data.nameofpoly, &data.xinit,
	       &data.yinit, &data.w, &data.h);
	createfunct(data, head);
      }
    }
  }

  fclose(ifp);
}

/*------------------------------------------------------------*/

void writefunct(shapeptr head, char fileName[])
{
  shapeptr data = head;
  FILE *ofp;
  ofp = openfile(fileName, "w");
  if (ofp != NULL)
  {
    rewind(ofp);
    while (data != NULL)
    {
      if (!strcmp(data->polygon, "c"))
      {
	fprintf(ofp, "%s %s %d %d %d\n", data->polygon, data->nameofpoly,
		data->xinit, data->yinit, data->radius);
      }
      else
      {
	fprintf(ofp, "%s %s %d %d %d %d\n", data->polygon, data->nameofpoly,
		data->xinit, data->yinit, data->w, data->h);
      }
      data = data->next;
    }
    fprintf(ofp, "%s", "x\n");
  }
  fclose(ofp);
}

/*-------------------------------------------------------------*/

void drawfunct(shapeptr init, int array[SIZE][SIZE])
{
  shapeptr sptr;
  int row, col;			/* display coordinates */

/* Note: every time draw is typed, the screen is set to all 0's   */

  for (row = SIZE - 1; row >= 0; --row)
  {
    for (col = 0; col < SIZE; ++col)
    {
      array[col][row] = 0;
    }
  }

  sptr = init;

  while (sptr != NULL)
  {
    if (!strcmp(sptr->polygon, "c"))
    {
      drawCircle(sptr->xinit, sptr->yinit, sptr->radius, array);
    }
    else if (!strcmp(sptr->polygon, "t"))
    {
      drawTriangle(sptr->xinit, sptr->yinit, sptr->w, sptr->h, array);
    }
    else if (!strcmp(sptr->polygon, "r"))
    {
      drawRectangle(sptr->xinit, sptr->yinit, sptr->w, sptr->h, array);
    }
    sptr = sptr->next;
  }
  printScreen(array);

}

/*---------------------------------------------------------------------*/

void erasefunct(shapeptr * sptr, int array[32][32])
{
  shapeptr currentptr, tempptr;
  int row, col;

  currentptr = *sptr;


  while (currentptr != NULL)	/* All nodes are set free, one by one */
  {
    tempptr = currentptr;
    currentptr = currentptr->next;
    free(tempptr);
  }

  *sptr = NULL;


  for (row = SIZE - 1; row >= 0; --row)	/* Screen is erased for good measure */
  {
    for (col = 0; col < SIZE; ++col)
    {
      array[col][row] = 0;
    }
  }


}
