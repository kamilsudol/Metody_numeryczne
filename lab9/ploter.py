import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

for i in range(1,4):
    file1 = "g_1_" + str(i) + ".out"	# wczytanie pliku z danymi
    data1 = np.loadtxt(file1)	# do tablicy data

    file2 = "G_1_" + str(i) + ".out"	# wczytanie pliku z danymi
    data2 = np.loadtxt(file2)	# do tablicy data

    t = data1[:, 0]	
    x = data1[:, 1]

    t2 = data2[:, 0]	
    x2 = data2[:, 1]

    #y = np.arange(-5,5,0.01)

    plt.plot(t, x, 'bo', lw=1, label='g(x)') # rysowanie wykresu
    plt.plot(t2, x2, 'r-', lw=1.3, label='G(x)') # rysowanie wykresu

    #plt.title("f(x) = 1/(1+x^2)")
    plt.legend(loc='upper right')	# legenda
    plt.grid()	# siatka pomocnicza

    plt.savefig("fig_1_" + str(i) + ".png")	# zapis wykresu do pliku
    plt.clf()

for i in range(1,5):
    file1 = "g_2_" + str(i) + ".out"	# wczytanie pliku z danymi
    data1 = np.loadtxt(file1)	# do tablicy data

    file2 = "G_2_" + str(i) + ".out"	# wczytanie pliku z danymi
    data2 = np.loadtxt(file2)	# do tablicy data

    t = data1[:, 0]	
    x = data1[:, 1]

    t2 = data2[:, 0]	
    x2 = data2[:, 1]

    #y = np.arange(-5,5,0.01)

    plt.plot(t, x, 'bo', lw=1, label='g2(x)') # rysowanie wykresu
    plt.plot(t2, x2, 'r-', lw=1.3, label='G(x)') # rysowanie wykresu

    #plt.title("f(x) = 1/(1+x^2)")
    plt.legend(loc='upper right')	# legenda
    plt.grid()	# siatka pomocnicza

    plt.savefig("fig_2_" + str(i) + ".png")	# zapis wykresu do pliku
    plt.clf()