/* =============================================================== */
/*
 * Christopher Cavello CSE 232 November 16, 1992 Assignment 8
 */


/*
 * This program should look a heck of a lot like "vegematic2.c" by Jay
 * Brockman
 */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Structures  */

/* Assume the maximum number of shapes will be 33 (Larry Bird) */
/* Also assume the maximum number of characters will be 33  */

typedef struct shape
{
  char polygon[33];
  char nameofpoly[33];
  int xinit, yinit;
  int radius;
  int x2, y2;
  int w, h;
} Shape;

 /* Function prototypes  *//* Borrow from jbrockma's "vegematic2.c" */

void movefunct(Shape[]);
void scalefunct(Shape[]);
void createfunct(Shape[], int *);
void fetchfunct(Shape[]);
int find(Shape[], char[]);	/* function required by this assignment */

main()
{
  Shape thisshape[33];
  char command[33];
  int i, j, k;			/* Various counters  */
  int aNumber = 0;

  int notDone = 1;

  while (notDone)
  {
    printf("Staubach_shapes> ");
    scanf("%s", command);

    /* Use "strcmp" to find what the command is .      */
    /* NOTE: strcmp returns 0 if strings are equal!!!  */

    if (!strcmp(command, "move"))
    {
      movefunct(thisshape);
    }
    else if (!strcmp(command, "scale"))
    {
      scalefunct(thisshape);
    }
    else if (!strcmp(command, "create"))
    {
      createfunct(thisshape, &aNumber);
    }
    else if (!strcmp(command, "fetch"))
    {
      fetchfunct(thisshape);
    }
    else if (!strcmp(command, "quit"))
    {
      notDone = 0;
    }
    else
      printf(" NO SUCH ANIMAL. Please try again.\n\n ");

  }				/* _______________end of while loop_________ */

}				/* ~~~~~~~~~~~~~~ end of MAIN
				 * ~~~~~~~~~~~~~~~~~ */



/* What follows are the functions.          */



int
  find(Shape thisshape[], char *searched)
{				/* Like in vegematic! */
  int i = 0;
  while (strcmp(searched, thisshape[i].nameofpoly) && i < 33)
    ++i;
  return i;
}



void
  fetchfunct(Shape * this)
{
  char polyname[33];
  int k = 0;
  scanf("%s", polyname);
  k = find(this, polyname);

  if (!strcmp(this[k].polygon, "circle"))
  {
    printf(" %s is a %s with center (%d,%d) and radius %d\n",
	   this[k].nameofpoly, this[k].polygon,
	   this[k].xinit, this[k].yinit, this[k].radius);
  }
  else
  {
    printf(" %s is a %s with center (%d,%d), \n 
	   width % d, and height % d \n ", this[k].nameofpoly,
	   this[k].polygon, ((this[k].xinit) + this[k].w) / 2,
	   ((this[k].yinit) + this[k].h) / 2, this[k].w,
	   this[k].h);
  }

}				/* ~~~~~~~~~~~~~ end of fetchfunct
				 * ~~~~~~~~~~~ */




void
  movefunct(Shape thisshape[])
{
  char direction[33], polyname[33];
  int count, amount;

  scanf("%s %s %d", polyname, direction, &amount);
  count = find(thisshape, polyname);


  if (!strcmp(direction, "right"))
  {
    thisshape[count].xinit += amount;
  }
  if (!strcmp(direction, "left"))
  {
    thisshape[count].xinit -= amount;
  }
  if (!strcmp(direction, "up"))
  {
    thisshape[count].yinit += amount;
  }
  if (!strcmp(direction, "down"))
  {
    thisshape[count].yinit -= amount;
  }
}




void
  createfunct(Shape thisshape[], int *last)
{
  char shapesname[33], shapeskind[33];
  int x, y, wid, ht, rad;

  scanf("%s %s %d %d", shapeskind, shapesname, &x, &y);
  strcpy(thisshape[*last].polygon, shapeskind);
  strcpy(thisshape[*last].nameofpoly, shapesname);
  thisshape[*last].xinit = x;
  thisshape[*last].yinit = y;

  /*
   * If circle, scan in radius. If triangle or rectangle, scan in height and
   * width
   */

  if (strcmp(shapeskind, "circle"))
  {				/* i.e. If it's a rect. or tri. */
    scanf("%d %d", &wid, &ht);
    thisshape[*last].w = wid;
    thisshape[*last].h = ht;
  }
  else
  {				/* Circle */
    scanf("%d", &rad);
    thisshape[*last].radius = rad;
  }

  ++(*last);			/* Increment index just like in vegematic2.c */

}				/* ~~~~~~~~~~~~~~ end of createfunct
				 * ~~~~~~~~~~~~~ */




void
  scalefunct(Shape thisshape[])
{
  char shapesname[33];
  float coefficient;
  int i = 0;
  scanf("%s %f", shapesname, &coefficient);
  i = find(thisshape, shapesname);

  if (strcmp(thisshape[i].polygon, "circle"))
  {				/* If it's not a circle */
    thisshape[i].h = rint(coefficient * thisshape[i].h);
    thisshape[i].w = rint(coefficient * thisshape[i].w);
  }
  else
  {
    thisshape[i].radius = rint(coefficient * thisshape[i].radius);
  }
}				/* ~~~~~~~~~~~~~~ end of scalefunct
				 * ~~~~~~~~~~~~~ */
