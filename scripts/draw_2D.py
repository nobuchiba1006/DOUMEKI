
import numpy as np

import numpy as np
import matplotlib
matplotlib.use("Agg")

import matplotlib.pyplot as plt

data = np.loadtxt("data_out.dat", skiprows=1)

zen = data[:,0]
wlen = data[:, 1]
zenerr = np.zeros(len(zen))
ce_up = data[:,2]
ce_up_err = data[:,3]
ce_down = data[:,4]
ce_down_err = data[:,5]
ce = data[:,6]
ce_err = data[:,7]

plt.figure(0)
plt.errorbar(zen, ce, color="black", yerr=ce_err, label="2PMTs %3.0f nm"%(wlen[0]))
plt.errorbar(zen, ce_up, color="blue", yerr=ce_up_err, label="PMT 0(up) %3.0f nm"%(wlen[0]))
plt.errorbar(zen, ce_down, color="red", yerr=ce_down_err, label="PMT 1(down)%3.0f nm"%(wlen[0]))
plt.legend(loc="best")
plt.xlabel("angle[deg]")
plt.ylabel("CE / m2")
plt.ylim((0, 0.035))
plt.grid()

plt.savefig("ce.png")

