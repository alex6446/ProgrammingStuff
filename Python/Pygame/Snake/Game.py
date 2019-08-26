import pygame
import random

WIDTH = 600
HEIGHT = 600
FPS = 5

BACKGROUND_COLOR = (20,26,27)
FRUIT_COLOR = (237,67,55)
HEAD_COLOR = (0,137,123)
BODY_COLOR = (0,86,77)
SCORE_COLOR = (245, 245, 245)
# BLACK = (20,26,27)
# LIGHT = (245, 245, 245)
# DARK = (54,54,54)
# GREY = (150,150,150)
# TEAL_DARK = (0,86,77)
# TEAL_LIGHT = (0,137,123)


class Snake():
	def __init__(self, screen):
		global WIDTH, HEIGHT
		self.screen = screen
		self.body = [[WIDTH / 2, HEIGHT / 4], [300, 135]] #, [300, 130], [300, 120], [300, 110], [300, 100], [300, 90], [300, 80], [300, 70], [300, 60], [300, 50], [300, 40], [300, 30], [300, 20], [300, 10], [300, 0], [290, 0], [280, 0], [270, 0], [260, 0], [250, 0], [240, 0], [230, 0], [220, 0], [210, 0], [200, 0], [190, 0], [180, 0]] # Position X, Y
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
		if side == "DOWN" and not direction == "UP":
			self.direction = "DOWN"
		if side == "UP" and not direction == "DOWN":
			self.direction = "UP"
		if side == "RIGHT" and not direction == "LEFT":
			self.direction = "RIGHT"
		if side == "LEFT" and not direction == "RIGHT":
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


def Border(screen):
	global WIDTH, HEIGHT
	size = 1
	# pygame.draw.rect(screen, SCORE_COLOR, (0, 0, size, HEIGHT))
	# pygame.draw.rect(screen, SCORE_COLOR, (0, 0, WIDTH, size))
	# pygame.draw.rect(screen, SCORE_COLOR, (0, HEIGHT-size, WIDTH, size))
	# pygame.draw.rect(screen, SCORE_COLOR, (WIDTH-size, 0, size, HEIGHT))


pygame.init()
pygame.font.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake Game")
clock = pygame.time.Clock()
font = pygame.font.Font('Roboto-Regular.ttf', 25) #SysFont('Comic Sans MS', 30)

snake = Snake(screen)
fruit = Fruit(screen, snake.body)
score = 2

running = True
while running:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_DOWN:
				snake.turn("DOWN")
			if event.key == pygame.K_UP:
				snake.turn("UP")
			if event.key == pygame.K_RIGHT:
				snake.turn("RIGHT")
			if event.key == pygame.K_LEFT:
				snake.turn("LEFT")
	
	# Update
	if snake.update(fruit.position) == "eaten":
		fruit.generate(snake.body)
		score += 1
	if not snake.check():
		break
	score_text = font.render('Score: ' + str(score), True, SCORE_COLOR)

	# Draw
	screen.fill(BACKGROUND_COLOR)
	Border(screen)
	snake.draw()
	fruit.draw()
	screen.blit(score_text,(450,550))
	pygame.display.flip()


pygame.quit()
