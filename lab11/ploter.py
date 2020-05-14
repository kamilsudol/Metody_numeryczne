import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

fig = plt.figure()	# stworzenie domyslnego obiektu figure

for i in range(1,4):
    file = "1_"+str(i)+".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data

    t = data[:, 0]	
    x = data[:, 1]

    plt.plot(t, x, 'r-', lw=1) # rysowanie wykresu

    plt.grid()	# siatka pomocnicza

    plt.savefig("1_"+str(i)+".png")	# zapis wykresu do pliku

    plt.clf()

for i in range(1,4):
    file = "2_"+str(i)+".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data
    #tw=np.arange(0,200,0.01)
    t = data[:, 0]	
    x = data[:, 1]

    plt.plot(t, x, 'r-', lw=1) # rysowanie wykresu

    plt.grid()	# siatka pomocnicza

    plt.savefig("2_"+str(i)+".png")	# zapis wykresu do pliku

    plt.clf()

for i in range(1,4):
    file = "3_"+str(i)+".out"	# wczytanie pliku z danymi
    data = np.loadtxt(file)	# do tablicy data
    #tw=np.arange(0,200,0.01)
    t = data[:, 0]	
    x = data[:, 1]

    file2 = "niezaszumiony"+str(i)+".out"	# wczytanie pliku z danymi
    data2 = np.loadtxt(file2)	# do tablicy data
    #tw=np.arange(0,200,0.01)
    t2 = data2[:, 0]	
    x2 = data2[:, 1]

    plt.plot(t, x, 'r-', lw=1) # rysowanie wykresu
    plt.plot(t2, x2, 'k-', lw=1)
    
    plt.grid()	# siatka pomocnicza

    plt.savefig("3_"+str(i)+".png")	# zapis wykresu do pliku
    plt.clf()