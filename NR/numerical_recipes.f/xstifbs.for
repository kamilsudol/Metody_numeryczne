      PROGRAM xstifbs
C     driver for routine stifbs
      INTEGER KMAXX,NMAX
      PARAMETER (KMAXX=200,NMAX=50)
      INTEGER kmax,kount,nbad,nok
      REAL dxsav,eps,hstart,x1,x2,y(3),xp,yp
      COMMON /path/ kmax,kount,dxsav,xp(KMAXX),yp(NMAX,KMAXX)
      EXTERNAL stifbs,derivs
1     continue
      write(*,*) 'ENTER EPS,HSTART:'
      read(*,*,END=999) eps,hstart
      kmax=0
      x1=0.
      x2=50.
      y(1)=1.
      y(2)=1.
      y(3)=0.
      call odeint(y,3,x1,x2,eps,hstart,0.,nok,nbad,derivs,stifbs)
      write(*,'(/1x,a,t30,i3)') 'Successful steps:',nok
      write(*,'(1x,a,t30,i3)') 'Bad steps:',nbad
      write(*,*) 'Y(END)=',y(1),y(2),y(3)
      goto 1
999   write(*,*) 'NORMAL COMPLETION'
      STOP
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
