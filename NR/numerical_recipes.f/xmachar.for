      PROGRAM xmachar
C     driver for routine machar
      INTEGER ibeta,iexp,irnd,it,machep,maxexp,minexp,negep,ngrd
      REAL eps,epsneg,xmax,xmin
      call machar(ibeta,it,irnd,ngrd,machep,negep,iexp,minexp,
     *     maxexp,eps,epsneg,xmin,xmax)
      write(*,*) 'ibeta=',ibeta
      write(*,*) 'it=',it
      write(*,*) 'irnd=',irnd
      write(*,*) 'ngrd=',ngrd
      write(*,*) 'machep=',machep
      write(*,*) 'negep=',negep
      write(*,*) 'iexp=',iexp
      write(*,*) 'minexp=',minexp
      write(*,*) 'maxexp=',maxexp
      write(*,*) 'eps=',eps
      write(*,*) 'epsneg=',epsneg
      write(*,*) 'xmin=',xmin
      write(*,*) 'xmax=',xmax
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
