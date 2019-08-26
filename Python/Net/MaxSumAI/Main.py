import numpy as np
import Ga as ga

# Y = x1w1 + x2w2 + x3w3 + ... 

equation_inputs = [4, -2, 3.5, 5, -11, 4.7] # Inputs of the equation
num_weights = 6 # Number of weights we are looking to optimize
sol_per_pop = 8000 # Solutions / individuals per population
pop_size = (sol_per_pop, num_weights) # Defining the population size
new_population = np.random.uniform(low=-4.0, high=4.0, size=pop_size) #Creating the initial population

# print(new_population)

num_generations = 24
num_parents_mating = 4

for generation in range(num_generations):

	fitness = ga.cal_pop_fitness(equation_inputs, new_population) # Measuring the fitness of each chromosome in population
	print(max(fitness))
	parents = ga.select_mating_pool(new_population, fitness, num_parents_mating) # Selecting the best parents in the population for mating
	offspring_crossover = ga.crossover(parents, 
		offspring_size=(pop_size[0]-parents.shape[0], num_weights)) # Generating next generation using crossover
	offspring_mutation = ga.mutation(offspring_crossover) 	# Adding some variations to the offspring using mutation

	# Creating the new population based on parents and offspring
	new_population[0:parents.shape[0], :] = parents
	new_population[parents.shape[0]:, :] = offspring_mutation




