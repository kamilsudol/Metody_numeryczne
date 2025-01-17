      PROGRAM xfrenel
C     driver for routine frenel
      INTEGER i,nval
      REAL c,s,x,xc,xs
      CHARACTER text*17
      open(7,file='FNCVAL.DAT',status='OLD')
10    read(7,'(a)') text
      if (text.ne.'Fresnel Integrals') goto 10
      read(7,*) nval
      write(*,*) text
      write(*,'(1x,t5,a1,t12,a6,t28,a4,t42,a6,t58,a4)')
     *     'X','Actual','S(X)','Actual','C(X)'
      do 11 i=1,nval
        read(7,*) x,xs,xc
        call frenel(x,s,c)
        write(*,'(f6.2,4e15.6)') x,xs,s,xc,c
11    continue
      close(7)
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
