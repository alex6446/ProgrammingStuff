import pygame
import math

WIDTH = 900
HEIGHT = 800
FPS = 60

BACKGROUND_COLOR = (5, 5, 5)

k = 1.61803398875
squares = []
sectors = []
side = 5
number = 12
state = 3
position = [550, 350]

pygame.init()
screen = pygame.display.set_mode((0, 0))
pygame.display.set_caption("Numbers visualise")
clock = pygame.time.Clock()

for i in range(number):
	if state == 0:
		position = [position[0] + side, position[1] - side*(k-1)]
		sectors.append([[position[0]-side*k, position[1]-side*k, side*k*2, side*k*2], 
			math.radians(270), math.radians(360)])
	elif state == 1:
		position = [position[0] - side*(k-1), position[1] - side*k]
		sectors.append([[position[0]-side*k, position[1], side*k*2, side*k*2], 
			math.radians(0), math.radians(90)])
	elif state == 2:
		position = [position[0] - side*k, position[1]]
		sectors.append([[position[0], position[1], side*k*2, side*k*2], 
			math.radians(90), math.radians(180)])
	elif state == 3:
		position =[position[0], position[1] + side]
		sectors.append([[position[0], position[1]-side*k, side*k*2, side*k*2], 
			math.radians(180), math.radians(270)])
	side *= k
	squares.append(( position[0], position[1], side+1, side+1 ))
	state = (state + 1) % 4

while True:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				pygame.quit()

	screen.fill(BACKGROUND_COLOR)
	for i in squares:
		pygame.draw.rect(screen, (250, 250, 250), i, 1)
	for i in sectors:
		pygame.draw.arc(screen, (250, 250, 250), i[0], i[1], i[2], 1)
	#pygame.draw.circle(screen, (139, 34, 34), position, r)
	pygame.display.flip()

