      FUNCTION expdev(idum)
      INTEGER idum
      REAL expdev
CU    USES ran1
      REAL dum,ran1
1     dum=ran1(idum)
      if(dum.eq.0.)goto 1
      expdev=-log(dum)
      return
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
