import math
import numpy as np

size = 15
HEIGHT = 600
WIDTH = 600

for y in range(300 - size, -1, -size):
	print(y)

for y in range(300 + size, HEIGHT - size + 1, size):
	print(y)

wall_down_right = math.sqrt(2)*min(30, 300)
print(wall_down_right)

for cord in range(size, min(105, 165) - 1*size + 1, size):
	cords = [WIDTH-105 + cord, HEIGHT-165 + cord] # 495  435
	print(cords)

weights_1 = np.random.uniform(low=-10.0, high=10.0, size=(18,4))
print(weights_1)
num = np.random.uniform(low=-1.5, high=1.5)
print(num)