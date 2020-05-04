import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

for i in range(1,4):
    file = str(i)+".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data

    #t = data[:, 0]
    t = np.arange(1,data.shape[0]+1)
    x1 = data[:, 0]
    x2 = data[:, 1]
    x3 = data[:, 2]
    xm = data[:, 3]

    plt.plot(t, x1, label='x1') # rysowanie wykresu
    plt.plot(t, x2, label='x2') # rysowanie wykresu
    plt.plot(t, x3, label='x3') # rysowanie wykresu
    plt.plot(t, xm, label='xm') # rysowanie wykresu


    l1 = plt.legend()	# legenda
    plt.grid()	# siatka pomocnicza


    plt.savefig(str(i)+".png")	# zapis wykresu do pliku

    plt.clf()

    F1 = data[:, 4]
    F2 = data[:, 5]
    plt.plot(t, F1, label='F[x_1,x_2]') # rysowanie wykresu
    plt.plot(t, F2, label='F[x_1,x_2,x_3]') # rysowanie wykresu

    l1 = plt.legend()	# legenda
    plt.grid()	# siatka pomocnicza


    plt.savefig(str(i)+"_F.png")	# zapis wykresu do pliku

    plt.clf()