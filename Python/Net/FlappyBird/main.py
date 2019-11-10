import pygame
import random
import math
import numpy as np

WIDTH = 450
HEIGHT = 650
FPS = 60

BACKGROUND_COLOR = (113, 197, 207)

class Net():
	def __init__(self):
		self.create()

	def create(self):
		self.weights = np.array([
			np.random.uniform(low=-2.0, high=2.0, size=(3,2)),
			#np.random.uniform(low=-2.0, high=2.0, size=(4,2))
		])

	def jump(self, input):
		#layer = self.sigmoid(np.dot(input, self.weights[0]))
		output = self.sigmoid(np.dot(input, self.weights[0]))
		if output[0] > output[1]:
			return True
		else: return False 

	def sigmoid(self, x):
		return 1 / (1 + np.exp(-x))

	def mutate(self):
		probability = 0.001
		for i in range(self.weights.shape[0]):
			for j in range(self.weights[i].shape[0]):
				for k in range(self.weights[i].shape[1]):
					if random.random() < probability:
						self.weights[i][j][k] += random.uniform(-1.0, 1.0) 

class Game():
	def __init__(self):
		self.brain = Net()
		self.brain.mutate()
		self.score_max = 0
		self.setup()

	def setup(self):
		self.position = [int(WIDTH/2), int(HEIGHT/2)]
		self.jump = False
		self.x = 0
		self.start = True
		self.dead = False
		self.on_floor = False
		self.pipes = []
		self.time_alive = 0
		self.score = 0
		self.score_number = font.render('Score: ' + str(self.score), True, (0, 0, 0))
		self.score_max_number = font.render('Max: ' + str(self.score_max), True, (0, 0, 0))

	def gen_rand_pos(self):
		pos = random.randint(pipe_height+100, HEIGHT-(floor_height+100))
		return pos

	def get_distance(self, x1, y1, x2, y2):
		return math.sqrt((x2-x1)**2 + (y2-y1)**2)

	def form_input(self):
		input = []
		for pipe in reversed(self.pipes):
			if self.position[0] < pipe[0] + pipe_width:
				input.append(pipe[0] + pipe_width - self.position[0])
				input.append(self.position[1] - pipe[1])
				input.append(pipe[1] - pipe_height - self.position[1])
				return input
	
	def fitness(self):
		return self.time_alive * (self.score + 1)

	def make_jump(self):
		if self.brain.jump(self.form_input()):
			if not self.dead:
				self.start = True
				self.jump = True
				self.x = -3.1 #3.5 #-2.5

	def reset(self):
		self.setup()
		#self.brain.create()

	def update(self):
		if len(self.pipes):
			self.make_jump()
		if self.start:
			if not self.jump and not self.on_floor:
				self.position = [self.position[0], self.position[1] + int(self.x*self.x/1.6)]
				if self.x < 4.3:
					self.x += 0.18 #18
			elif not self.dead:
				self.position = [self.position[0], self.position[1] - int(self.x*self.x)] #1 #*2.5
				self.x += 0.15 #0.2 #0.158 
				if self.x > -1:
					self.jump = False
					self.x = 0

			if self.position[1]+r >= HEIGHT-floor_height:
				self.on_floor = True
				self.dead = True
				self.start = False

			if not self.dead:
				self.time_alive += 1
				if not len(self.pipes):
					self.pipes.append([WIDTH, self.gen_rand_pos()])
				else:
					if self.pipes[0][0]+pipe_width <= 0:
						self.pipes.pop(0)
					if self.pipes[-1][0]+pipe_width+pipe_distance <= WIDTH:
						self.pipes.append([WIDTH, self.gen_rand_pos()])
				for pipe in self.pipes:
					if (self.position[0] < pipe[0] + pipe_width and 
					    self.position[0] > pipe[0] + pipe_width - speed):
						self.score += 1
					pipe[0] -= speed	

				for pipe in self.pipes:
					if (self.position[1]+r > pipe[1] and 
						self.position[0]+r > pipe[0] and 
						self.position[0]-r < pipe[0]+pipe_width):
						self.dead = True
						self.jump = False
						self.x = 0
					if (self.position[1]-r < pipe[1]-pipe_height and 
						self.position[0]+r > pipe[0] and 
						self.position[0]-r < pipe[0]+pipe_width):
						self.dead = True
						self.jump = False
						self.x = 0
				self.score_number = font.render('Score: ' + str(self.score), True, (0, 0, 0))
			if self.score > self.score_max:
				self.score_max = self.score
				self.score_max_number = font.render('Max: ' + str(self.score_max), True, (0, 0, 0))

	def draw(self):
		if len(self.pipes):
			for pipe in self.pipes:
				pygame.draw.rect(screen, (34, 139, 34), (pipe[0], pipe[1], pipe_width, HEIGHT-pipe[1]))
				pygame.draw.rect(screen, (34, 139, 34), (pipe[0], 0, pipe_width, pipe[1]-pipe_height))
		pygame.draw.circle(screen, (139, 34, 34), self.position, r)
		screen.blit(self.score_number,(10, 5))
		screen.blit(self.score_max_number,(200, 5))


