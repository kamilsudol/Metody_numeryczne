import numpy as np		# importowanie przydatnych modulow
import matplotlib.pyplot as plt

file = "out1.txt"
data = np.loadtxt(file)
alfa = data[:,0]
var=data[:,1:]

plt.grid()

for i in range(6):
    plt.plot(alfa,var[:,i],'-o',ms=3,label="w"+str(i)+" = sqrt( lambda" + str(i)+")")

plt.legend(loc="upper right")
plt.savefig("pierwiastki.png")

plt.close()

#################################################################

file = "out2.txt"
data = np.loadtxt(file)
x = data[:,0]
var=data[:,1:]

plt.grid()

for i in range(6):
    plt.plot(x,var[:,i],'-',ms=3,label="u"+str(i)+"(x)")

plt.legend(loc="upper right")
plt.savefig("wek_wlasne_0.png")

plt.close()

#################################################################

file = "out3.txt"
data = np.loadtxt(file)
x = data[:,0]
var=data[:,1:]

plt.grid()

for i in range(6):
    plt.plot(x,var[:,i],'-',ms=3,label="u"+str(i)+"(x)")

plt.legend(loc="upper right")
plt.savefig("wek_wlasne_100.png")

plt.close()