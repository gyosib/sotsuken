import numpy as np
import matplotlib.pyplot as plt
from wavelets import WaveletAnalysis

# given a signal x(t)
#x = np.random.rand(2000)
x = np.loadtxt('sand2030_cut.csv', delimiter = ' ')
# and a sample spacing
dt = 1/5000

wa = WaveletAnalysis(x, dt=dt)

# wavelet power spectrum
power = wa.wavelet_power

# scales 
scales = wa.scales

# associated time vector
t = wa.time

# reconstruction of the original data
rx = wa.reconstruction()

fig, ax = plt.subplots()
T, S = np.meshgrid(t, scales)
ax.contourf(T, S, power, 100)
ax.set_yscale('log')
fig.savefig('sand2030_wavelet.png')
