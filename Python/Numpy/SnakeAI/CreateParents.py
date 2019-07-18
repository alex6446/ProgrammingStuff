import numpy as np

num_parents = 250
parents = np.array([])

for num in range(num_parents):
	parent = {
			 "weights_1": 2 * np.random.random((24,16)) - 1, 
			 "weights_2": np.random.random((16,4)) - 1,
			 }
	parents = np.append(parents, parent)


np.save("parents", parents)


