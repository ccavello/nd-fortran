      PROGRAM RAPID
*********************************************
*  MAIN program for performing the analysis *
*  for the RAck-and-PInion Design problem.  *
*                                           *
*  EG 120 - Fall 1991                       *
*********************************************
      REAL L, THIDL(0:30)
      L = 2.40
      D = 0.65
      F = 45.0/ATAN(1.0)
      WRITE(6,*)' '
      WRITE(6,*)' '
      WRITE(6,*)'Program output for Final Design Project'
      WRITE(6,*)' '
      CALL IDEAL(L, D, F, THIDL)
      CALL INVALU(F, THIDL,RMSMIN,NLOC,SLOC,SGLOC)
	WRITE(6,*)'Minimum RMS is:',RMSMIN
	WRITE(6,*)'AT point:',NLOC
	WRITE(6,*)'Where'
	WRITE(6,*)'S=',SLOC
	WRITE(6,*)'SIGMA=',SGLOC
      STOP
      END
*
*
      SUBROUTINE IDEAL(L, D, F, THIDL)
*********************************************
*  Called from: MAIN                        *
*                                           *
*   Input: L - Wheelbase (2.40 m)           *
*          D - Semiaxle distance (0.65 m)   *
*          F - degrees per radian factor    *
*                                           *
*  Output: THIDL - array of ideal inner     *
*              wheel steering angles in     *
*              degrees.  THIDL(J) is the    *
*              value corresponding to an    *
*              outer wheel steering angle   *
*              of J degrees.                *
*                                           *
*  Ref: Design Notes 1 and Assignment 1.    *
*********************************************
*
*  Declarations; computation of angles
*
      REAL L, THIDL(0:30)
*
      THIDL(0) = 0.0
      DO 100 J = 1, 30
        Z = L/(L/TAN(REAL(J)/F) - 2.0*D)
        THIDL(J) = F*ATAN(Z)
 100  CONTINUE
      RETURN
      END
*
*
      SUBROUTINE INVALU(F, THIDL,RMSMIN,NLOC,SLOC,SGLOC)
