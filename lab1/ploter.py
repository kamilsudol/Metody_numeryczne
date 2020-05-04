import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

file = "out.txt"	# wczytanie pliku z danymi
data = np.loadtxt(file)	# do tablicy data
tw=np.arange(0,200,0.01)
t = data[:, 0]	
x = data[:, 1]

plt.plot(t, x, 'bx', lw=2, label='x(t), h=0.1') # rysowanie wykresu
plt.plot(tw, np.cos(tw/10), 'k-', lw=2, label='cos(t)') # wykres funkcji analitycznej

l1 = plt.legend()	# legenda
plt.grid()	# siatka pomocnicza

plt.xlabel('t')	# tytuly osi i wykresu
plt.ylabel('x(t)')
plt.title('wychylenie x(t)')

plt.savefig("zad1.png")	# zapis wykresu do pliku

