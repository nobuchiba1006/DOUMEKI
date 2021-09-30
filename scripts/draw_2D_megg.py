
import numpy as np

import numpy as np
import matplotlib
matplotlib.use("Agg")
import sys

import matplotlib.pyplot as plt

data = np.loadtxt("data_out.dat", skiprows=1)
print(data.shape)
npmts = int((data.shape[1] - 4) / 2)

zen = data[:,0]
wlen = data[:, 1]
zenerr = np.zeros(len(zen))

ces = []
ces_err = []

index = 1
for i in range(npmts) :
    index += 1
    ces.append(data[:, index])
    index += 1
    ces_err.append(data[:, index])
    
index += 1
totce = data[:,index]
index += 1
totce_err = data[:,index]

colors_20 = ["#1f77b4", "#aec7e8", "#ff7f0e", "#ffbb78", "#2ca02c", "#98df8a", "#d62728", "#ff9896", "#9467bd","#c5b0d5", "#8c564b", "#c49c94", "#e377c2", "#f7b6d2", "#7f7f7f", "#c7c7c7", "#bcbd22", "#dbdb8d", "#17becf", "#9edae5"]


plt.figure(0)
plt.errorbar(zen, totce, color="black", yerr=totce_err, label="all PMTs %3.0f nm"%(wlen[0]))
for i in range(npmts) :
    plt.errorbar(zen, ces[i], color=colors_20[i], yerr=ces_err[i], label="PMT %d %3.0f nm"%(i, wlen[0]))
#plt.legend(loc="best")
plt.xlabel("angle[deg]")
plt.ylabel("CE / m2")
plt.ylim((0, 0.05))
plt.grid()

plt.savefig("ce.png")

