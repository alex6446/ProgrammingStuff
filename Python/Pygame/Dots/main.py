import pygame
import math

WIDTH = 1280
HEIGHT = 1024
FPS = 15

BACKGROUND_COLOR = (0, 0, 0)
scale = 0.1
numbers = 10000000
prime_numbers = [2, 3]

def get_position(number):
	x = number*math.sin(number)*scale
	y = number*math.cos(number)*scale
	position = (int(x + WIDTH/2), int(y + HEIGHT/2))
	return position

# for num in range(2, numbers):
# 	if num > 1: 
# 		for i in range(2, num//2+1):   
# 			if (num % i) == 0: 
# 				break
# 		else: 
# 			prime_numbers.append(num)

for num in range(5, numbers):
	i =0
	while prime_numbers[i]<=math.sqrt(num):
		if num % prime_numbers[i]  == 0: 
			break
		i+=1
	else: 
		prime_numbers.append(num)

sum = 0
for i in prime_numbers:
	sum += 1
print(prime_numbers[len(prime_numbers)-1])

print(sum)

pygame.init()
screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
pygame.display.set_caption("Numbers visualise")
clock = pygame.time.Clock()

running = True
while running:
	clock.tick(FPS)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False
		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				running = False
		if event.type == pygame.MOUSEBUTTONDOWN:
		    if event.button == 4:
		        scale *= 1.3
		    elif event.button == 5:
		        scale /= 1.3


	screen.fill(BACKGROUND_COLOR)
	for i in prime_numbers:
		pygame.draw.circle(screen, (0, 128, 128), get_position(i), 0)
	pygame.display.flip()

pygame.quit()

