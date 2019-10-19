import numpy as np 


def sigmoid(x):
	return 1 / (1 + np.exp(-x))

training_inputs = np.array([[0,0,1],
							# [0,1,1],
							# [1,0,1],
							# [1,1,1]
							])

training_outputs = np.array([[0],
							 # [1],
							 # [1],
							 # [0]
							 ])

np.random.seed(1)


weights_1 = 2 * np.random.random((3,4)) - 1
weights_2 = 2 * np.random.random((4,1)) - 1

print("weights_1:\n", weights_1)
print("weights_2:\n", weights_2)

layer_0 = training_inputs
print("layer_0:\n", layer_0)
layer_1 = np.dot(layer_0, weights_1)
print("layer_1:\n", layer_1)
layer_2 = np.dot(layer_1, weights_2)
print("layer_2:\n", layer_2)




