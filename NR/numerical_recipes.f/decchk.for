      LOGICAL FUNCTION decchk(string,n,ch)
      INTEGER n
      CHARACTER string*(*),ch*1
      INTEGER ij(10,10),ip(10,8),i,j,k,m
      SAVE ij,ip
      DATA ip/0,1,2,3,4,5,6,7,8,9,1,5,7,6,2,8,3,0,9,4,5,8,0,3,7,9,6,1,4,
     *2,8,9,1,6,0,4,3,5,2,7,9,4,5,3,1,2,6,8,7,0,4,2,8,6,5,7,3,9,0,1,2,7,
     *9,3,8,0,6,4,1,5,7,0,4,6,9,1,3,2,5,8/,ij/0,1,2,3,4,5,6,7,8,9,1,2,3,
     *4,0,9,5,6,7,8,2,3,4,0,1,8,9,5,6,7,3,4,0,1,2,7,8,9,5,6,4,0,1,2,3,6,
     *7,8,9,5,5,6,7,8,9,0,1,2,3,4,6,7,8,9,5,4,0,1,2,3,7,8,9,5,6,3,4,0,1,
     *2,8,9,5,6,7,2,3,4,0,1,9,5,6,7,8,1,2,3,4,0/
      k=0
      m=0
      do 11 j=1,n
        i=ichar(string(j:j))
        if (i.ge.48.and.i.le.57)then
          k=ij(k+1,ip(mod(i+2,10)+1,mod(m,8)+1)+1)
          m=m+1
        endif
11    continue
      decchk=(k.eq.0)
      do 12 i=0,9
        if (ij(k+1,ip(i+1,mod(m,8)+1)+1).eq.0) goto 1
12    continue
1     ch=char(i+48)
      return
      end
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
