import pygame
import random
import numpy as np
import Net

WIDTH = 600
HEIGHT = 600
FPS = 15

BACKGROUND_COLOR = (20,26,27)
FRUIT_COLOR = (237,67,55)
HEAD_COLOR = (0,137,123)
BODY_COLOR = (0,86,77)
TEXT_COLOR = (245, 245, 245)
# BLACK = (20,26,27)
# LIGHT = (245, 245, 245)
# DARK = (54,54,54)
# GREY = (150,150,150)
# TEAL_DARK = (0,86,77)
# TEAL_LIGHT = (0,137,123)

GENERATIONS = 500
POPULATION = 1000
PARENTS = int(POPULATION/4)

class Snake():
	def __init__(self, screen):
		global WIDTH, HEIGHT
		self.WIDTH = WIDTH
		self.HEIGHT = HEIGHT
		self.screen = screen
		self.active = True
		self.body = [[WIDTH / 2, HEIGHT / 4], [300, 135], [300, 120], [300, 105]] #, [300, 130], [300, 120], [300, 110], [300, 100], [300, 90], [300, 80], [300, 70], [300, 60], [300, 50], [300, 40], [300, 30], [300, 20], [300, 10], [300, 0], [290, 0], [280, 0], [270, 0], [260, 0], [250, 0], [240, 0], [230, 0], [220, 0], [210, 0], [200, 0], [190, 0], [180, 0]] # Position X, Y
		self.size = 15
		self.step = self.size
		self.direction = "DOWN"

	def update(self, position):
		direction = self.direction
		body = self.body
		step = self.step
		eaten = False

		temp = body[-1]

		def reDraw():
			for i in range(len(body) - 1, 0, -1):
				body[i] = list(body[i - 1])

		if direction == "DOWN":
			reDraw()
			body[0][1] += step
		elif direction == "UP":
			reDraw()
			body[0][1] -= step
		elif direction == "RIGHT":
			reDraw()
			body[0][0] += step
		elif direction == "LEFT":
			reDraw()
			body[0][0] -= step

		if body[0] == position:
			body.append(temp)
			return "eaten"
		else:
			return False

	def draw(self):
		global HEAD_COLOR, BODY_COLOR
		body = self.body
		size = self.size
		screen = self.screen
		for part in body:
			if part == body[0]:
				pygame.draw.rect(screen, HEAD_COLOR, (part[0], part[1], size, size))
			else:
				pygame.draw.rect(screen, BODY_COLOR, (part[0]+1, part[1]+1, size-2, size-2))

	def turn(self, side):
		direction = self.direction
		if side == "DOWN" :
			self.direction = "DOWN"
		if side == "UP" :
			self.direction = "UP"
		if side == "RIGHT" :
			self.direction = "RIGHT"
		if side == "LEFT" :
			self.direction = "LEFT"

	def check(self):
		global WIDTH, HEIGHT
		body = self.body
		size = self.size
		x = body[0][0]
		y = body[0][1]
		if body.count(body[0]) > 1:
			return False

		if x < 0 or x >= WIDTH:
			return False
		if y < 0 or y >= HEIGHT:
			return False

		return True

class Fruit():
	def __init__(self, screen, body):
		self.screen = screen
		self.size = 15
		self.generate(body)

	def generate(self, body):
		global WIDTH, HEIGHT
		size = self.size
		complete = False
		free = []
		for i in range(0, WIDTH - size + 1, size):
			for j in range(0, HEIGHT - size + 1, size):
				cords = [i, j]
				if cords not in body:
					free.append(cords)

		self.position = random.choice(free)

	def draw(self):
		global FRUIT_COLOR
		screen = self.screen
		size = self.size
		x = self.position[0]
		y = self.position[1]
		pygame.draw.rect(screen, FRUIT_COLOR, (x, y, size, size))


pygame.init()
pygame.font.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake Game")
clock = pygame.time.Clock()
font = pygame.font.Font('Roboto-Regular.ttf', 25) #SysFont('Comic Sans MS', 30)
info_font = pygame.font.Font('Roboto-Regular.ttf', 15)

for generation in range(GENERATIONS):
	game_data = np.array([])
	for chromosome in range(POPULATION):
		snake = Snake(screen)
		fruit = Fruit(screen, snake.body)
		score = 3
		game_data = np.append(game_data, {
										"snake": snake, 
										"fruit": fruit, 
										"score": score,
										})
	# print(game_data)
	chromosome = random.randint(0, game_data.size - 1)

	if generation == 0:
		gen = Net.Generation(POPULATION, PARENTS, game_data, True)
	else:
		gen = Net.Generation(POPULATION, PARENTS, game_data, False) #False

	running = True
	while running:
		clock.tick(FPS)

		for chromo in range(game_data.size):
			if game_data[chromo]["snake"].active == True and game_data[chromo]["score"] > game_data[chromosome]["score"]:
				chromosome = chromo

		# snake = game_data[chromosome]["snake"]
		# fruit = game_data[chromosome]["fruit"]
		# score = game_data[chromosome]["score"]

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()
				running = False
			if event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					game_data[chromosome]["snake"].active = False
					game_data[chromosome]["score"] = 0
			# 	if event.key == pygame.K_DOWN:
			# 		game_data[chromosome]["snake"].turn("DOWN")
			# 	if event.key == pygame.K_UP:
			# 		game_data[chromosome]["snake"].turn("UP")
			# 	if event.key == pygame.K_RIGHT:
			# 		game_data[chromosome]["snake"].turn("RIGHT")
			# 	if event.key == pygame.K_LEFT:
			# 		game_data[chromosome]["snake"].turn("LEFT")

		# Feed information
		for child in range(POPULATION):
			if game_data[child]["snake"].active == True:
				gen.children[child].collect_info()
				direction = gen.children[child].generate_turn()
				game_data[child]["snake"].turn(direction)

		# print(gen.children[chromosome].first_layer)

		# Update
		for chromo in range(game_data.size):
			if game_data[chromo]["snake"].active == True:
				game_data[chromo]["score"] += 1
				if game_data[chromo]["snake"].update(game_data[chromo]["fruit"].position) == "eaten":
					game_data[chromo]["fruit"].generate(game_data[chromo]["snake"].body)
					game_data[chromo]["score"] += 100
				if not game_data[chromo]["snake"].check():
					game_data[chromo]["snake"].active = False
			if game_data[chromo]["score"] > 1000:
				game_data[chromo]["score"] = 0
				game_data[chromo]["snake"].active = False

		if game_data[chromosome]["snake"].active == False:
			for chromo in range(game_data.size):
				if game_data[chromo]["snake"].active == True:
					chromosome = chromo
					running = True
					break
				else:
					running = False



		score_text = font.render('Score: ' + str(game_data[chromosome]["score"]), True, TEXT_COLOR)
		generation_number = info_font.render('Generation: ' + str(generation+1), True, TEXT_COLOR)
		chromosome_index = info_font.render('Chromosome: ' + str(chromosome), True, TEXT_COLOR)
		# print(game_data[chromosome]["score"])
		# Draw
		screen.fill(BACKGROUND_COLOR)
		game_data[chromosome]["snake"].draw()
		game_data[chromosome]["fruit"].draw()
		screen.blit(generation_number,(10,0))
		screen.blit(chromosome_index,(10,20))
		screen.blit(score_text,(450,550))
		pygame.display.flip()
		# print("DONE", game_data[chromosome]["score"])

	gen.parents_selection()


pygame.quit()