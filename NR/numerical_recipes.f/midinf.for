      SUBROUTINE midinf(funk,aa,bb,s,n)
      INTEGER n
      REAL aa,bb,s,funk
      EXTERNAL funk
      INTEGER it,j
      REAL a,b,ddel,del,sum,tnm,func,x
      func(x)=funk(1./x)/x**2
      b=1./aa
      a=1./bb
      if (n.eq.1) then
        s=(b-a)*func(0.5*(a+b))
      else
        it=3**(n-2)
        tnm=it
        del=(b-a)/(3.*tnm)
        ddel=del+del
        x=a+0.5*del
        sum=0.
        do 11 j=1,it
          sum=sum+func(x)
          x=x+ddel
          sum=sum+func(x)
          x=x+del
11      continue
        s=(s+(b-a)*sum/tnm)/3.
      endif
      return
      END
C  (C) Copr. 1986-92 Numerical Recipes Software 7&X*!'(.
