from matplotlib import mlab
import pylab
import numpy as np
import math as m


def func(x):
	
	return 1/x

xmin = -20.0
xmax = 20.0

dx = 0.01

x = np.linspace(-2*np.pi, 2*np.pi, 1000)
y = (np.sin(x)) / (np.cos(x))
#print(xlist)

#x = range(xmin, xmax, dx)
#y = [func(x) for x in xlist]
tol = 15
y[y > tol] = np.nan
y[y < -tol] = np.nan


pylab.plot(x, y, '-g', lw=1)
pylab.ylim(-10, 10)
pylab.show()












