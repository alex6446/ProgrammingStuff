import pygame
import numpy as np
import random
import math

class Net():
	def __init__(self):
		self.weights = np.random.uniform(low=-2.0, high=2.0, size=(2,4))

	def get_direction(self, input):
		output = self.sigmoid(np.dot(input, self.weights))
		#direction = np.where(output == np.amax(output))[0][0]
		direction = [int((output[0] - output[1])*5), 
					int((output[2] - output[3])*5)]
		return direction;

	def sigmoid(self, x):
		return 1 / (1 + np.exp(-x))

	def mutate(self):
		probability = 0.001
		for i in range(self.weights.shape[0]):
			for j in range(self.weights.shape[1]):
				if random.random() < probability:
					self.weights[i][j] += random.uniform(-1.0, 1.0) 

class Dot():
	def __init__(self, screen, width, height, aim, dot):
		self.screen = screen
		self.width = width
		self.height = height
		self.aim = aim
		self.dot = dot

		self.position = self.dot["position"]
		self.alive = True
		self.win = False
		self.steps = 0
		self.max_steps = 300

		self.brain = Net()

	def form_input(self):
		input = np.array([
			self.aim["position"][0] - self.position[0],
			self.aim["position"][1] - self.position[1],
			# self.width - self.position[0],
			# self.height - self.position[1],
			# self.position[0],
			# self.position[1]
		])
		return input
		
	def fitness(self):
		score = (abs(self.position[0] - self.aim["position"][0]) + 
				 abs(self.position[1] - self.aim["position"][1]))
		score = self.steps/score
		if self.win:
			score *= 2
		return int(score)

	def reset(self):
		self.position = self.dot["position"]
		self.alive = True
		self.win = False
		self.steps = 0

	def update(self):
		if self.alive and not self.win:
			self.steps += 1
			direction = self.brain.get_direction(self.form_input())
			acceleration = direction
			# if direction == 0:
			# 	acceleration = [0, -self.dot["velocity"]]
			# elif direction == 1:
			# 	acceleration = [0, self.dot["velocity"]]
			# elif direction == 2:
			# 	acceleration = [-self.dot["velocity"], 0]
			# else:
			# 	acceleration = [self.dot["velocity"], 0]
			#self.position = [x + y for x, y in zip(self.position, acceleration)]
			self.position = [self.position[0]+acceleration[0],
							 self.position[1]+acceleration[1]]

		if (self.position[0] <= 0 or self.position[0] >= self.width or
			self.position[1] <= 0 or self.position[1] >= self.height):
			self.alive = False

		if (math.sqrt((self.position[0]-self.aim["position"][0])**2 + 
				 	  (self.position[1]-self.aim["position"][1])**2) <=
					   self.dot["radius"] + self.aim["radius"]):
			self.win = True
			self.alive = False

		if self.steps >= self.max_steps:
			self.alive = False

	def draw(self):
		pygame.draw.circle(screen, self.dot["color"], self.position, self.dot["radius"])


class Population():
	def __init__(self, size, screen, width, height, aim, dot):
		self.size = size
		self.is_dead = False
		self.is_win = 0
		self.dots = np.array([])
		for i in range(self.size):
			self.dots = np.append(self.dots, 
										Dot(screen, width, height, aim, dot))

	def reset(self):
		self.is_dead = False
		for i in range(self.size):
			self.dots[i].reset()

	def count_fitness(self):
		self.fitness_sum = 0
		for i in range(self.size):
			self.fitness_sum += self.dots[i].fitness()

	def natural_selection(self):
		for i in range(self.size):
			self.dots[i].brain.weights = self.dots[self.select_parent()].brain.weights

	def select_parent(self):
		pivot = random.randint(0, self.fitness_sum)
		currentSum = 0
		for i in range(self.size):
			currentSum += self.dots[i].fitness()
			if currentSum >= pivot:
				return i;

	def mutate(self):
		for i in range(self.size):
			self.dots[i].brain.mutate()

	def update(self):
		self.is_dead = True
		self.is_win = 0
		for i in range(self.size):
			if self.dots[i].alive:
				self.is_dead = False
			if self.dots[i].win:
				self.is_win += 1
			self.dots[i].update()

	def draw(self):
		for i in range(self.size):
			self.dots[i].draw()


class Evolution():
	def __init__(self, dots, screen, width, height, aim, dot, generations):
		self.screen = screen
		self.generations = generations
		self.current_generation = 1
		self.population = Population(dots, screen, width, height, aim, dot)
		self.font = pygame.font.Font('Roboto-Regular.ttf', 20)

	def update(self):
		self.generation_number = self.font.render('Generation: ' + 
							str(self.current_generation), True, (0, 0, 0))
		self.win_number = self.font.render('Won: ' + 
							str(self.population.is_win), True, (0, 0, 0))
		if self.current_generation <= self.generations:
			if not self.population.is_dead:
				self.population.update()
			else:
				self.current_generation += 1
				self.population.count_fitness()
				self.population.natural_selection()
				self.population.reset()
				self.population.mutate()

	def draw(self):
		self.population.draw()
		self.screen.blit(self.generation_number,(10, 5))
		self.screen.blit(self.win_number,(10, 25))




WIDTH = 600
HEIGHT = 600
FPS = 25

GENERATIONS = 20
POPULATION = 1000

BACKGROUND_COLOR = (245, 245, 245)
AIM = {
	"color": (178, 34, 34), 
	"position": (int(WIDTH/2), 50),
	"radius": 9
}
DOT = {
	"color": (0, 0, 0), 
	"position": [int(WIDTH/1.5), HEIGHT-50],
	"radius": 3,
	"velocity": 5
}

pygame.init()
pygame.font.init()

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Game")
clock = pygame.time.Clock()
font = pygame.font.Font('Roboto-Regular.ttf', 25) #SysFont('Comic Sans MS', 30)

evolution = Evolution(POPULATION, screen, WIDTH, HEIGHT, AIM, DOT, GENERATIONS)


running = True
while running:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
			running = False
	evolution.update()

	screen.fill(BACKGROUND_COLOR)
	pygame.draw.circle(screen, AIM["color"], AIM["position"], AIM["radius"])
	evolution.draw()
	pygame.display.flip()

pygame.quit()