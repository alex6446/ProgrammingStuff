import pygame
import random

WIDTH = 450
HEIGHT = 650
FPS = 60

BACKGROUND_COLOR = (113, 197, 207)

class Game():
	def __init__(self):
		self.score_max = 0
		self.setup()

	def setup(self):
		self.position = [int(WIDTH/2), int(HEIGHT/2)]
		self.jump = False
		self.x = 0
		self.start = False
		self.dead = False
		self.on_floor = False
		self.pipes = []
		self.score = 0
		self.score_number = font.render('Score: ' + str(self.score), True, (0, 0, 0))
		self.score_max_number = font.render('Max: ' + str(self.score_max), True, (0, 0, 0))

	def gen_rand_pos(self):
		pos = random.randint(pipe_height+100, HEIGHT-(floor_height+100))
		return pos

	def make_jump(self):
		if not self.dead:
			self.start = True
			self.jump = True
			self.x = -3.1 #3.5 #-2.5

	def reset(self):
		self.setup()

	def update(self):
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



pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Numbers visualise")
clock = pygame.time.Clock()
font = pygame.font.Font('Roboto-Regular.ttf', 25)

r = 15
speed = 2
floor_height = 60
pipe_width = 70
pipe_height = 130
pipe_distance = 130

DaGame = Game()

while True:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				DaGame.reset()
			if event.key == pygame.K_SPACE:
				DaGame.make_jump()

	# update #####################

	DaGame.update()

	# draw #######################

	screen.fill(BACKGROUND_COLOR)
	DaGame.draw()
	pygame.draw.rect(screen, (139,69,19), (0, HEIGHT-floor_height, WIDTH, floor_height))
	pygame.display.flip()




