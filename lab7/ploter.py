import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

file = "rownolegle4.out"	# wczytanie pliku z danymi
data = np.loadtxt(file)	# do tablicy data
tw=np.arange(-5,5,0.01)
t = data[:, 0]	
x = data[:, 1]

plt.plot(t, x, 'b-', lw=2, label='n = 20') # rysowanie wykresu
plt.plot(tw, 1/(1+tw**2), 'k-', lw=2, label='f(x)') # wykres funkcji analitycznej

l1 = plt.legend()	# legenda
plt.grid()	# siatka pomocnicza

#plt.xlabel('t')	# tytuly osi i wykresu
#plt.ylabel('x(t)')
plt.title('Węzły równoodległe')

plt.savefig("zad8.png")	# zapis wykresu do pliku

