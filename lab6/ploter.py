import numpy as np
import matplotlib.pyplot as plt

file = "out2"
data = np.loadtxt(file)
re = data[:, 0]
im = data[:, 1]

re = re.reshape(4,-1)
im = im.reshape(4,-1)

plt.xlabel("Re(z)")
plt.ylabel("Im(z)")

for i in np.arange(0,4):
    plt.plot(re[i], im[i], '-o', label = "Z("+str(i)+")")

plt.legend(loc="upper left")  

plt.show()