      FUNCTION erf(x)
      REAL erf,x
CU    USES gammp
      REAL gammp
      if(x.lt.0.)then
        erf=-gammp(.5,x**2)
      else
        erf=gammp(.5,x**2)
      endif
      return
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
