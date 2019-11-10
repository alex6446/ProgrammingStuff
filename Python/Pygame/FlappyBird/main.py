import pygame
import random

WIDTH = 450
HEIGHT = 650
FPS = 60

BACKGROUND_COLOR = (113, 197, 207)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Numbers visualise")
clock = pygame.time.Clock()
font = pygame.font.Font('Roboto-Regular.ttf', 25)

r = 15
position = [int(WIDTH/2), int(HEIGHT/2)]
jump = False
x = 0
start = False
dead = False
k = 1 #HEIGHT/750
on_floor = False
speed = 2

floor_height = 60

pipe_width = 70
pipe_height = 130
pipe_distance = 130
pipes = []
score = 0
score_max = score
score_number = font.render('Score: ' + str(score), True, (0, 0, 0))
score_max_number = font.render('Max: ' + str(score_max), True, (0, 0, 0))

def gen_rand_pos():
	pos = random.randint(pipe_height+100, HEIGHT-(floor_height+100))
	return pos

while True:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				position = [int(WIDTH/2), int(HEIGHT/2)]
				jump = False
				x = 0
				start = False
				dead = False
				on_floor = False
				score = 0
				score_number = font.render('Score: ' + str(score), True, (0, 0, 0))
				pipes.clear()
			if event.key == pygame.K_SPACE:
				if not dead:
					start = True
					jump = True
					x = -3.1 #3.5 #-2.5

	# update #####################

	if start:
		if not jump and not on_floor:
			position = [position[0], position[1] + int(x*x/1.6*k)] #1.57
			if x < 4.3:
				x += 0.18 #18
		elif not dead:
			position = [position[0], position[1] - int(x*x*k)] #1 #*2.5
			x += 0.15 #0.2 #0.158 
			if x > -1:
				jump = False
				x = 0

		if position[1]+r >= HEIGHT-floor_height:
			on_floor = True
			dead = True
			start = False

		if not dead:
			if not len(pipes):
				pipes.append([WIDTH, gen_rand_pos()])
			else:
				if pipes[0][0]+pipe_width <= 0:
					pipes.pop(0)
				if pipes[-1][0]+pipe_width+pipe_distance <= WIDTH:
					pipes.append([WIDTH, gen_rand_pos()])
			for pipe in pipes:
				if (position[0] < pipe[0] + pipe_width and 
				    position[0] > pipe[0] + pipe_width - speed):
					score += 1
				pipe[0] -= speed	

			for pipe in pipes:
				if (position[1]+r > pipe[1] and 
					position[0]+r > pipe[0] and 
					position[0]-r < pipe[0]+pipe_width):
					dead = True
					jump = False
					x = 0
				if (position[1]-r < pipe[1]-pipe_height and 
					position[0]+r > pipe[0] and 
					position[0]-r < pipe[0]+pipe_width):
					dead = True
					jump = False
					x = 0
			score_number = font.render('Score: ' + str(score), True, (0, 0, 0))
		if score > score_max:
			score_max = score
			score_max_number = font.render('Max: ' + str(score_max), True, (0, 0, 0))

	# draw #######################

	screen.fill(BACKGROUND_COLOR)
	if len(pipes):
		for pipe in pipes:
			pygame.draw.rect(screen, (34, 139, 34), (pipe[0], pipe[1], pipe_width, HEIGHT-pipe[1]))
			pygame.draw.rect(screen, (34, 139, 34), (pipe[0], 0, pipe_width, pipe[1]-pipe_height))
	pygame.draw.rect(screen, (139,69,19), (0, HEIGHT-floor_height, WIDTH, floor_height))
	pygame.draw.circle(screen, (139, 34, 34), position, r)
	screen.blit(score_number,(10, 5))
	screen.blit(score_max_number,(200, 5))
	pygame.display.flip()



# int(x*x/1.5)
# if x < 4:
# 	x += 0.2

# -int(x*x*2)
# if x > -1:
# 	jump = False


