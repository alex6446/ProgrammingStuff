import numpy as np 

def sigmoid(x):
	return 1 / (1 + np.exp(-x))

training_inputs = np.array([[0,0,1],
							[1,1,1],
							[1,0,1],
							[0,1,1]])

training_outputs = np.array([[0],
							 [1],
							 [1],
							 [0]])



np.random.seed(1)

synaptic_weights = 2 * np.random.random((3,1)) - 1

# print("Случайные веса: ")
# print(synaptic_weights)

input_layer = training_inputs
print("input_layer:\n", input_layer)
print("synaptic_weights:\n", synaptic_weights)
outputs = sigmoid( np.dot(input_layer, synaptic_weights))
print("outputs:\n", outputs)

#Метод обратного распространения
for i in range(50000):
	input_layer = training_inputs
	outputs = sigmoid( np.dot(input_layer, synaptic_weights))

	err = training_outputs - outputs
	# print("\n*******\n")
	# print("training_outputs:\n", training_outputs)
	# print("err:\n", err)

	adjustments = err * (outputs * (1 - outputs))

	# print("adjustments:\n", adjustments)

	synaptic_weights += np.dot( input_layer.T, adjustments)


print("Веса после обучения")
print(synaptic_weights)

print("Результат после обучения: ")
print(outputs)

#TEST
new_inputs = np.array([1,1,0])
output = sigmoid( np.dot( new_inputs, synaptic_weights))

print("Новые данные: ")
print(output)

