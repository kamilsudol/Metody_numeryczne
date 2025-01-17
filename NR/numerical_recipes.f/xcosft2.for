      PROGRAM xcosft2
C     driver for routine cosft2
      INTEGER NP
      REAL EPS,PI,WIDTH
      PARAMETER(EPS=1.0E-3,NP=16,WIDTH=30.0,PI=3.14159)
      INTEGER i,j,nlim
      REAL big,per,scal,small,data(NP)
1     write(*,'(1x,a,i2,a)') 'Period of cosine in channels (2-',NP,')'
      read(*,*) per
      if (per.le.0.) stop
      do 11 i=1,NP
        data(i)=cos(2.0*PI*(i-0.5)/per)
11    continue
      call cosft2(data,NP,+1)
      big=-1.0e10
      small=1.0e10
      do 12 i=1,NP
        if (data(i).lt.small) small=data(i)
        if (data(i).gt.big) big=data(i)
12    continue
      scal=WIDTH/(big-small)
      do 13 i=1,NP
        nlim=scal*(data(i)-small)+EPS
        write(*,'(1x,i2,f6.2,1x,60a1)') i,data(i),('*',j=1,nlim+1)
13    continue
      write(*,*) 'press continue ...'
      read(*,*)
      call cosft2(data,NP,-1)
      big=-1.0e10
      small=1.0e10
      do 14 i=1,NP
        if (data(i).lt.small) small=data(i)
        if (data(i).gt.big) big=data(i)
14    continue
      scal=WIDTH/(big-small)
      do 15 i=1,NP
        nlim=scal*(data(i)-small)+EPS
        write(*,'(1x,i4,1x,60a1)') i,('*',j=1,nlim+1)
15    continue
      goto 1
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
