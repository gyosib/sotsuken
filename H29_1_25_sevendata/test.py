import numpy as np
import matplotlib.pyplot as plt
from wavelets import WaveletAnalysis

# given a signal x(t)
#x = np.random.rand(2000)
t = np.linspace(-np.pi, np.pi, 360)
x = np.sin(t)
# and a sample spacing
dt = 100/360

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
fig.savefig('test.png')
