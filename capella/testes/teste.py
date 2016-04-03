import numpy as np
import matplotlib.pyplot as plt
import sys

x = []
y = []

for line in sys.stdin:
	l = line.split(' ')
	if (len(l) > 1):
		x.append(float(l[0]))
		y.append(float(l[1]))

plt.plot(x, y, 'ro')
plt.axis([min(x)-100, max(x)+100, min(y)-100, max(y)+100])
plt.show()

plt.show()