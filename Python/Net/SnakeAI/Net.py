import numpy as np
import random
import Organiser

class Generation():
	def __init__(self, population, num_parents, game_data, first_gen):
		self.population = population
		self.num_parents = num_parents
		self.game_data = game_data
		self.get_parents()
		self.children = np.array([])
		for child in range(population):
			self.children = np.append(self.children, Chromosome(game_data[child], 
																self.parents,
																first_gen,
																child))

	def get_parents(self):
		self.parents = np.load("parents.npy", allow_pickle = True)
		
	def parents_selection(self):
		# parent_1 = random.randint(0, self.population-1)
		# parent_2 = random.randint(0, self.population-1)
		# for child in range(self.population):
		# 	score = self.game_data[child]["score"]
		# 	if score > self.game_data[parent_1]["score"]:
		# 		parent_2 = parent_1
		# 		parent_1 = child
		# 	elif score > self.game_data[parent_2]["score"]:
		# 		parent_2 = child

		# print("parent_1", self.game_data[parent_1]["score"])
		# print("parent_2", self.game_data[parent_2]["score"])

		# parent_1 = self.children[parent_1]
		# parent_2 = self.children[parent_2]

		# np.savez("parent_1", weights_1=parent_1.weights_1, 
		# 					 weights_2=parent_1.weights_2) 
		# np.savez("parent_2", weights_1=parent_2.weights_1, 
		# 					 weights_2=parent_2.weights_2) 
		pass

		
class Chromosome():
	def __init__(self, child_data, parents, first_gen, number):
		self.child_data = child_data
		self.parents = parents
		self.number = number
		if first_gen:
			self.generate_weights()
		else:
			self.crossover()
			self.mutation()

	def generate_weights(self):
		self.weights_1 = np.random.uniform(low=-20.0, high=20.0, size=(24,16))
		self.weights_2 = np.random.uniform(low=-20.0, high=20.0, size=(16,4))
		# self.weights_1 = self.parent_1["weights_1"]
		# self.weights_2 = self.parent_1["weights_2"]

	def crossover(self):
		parents = self.parents

		parent_1 = self.number%parents.shape[0]
		parent_2 = (self.number+1)%parents.shape[0]

		self.weights_1 = parents[parent_1]["weights_1"]
		self.weights_2 = parents[parent_2]["weights_2"]

		for i in range(int(self.weights_1.shape[0]/2)):
			self.weights_1[i] = parents[parent_2]["weights_1"][i]
		for i in range(int(self.weights_2.shape[0]/2)):
			self.weights_2[i] = parents[parent_1]["weights_2"][i]
		
	def mutation(self):
		for row in range(self.weights_1.shape[0]-1):
			col = random.randint(0, (self.weights_1[row].size - 1))
			self.weights_1[row][col] += np.random.uniform(low=-10, high=10)

		for row in range(self.weights_2.shape[0]-1):
			col = random.randint(0, (self.weights_2[row].size - 1))
			self.weights_2[row][col] += np.random.uniform(low=-10, high=10)


	def collect_info(self):
		self.first_layer = Organiser.form_layer(self.child_data)

	def sigmoid(self, x):
		return 1 / (1 + np.exp(-x))

	def generate_turn(self):
		layer_0 = self.first_layer
		layer_1 = self.sigmoid(np.dot(layer_0, self.weights_1))
		layer_2 = self.sigmoid(np.dot(layer_1, self.weights_2))

		turn_index = 0
		turn = "LEFT"
		direction = self.child_data["snake"].direction

		for index in range(layer_2.size):
			if layer_2[index] > layer_2[turn_index]:
				turn_index = index

		# print(layer_2)


		# if turn_index == 0: #DOWN
		# 	if direction == "DOWN":
		# 		turn = "UP"
		# 	elif direction == "UP":
		# 		turn = "DOWN"
		# 	elif direction == "RIGHT":
		# 		turn = "LEFT"
		# 	else:
		# 		turn = "RIGHT"
		# elif turn_index == 1: #UP
		# 	if direction == "DOWN":
		# 		turn = "DOWN"
		# 	elif direction == "UP":
		# 		turn = "UP"
		# 	elif direction == "RIGHT":
		# 		turn = "RIGHT"
		# elif turn_index == 2: #RIGHT
		# 	if direction == "DOWN":
		# 		turn = "LEFT"
		# 	elif direction == "UP":
		# 		turn = "RIGHT"
		# 	elif direction == "RIGHT":
		# 		turn = "DOWN"
		# 	else:
		# 		turn = "UP"
		# elif turn_index == 3: #LEFT
		# 	if direction == "DOWN":
		# 		turn = "RIGHT"
		# 	elif direction == "UP":
		# 		turn = "LEFT"
		# 	elif direction == "RIGHT":
		# 		turn = "UP"
		# 	else:
		# 		turn = "DOWN"

		if turn_index == 0: #DOWN
			turn = "DOWN"
		elif turn_index == 1: #UP
			turn = "UP"
		elif turn_index == 2: #RIGHT
			turn = "RIGHT"
		elif turn_index == 3: #LEFT
			turn = "LEFT"

		# print(turn)

		return turn 
		

# test = Generation(20, 3)
# print(test.children)