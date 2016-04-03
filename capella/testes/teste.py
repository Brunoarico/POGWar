import numpy as np
import matplotlib.pyplot as plt

with open("test.txt") as f:
    data = f.read()

data = data.split('\n')
x = []
y = []
print data
for k in data:
	l = k.split(' ')
	if (len(l) > 1):
		x.append(float(l[0]))
		y.append(float(l[1]))

plt.plot(x, y, 'ro')
plt.axis([min(x)-100, max(x)+100, min(y)-100, max(y)+100])
plt.show()

plt.show()