class Population():
	def __init__(self, size):
		self.size = size
		self.is_dead = False
		self.num_alive = 0
		self.birds = np.array([])
		for i in range(self.size):
			self.birds = np.append(self.birds, Game())

	def reset(self):
		self.is_dead = False
		for i in range(self.size):
			self.birds[i].reset()

	def count_fitness(self):
		self.fitness_sum = 0
		for i in range(self.size):
			self.fitness_sum += self.birds[i].fitness()

	def natural_selection(self):
		temp_birds = list(self.birds)
		for i in range(self.size):
			if not i:
				temp_birds[i].brain.weights = self.birds[self.get_best()].brain.weights
			else:	
				temp_birds[i].brain.weights = self.birds[self.select_parent()].brain.weights
		self.birds = list(temp_birds)

	def get_best(self):
		fitness = 0
		index = 0
		for i in range(self.size):
			if self.birds[i].fitness() > fitness:
				fitness = self.birds[i].fitness()
				index = i
		return index

	def select_parent(self):
		pivot = random.randint(0, self.fitness_sum)
		currentSum = 0
		for i in range(self.size):
			currentSum += self.birds[i].fitness()
			if currentSum >= pivot:
				return i;

	def mutate(self):
		for i in range(self.size):
			if i:
				self.birds[i].brain.mutate()

	def update(self):
		self.is_dead = True
		self.num_alive = 0
		for i in range(self.size):
			if not self.birds[i].dead:
				self.is_dead = False
				self.num_alive += 1
			self.birds[i].update()

	def draw(self):
		for i in range(self.size):
			if not self.birds[i].dead:
				self.birds[i].draw()
				break


class Evolution():
	def __init__(self, birds, generations):
		self.screen = screen
		self.generations = generations
		self.current_generation = 1
		self.population = Population(birds)
		self.font = pygame.font.Font('Roboto-Regular.ttf', 20)

	def update(self):
		self.generation_number = self.font.render('Generation: ' + 
							str(self.current_generation), True, (0, 0, 0))
		self.win_number = self.font.render('Alive: ' + 
							str(self.population.num_alive), True, (0, 0, 0))
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
		self.screen.blit(self.generation_number,(10, 35))
		self.screen.blit(self.win_number,(10, 55))




pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Numbers visualise")
clock = pygame.time.Clock()
font = pygame.font.Font('Roboto-Regular.ttf', 25)

GENERATIONS = 1000
POPULATION = 1000

r = 15
speed = 2
floor_height = 60
pipe_width = 70
pipe_height = 130
pipe_distance = 130

#DaGame = Game()
Generation = Evolution(POPULATION, GENERATIONS)

while True:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				#DaGame.reset()
				Generation.population.reset()
			# if event.key == pygame.K_SPACE:
			# 	Generation.population.start()
			# 	#DaGame.start = True

	# update #####################

	#DaGame.update()
	Generation.update()

	# draw #######################

	screen.fill(BACKGROUND_COLOR)
	#DaGame.draw()
	Generation.draw()
	pygame.draw.rect(screen, (139,69,19), (0, HEIGHT-floor_height, WIDTH, floor_height))
	pygame.display.flip()






