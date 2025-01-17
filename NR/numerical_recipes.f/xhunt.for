      PROGRAM xhunt
C     driver for routine hunt
      INTEGER N
      PARAMETER(N=100)
      INTEGER i,j,ji
      REAL x,xx(N)
C     create array to be searched
      do 11 i=1,N
        xx(i)=exp(i/20.0)-74.0
11    continue
      write(*,*) 'Result of:    j=0 indicates x too small'
      write(*,*) '            j=100 indicates x too large'
      write(*,'(t7,a7,t17,a5,t25,a1,t32,a5,t42,a7)') 'locate:',
     *     'guess','j','xx(j)','xx(j+1)'
C     perform test
      do 12 i=1,19
        x=-100.0+200.0*i/20.0
C     trial parameter
        ji=5*i
        j=ji
C     begin search
        call hunt(xx,N,x,j)
        if (j.eq.0) then
          write(*,'(1x,f12.6,2i6,a12,f12.6)') x,ji,j,
     *         'lower lim',xx(j+1)
        else if (j.eq.N) then
          write(*,'(1x,f12.6,2i6,f12.6,a12)') x,ji,j,
     *         xx(j),'upper lim'
        else
          write(*,'(1x,f12.6,2i6,2f12.6)') x,ji,j,xx(j),xx(j+1)
        endif
12    continue
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
