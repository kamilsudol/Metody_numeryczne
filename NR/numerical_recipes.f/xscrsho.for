      PROGRAM xscrsho
C     driver for routine scrsho
      REAL bessj0
      EXTERNAL bessj0
      write(*,*) 'Graph of the Bessel Function J0:'
      call scrsho(bessj0)
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
