import pygame
import random
import os

WIDTH = 450
HEIGHT = 650
FPS = 60

K = HEIGHT/650

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

game_folder = os.path.dirname(__file__)
img_folder = os.path.join(game_folder, "images")
font_folder = os.path.join(game_folder, "fonts")

class Floor(pygame.sprite.Sprite):
	def __init__(self):
		pygame.sprite.Sprite.__init__(self)
		self.image = pygame.image.load(os.path.join(img_folder, "ahegao_all.png"))
		self.image = pygame.transform.scale(self.image, 
		(int(self.image.get_size()[0]*1.5), int(self.image.get_size()[1]*1.5)))
		self.rect = self.image.get_rect()
		self.rect.bottomleft = (0, HEIGHT)

	def update(self):
		self.rect.x -= speed

	def draw(self):
		screen.blit(self.image, self.rect)


class Pipe(pygame.sprite.Sprite):
	def __init__(self):
		pygame.sprite.Sprite.__init__(self)
		self.image = pygame.image.load(os.path.join(img_folder, "chlen_long.png"))
		self.image = pygame.transform.scale(self.image, 
		(int(self.image.get_size()[0]), int(self.image.get_size()[1])))
		self.rect = self.image.get_rect()
		self.rect.topleft = [WIDTH, self.get_rand_pos()]
		self.revs = [self.rect[0], self.rect[1], self.rect[2], self.rect[3]]

	def get_rand_pos(self):
		pos = random.randint(int(pipe_height+100), int(HEIGHT-(floor_height+100)))
		return pos

	def update(self):
		self.rect.x -= speed
		self.revs = [self.rect[0], self.rect[1], self.rect[2], self.rect[3]] 
		self.revs[1] -= self.rect[3] + pipe_height

	def draw(self):
		screen.blit(self.image, self.rect)
		screen.blit(pygame.transform.flip(self.image, False, True), self.revs)	


class Bird(pygame.sprite.Sprite):
	def __init__(self):
		pygame.sprite.Sprite.__init__(self)
		self.image = pygame.image.load(os.path.join(img_folder, "flappy_loli_head.png"))
		self.image = pygame.transform.scale(self.image, 
		(int(self.image.get_size()[0]*0.2), int(self.image.get_size()[1]*0.2)))
		self.rect = self.image.get_rect()
		self.rect.bottomleft = (int(WIDTH/2), int(HEIGHT/2))
		self.setup()

	def setup(self):
		self.jumped = False
		self.x = 0
		self.start = False
		self.dead = False
		self.on_floor = False

	def jump(self):
		self.jumped = True
		self.x = -3.1

	def check_collision(self, pipe, dead):
		if (self.rect.bottom-30 > pipe.rect.y and 
			self.rect.right-30 > pipe.rect.x and 
			self.rect.x+30 < pipe.rect.right):
			self.jumped = False
			self.x = 0
			return True
		if (self.rect.y+30 < pipe.rect.y-pipe_height and 
			self.rect.right-30 > pipe.rect.x and 
			self.rect.x+30 < pipe.rect.right):
			self.jumped = False
			self.x = 0
			return True
		return dead

	def reset(self):
		self.rect.bottomleft = (int(WIDTH/2), int(HEIGHT/2))
		self.setup()

	def update(self, dead, start):
		if not self.jumped and not self.on_floor:
			self.rect.y = self.rect.y + int(self.x*self.x/1.6) #1.57
			if self.x < 4.3:
				self.x += 0.18 #18
		elif not dead:
			self.rect.y = self.rect.y - int(self.x*self.x) #1 #*2.5
			self.x += 0.15 #0.2 #0.158 
			if self.x > -1:
				self.jumped = False
				self.x = 0
		if self.rect.bottom >= HEIGHT-floor_height+20:
			self.on_floor = True
			return True, False
		return dead, start

	def draw(self):
		screen.blit(self.image, self.rect)


class Game():
	def __init__(self):
		self.floor = [Floor(), Floor()]
		self.pipes = []
		self.bird = Bird()
		self.setup()

	def setup(self):
		self.start = False
		self.dead = False
		self.background = pygame.image.load(os.path.join(img_folder, "flappy_background.jpg"))
		self.background = pygame.transform.scale(self.background, 
		(int(self.background.get_size()[0]*0.7), int(self.background.get_size()[1]*0.7)))
		self.floor[1].rect.x += self.floor[0].rect.right
		global pipe_width, pipe_height, pipe_distance, floor_height, speed
		pipe_height = 130
		pipe_distance = 130
		floor_height = self.floor[0].image.get_size()[1]
		self.pipes.append(Pipe())
		pipe_width = self.pipes[0].image.get_size()[0] 
		speed = 2
		self.score = 0
		self.score_max = self.score
		self.score_number = font.render('Score: ' + str(self.score), True, (0, 0, 0))
		self.score_max_number = font.render('Max: ' + str(self.score_max), True, (0, 0, 0))

	def update(self):
		if self.start:
			self.dead, self.start = self.bird.update(self.dead, self.start)

			if not self.dead:
				for i in self.floor:
					i.update()
				if self.floor[0].rect.right < 0:
					(self.floor[0].rect.x, self.floor[1].rect.x) = (self.floor[1].rect.x, 
						self.floor[1].rect.right)

				if self.pipes[0].rect.right <= 0:
					self.pipes.pop(0)
				if self.pipes[-1].rect.right + pipe_distance <= WIDTH:
					self.pipes.append(Pipe())
				for pipe in self.pipes:
					if (self.bird.rect.x + self.bird.rect[2]/2 < pipe.rect.right and 
					    self.bird.rect.x + self.bird.rect[2]/2 > pipe.rect.right - speed):
						self.score += 1
					pipe.update()
				for pipe in self.pipes:
					self.dead = self.bird.check_collision(pipe, self.dead)
				self.score_number = font.render('Score: ' + str(self.score), True, (0, 0, 0))
			if self.score > self.score_max:
				self.score_max = self.score
				self.score_max_number = font.render('Max: ' + str(self.score_max), True, (0, 0, 0))

	def jump(self):
		if not self.dead:
			self.start = True
			self.bird.jump()

	def reset(self):
		self.bird.reset()
		self.start = False
		self.dead = False
		self.pipes.clear()
		self.pipes.append(Pipe())
		self.floor = [Floor(), Floor()]
		self.floor[1].rect.x += self.floor[0].rect.right
		self.score = 0
		self.score_number = font.render('Score: ' + str(self.score), True, (0, 0, 0))

	def draw(self):
		screen.blit(self.background, self.background.get_rect())
		for i in self.pipes:
			i.draw()
		self.bird.draw()
		for i in self.floor:
			i.draw()
		screen.blit(self.score_number,(10, 10))
		screen.blit(self.score_max_number,(300, 10))


pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Flappy Porn")
clock = pygame.time.Clock()
font = pygame.font.Font(os.path.join(font_folder, 'KGSummerSunshineBlackout.ttf'), 24)

FlappyPorn = Game()

while True:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				FlappyPorn.reset()
			if event.key == pygame.K_SPACE:
				FlappyPorn.jump()

	FlappyPorn.update()

	screen.fill(BLACK)
	FlappyPorn.draw()
	pygame.display.flip()


