import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

for i in range(1,5):
    file = "fun" + str(i) + ".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data

    t = data[:, 0]	
    x = data[:, 1]
    y = np.arange(-5,5,0.01)

    plt.plot(t, x, 'b-', lw=1, label='Interpolacja') # rysowanie wykresu
    plt.plot(y, 1/(1+y**2), 'k-', lw=1, label='f(x)') # rysowanie wykresu

    plt.title("f(x) = 1/(1+x^2)")
    plt.legend(loc='upper right')	# legenda
    plt.grid()	# siatka pomocnicza

    plt.savefig("fig" + str(i) + ".png")	# zapis wykresu do pliku
    plt.clf()

for i in range(1,4):
    file = "cos" + str(i) + ".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data

    t = data[:, 0]	
    x = data[:, 1]
    y = np.arange(-5,5,0.01)

    plt.plot(t, x, 'b-', lw=1, label='Interpolacja') # rysowanie wykresu
    plt.plot(y, np.cos(2*y), 'k-', lw=1, label='f(x)') # rysowanie wykresu

    plt.title("f(x) = cos(2x)")
    plt.legend(loc='upper right')	# legenda
    plt.grid()	# siatka pomocnicza

    plt.savefig("fig" + str(i+4) + ".png")	# zapis wykresu do pliku
    plt.clf()
