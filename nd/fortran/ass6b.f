**********************************************************
* A program to utilize the Newton-Ralphson method in     *
* finding roots for equations.                           *
********************************************************** 
	REAL X,XIMP
	X=0.0
C	SET THE EQUATIONS TO BE SOLVED.
33	F=(0.5*X+8.0)*SIN(X)-2.0
C	D IS THE DERIVATIVE OF F
	D=0.5*SIN(X)+COS(X)*(0.5*X+8.0)

	CONTINUE
	IF(ABS(F).GE.0.00001) THEN
	 XIMP=X-(F/D) 
	 X=XIMP
	 GO TO 33
	ENDIF

C	OUTPUT RESULTS 
	WRITE(6,*)'PROGRAM BY CHRISTOPHER CAVELLO.'
	WRITE(6,*)'WRITTEN NOVEMBER 15, 1991.'
        WRITE(6,*)' '
	WRITE(6,*)'F(X) APPROXIMATES ZERO AT THIS POINT:'
	WRITE(6,*)'X=',X
	write(6,*)'Y=',F
	STOP
	END
 
