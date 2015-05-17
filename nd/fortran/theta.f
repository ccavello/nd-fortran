c	A program to calculate the ideal
c	angle of the inner wheel of a turning
c	car when the outer angle is given.

c	Set the names of the variables.

	real d,L,THIDL,THOUTR,PI

c	Ask for and read the value of Theta(outer)
c	 in degrees.

	write(0,*) 'Enter the value of Theta(outer) in degrees.'
	read(5,*) THOUTR 

c	Convert thoutr to radians, having set a value for pi.

	PI=3.141592654

	THOUTR=THOUTR*PI/180.0

c	Assign values for d and L.

	d=0.65
	L=2.40

c	Compute a value for Theta(inner) in radians, then
c	 convert it to degrees.

  	THIDL=ATAN(L/((L/TAN(THOUTR))-2.0*d))
	THIDL=THIDL*180.0/PI

c	Output the data.

	write(6,*) 'Theta(outer)=',THOUTR*180.0/PI

	write(6,*) 'Theta(ideal)=',THIDL

c  	Output name of program's author.

	write(6,*) 'This program was written by'
	write(6,*) 'Christopher Cavello on 9/20/1991'

c	End the program.

	STOP	
	END	