*********************************************
*  Called from: MAIN (to get input values   *
*               of the steering arm length  *
*               S in meters and angle SIGMA *
*               in degrees.                 *
*                                           *
*   Input:  F - degrees per radian factor   *
*       THIDL - ideal inner steering angles *
*********************************************
*
*  Declarations; set specified values C and H
*
      REAL THIDL(0:30)
      C = 0.30
      H = 0.22
      S = 0.22
*
*  Get input values and give S its value
*
        CALL BISECT(S,SIGMA)
	SGV=SIGMA
	WRITE(6,*)'SIGMA at the V point is:',SGV
c
c**	Set up of the advanced problem solving program
c
	CALL LOC(SGV,RMSMIN,SGLOC,SLOC,NLOC,THIDL)
      RETURN
      END
*
c
c**	The subroutine function BISECT
c
	SUBROUTINE BISECT(S,SIGMA)
	PI=4.0*ATAN(1.0)
	SIGA=5.0*PI/180.0
	SIGB=15.0*PI/180.0
	SIGEND=F(S,SIGB)
  600   CONTINUE
	SIGM=(SIGA+SIGB)/2.0
	IF(((F(S,SIGM))*(SIGEND)) .GT. 0.0) THEN
	  SIGB=SIGM
	ELSE
	  SIGA=SIGM
	ENDIF
	IF (SIGB-SIGA .GT. 0.00001) GO TO 600
	SIGMR=SIGB-(SIGB-SIGA)*F(S,SIGB)/(F(S,SIGB)-F(S,SIGA))
	SIGMA=SIGMR*180.0/PI
	RETURN
	END
c
c**	Function subprogram F
c
	FUNCTION F(S,SIG)
	REAL M
	PI=4.0*ATAN(1.0)
	C=0.3
	H=0.22
	THO=30.0*PI/180.0
	TS=(C-S*SIN(SIG))**2.0+(H-S*COS(SIG))**2.0
	M=C-S*SIN(SIG-THO)-(SQRT(TS-(H-S*COS(SIG-THO))**2.0))
	F=SQRT(S**2.0-0.0004)+SQRT(TS-0.0004)-SQRT(H**2.0+(C+M)**2.0)
	RETURN
	END
c
c
c**	Subroutine set up to find minimum RMS on the constraint
c**	boundries.
c
c
	SUBROUTINE LOC(SGV,RMSMIN,SGLOC,SLOC,NLOC,IDL)
	REAL IDL(0:30)
c
c
c**	Inittialize coordinates, minimum RMS, and segment interval sizes
c
c
	C = 0.3
	H = 0.22
	SGU=5.21591
	SU=0.22
	SV=0.22
	SGW=7.37278
	SW=0.155855
	  RMSMIN=10.0
	  DSGUV=(SGV-SGU)/5000.0
	  DSVW=(SW-SV)/5000.0
	  DSWU=(SU-SW)/5000.0
c
c**	Begin search for S and SG, also set initial and last search points
c**	as well as the incriment
c
	WRITE(0,*) 'INIT, LAST, INC ???'
	READ(5,*) INIT, LAST, INC
	PI=4.0*ATAN(1.0)
	F = 180.0/PI
c
c	DO LOOP
c
	DO 77 N=INIT,LAST,INC
	   IF(N .LE. 5001) THEN
	       S=0.22
	       SG=SGU+DSGUV*REAL(N-1)
 	   ELSE IF(N .LE. 10001) THEN
	       S=SV+DSVW*REAL(N-5001)
	       CALL BISECT(S,SG)
	   ELSE IF(N .LE. 15001) THEN
	       S=SW+DSWU*REAL(N-10001)
	       SGR=ASIN(0.02/S)
	       SG=SGR*180.0/PI
	   ENDIF
c
c**	Compute RMS and update RMSMIN if needed
c
	CALL ANGLES(S,SG,C,H,F,IDL,DELTA)
	  IF(DELTA .LT. RMSMIN) THEN
	    RMSMIN=DELTA
	    SGLOC=SG
	    SLOC=S
	    NLOC=N
	  ENDIF
   77   CONTINUE
	RETURN
	END
 
*
      SUBROUTINE ANGLES(S, SG, C, H, F, IDL,
     &  DELTA)
*********************************************
*  Called from: INVALU (to find inner wheel *
*               steering angles and their   *
*               root mean square deviation  *
*               DELTA from the ideal.       *
*                                           *
*   Input:  S - Steering arm length (m)     *
*          SG - Steering arm angle (deg)    *
*           C - specified distance (0.30 m) *
*           H - specified distance (0.22 m) *
*           F - degrees per radian factor   *
*         IDL - ideal angles                *
*                                           *
*  Output: DELTA - rms deviation            *
*                                           *
*  Ref: Assignment 3.                       *
*********************************************
*
*  Declarations; tie-rod length T and its
*  square TSQ; square SSQ of S and HSQ of H
*
      REAL IDL(0:30), OUTR(0:30), INNR(0:30),
     &  M
       SR = SG/F
      TSQ = (C - S*SIN(SR))**2 +
     &      (H - S*COS(SR))**2
        T = SQRT(TSQ)
      SSQ = S*S
      HSQ = H*H
*
*  Start loop for outer steering angle OUTR;
*  compute rack motion M and auxiliary
*  values; compute inner angle INNR in deg.
*
      DO 300 J = 0, 30
        OUTR(J) = REAL(J)
         SGOUTR = (SG - OUTR(J))/F
              M = C - S*SIN(SGOUTR) -
     &    SQRT(TSQ - (H - S*COS(SGOUTR))**2)
            CPM = C + M
          CPMSQ = CPM**2
              P = SQRT(HSQ + CPMSQ)
          ALPHA = ATAN(H/CPM)
        INNR(J) = (ASIN((CPMSQ + HSQ + SSQ -
     &     TSQ)/(2.0*S*P)) - SR - ALPHA)*F
 300  CONTINUE
*
*  Get rms deviation and output results
*
      DELTA = RMS(IDL, INNR)
      RETURN
      END
*
*
c
c** 	Function subprogram to find root-mean-square deviation
c**	between the actual and the ideal inner steering angles
c**	using Simpson's rule.
c
 	FUNCTION RMS(IDL,INNR)
  	REAL IDL(0:30),INNR(0:30)
	SUM=0.0
	DO 500 L=0,28,2
	F=(L+2-L)/6.0
	F1=((INNR(L)-IDL(L))**2)
	F2=(4.0*((INNR(L+1)-IDL(L+1))**2))
	F3=(INNR(L+2)-IDL(L+2))**2
	SUM=SUM+(F*(F1+F2+F3))
  500   CONTINUE
	RMS=SQRT(SUM/30.0)
	RETURN
	END

