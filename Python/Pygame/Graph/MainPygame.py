import pygame
import math

pygame.init()

win = pygame.display.set_mode((800, 800))
pygame.display.set_caption("First Game")


run = True
while run:
	pygame.time.delay(100)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False

	win.fill((238, 238, 238))
	pygame.draw.rect(win, (105, 105, 105), (0, 400, 800, 2))
	pygame.draw.rect(win, (105, 105, 105), (400, 0, 2, 800))

	x = -400
	x_prev = -400
	y_prev = 6/(x+3) + 3
	while x <= 400:
		try:
			y = 6/(x+3) + 3
			pygame.draw.rect(win, (255, 0, 0), (25*x+400, 800 - (25*y2+400), 1, 1))
		except:
			pass
		x += 0.01


	pygame.display.update()
