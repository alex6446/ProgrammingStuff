import math

def form_layer(data):
	right = left = up = down = 0
	if data["snake"].direction == "DOWN":
		down = 1
	elif data["snake"].direction == "UP":
		up = 1
	elif data["snake"].direction == "RIGHT":
		right = 1
	elif data["snake"].direction == "LEFT":
		left = 1
	
	head = data["snake"].body[0]
	head_x = head[0]
	head_y = head[1]
	size = data["snake"].size
	fruit_x = data["fruit"].position[0]
	fruit_y = data["fruit"].position[1]
	fruit_found = False
	HEIGHT = data["snake"].HEIGHT
	WIDTH = data["snake"].WIDTH

	fruit_down = 0
	fruit_up = 0
	fruit_right = 0
	fruit_left = 0

	# if fruit_x == head_x:
	# 	if fruit_y > head_y:
	# 		fruit_down = fruit_y - head_y
	# 		fruit_found = True
	# 	elif fruit_y < head_y:
	# 		fruit_up = head_y - fruit_y
	# 		fruit_found = True
	# elif fruit_y == head_y:
	# 	if fruit_x > head_x:
	# 		fruit_right = fruit_y - head_y
	# 		fruit_found = True
	# 	elif fruit_y < head_y:
	# 		fruit_left = head_y - fruit_y
	# 		fruit_found = True

	if fruit_x > head_x:
		fruit_right = fruit_x - head_x
		fruit_left -= fruit_right
	elif fruit_x <= head_x:
		fruit_left = head_x - fruit_x
		fruit_right -= fruit_left

	if fruit_y > head_y:
		fruit_down = fruit_y - head_y
		fruit_up -= fruit_down
	elif fruit_y <= head_y:
		fruit_up = head_y - fruit_y
		fruit_down -= fruit_up

	wall_down = HEIGHT - head_y
	wall_up = head_y
	wall_right = WIDTH - head_x
	wall_left = head_x

	body_down = 0
	body_up = 0
	body_right = 0
	body_left = 0


	for y in range(int(head_y + size), HEIGHT - size + 1, size):
		cords = [head_x, y]
		if cords in data["snake"].body:
			body_down = y - head_y
			break

	for y in range(int(head_y - size), -1, -size):
		cords = [head_x, y]
		if cords in data["snake"].body:
			body_up = head_y - y
			break

	for x in range(int(head_x + size), WIDTH - size + 1, size):
		cords = [x, head_y]
		if cords in data["snake"].body:
			body_right = x - head_x
			break

	for x in range(int(head_x - size), -1, -size):
		cords = [x, head_y]
		if cords in data["snake"].body:
			body_left = head_x - x
			break


	fruit_down_right = 0
	fruit_right_up = 0
	fruit_up_left = 0
	fruit_left_down = 0

	if not fruit_found:
		for cord in range(size, int(min(wall_down, wall_right)) + 1, size):
			if head_x + cord == fruit_x and head_y + cord == fruit_y:
				fruit_down_right = math.sqrt(2)*cord
				fruit_found = True

	if not fruit_found:
		for cord in range(size, int(min(wall_right, wall_up)) + 1, size):
			if head_x + cord == fruit_x and head_y - cord == fruit_y:
				fruit_right_up = math.sqrt(2)*cord
				fruit_found = True

	if not fruit_found:
		for cord in range(size, int(min(wall_up, wall_left)) + 1, size):
			if head_x - cord == fruit_x and head_y - cord == fruit_y:
				fruit_up_left = math.sqrt(2)*cord
				fruit_found = True

	if not fruit_found:
		for cord in range(size, int(min(wall_left, wall_down)) + 1, size):
			if head_x - cord == fruit_x and head_y + cord == fruit_y:
				fruit_left_down = math.sqrt(2)*cord
				fruit_found = True


	wall_down_right = math.sqrt(2)*min(wall_down, wall_right)
	wall_right_up = math.sqrt(2)*min(wall_right, wall_up)
	wall_up_left = math.sqrt(2)*min(wall_up, wall_left)
	wall_left_down = math.sqrt(2)*min(wall_left, wall_down)

	body_down_right = 0
	body_right_up = 0
	body_up_left = 0
	body_left_down = 0

	for cord in range(size, int(min(wall_down, wall_right)) + 1, size):
		cords = [head_x + cord, head_y + cord]
		if cords in data["snake"].body:
			body_down_right = math.sqrt(2)*cord
			break

	for cord in range(size, int(min(wall_right, wall_up)) + 1, size):
		cords = [head_x + cord, head_y - cord]
		if cords in data["snake"].body:
			body_right_up = math.sqrt(2)*cord
			break

	for cord in range(size, int(min(wall_up, wall_left)) + 1, size):
		cords = [head_x - cord, head_y - cord]
		if cords in data["snake"].body:
			body_up_left = math.sqrt(2)*cord
			break

	for cord in range(size, int(min(wall_left, wall_down)) + 1, size):
		cords = [head_x - cord, head_y + cord]
		if cords in data["snake"].body:
			body_left_down = math.sqrt(2)*cord
			break

	# if down:
	# 	front_fruit = fruit_down/size
	# 	front_wall = wall_down/size
	# 	front_body = body_down/size
	
	# 	back_fruit = fruit_up/size
	# 	back_wall = wall_up/size
	# 	back_body = body_up/size

	# 	left_fruit = fruit_right/size
	# 	left_wall = wall_right/size
	# 	left_body = body_right/size

	# 	right_fruit = fruit_left/size
	# 	right_wall = wall_left/size
	# 	right_body = body_left/size

	# 	front_left_fruit = fruit_down_right
	# 	front_left_wall = wall_down_right
	# 	front_left_body = body_down_right

	# 	left_back_fruit = fruit_right_up
	# 	left_back_wall = wall_right_up
	# 	left_back_body = body_right_up

	# 	back_right_fruit = fruit_up_left
	# 	back_right_wall = wall_up_left
	# 	back_right_body = body_up_left

	# 	right_front_fruit = fruit_left_down
	# 	right_front_wall = wall_left_down
	# 	right_front_body = body_left_down

	# elif up:
	# 	front_fruit = fruit_up/size
	# 	front_wall = wall_up/size
	# 	front_body = body_up/size
	
	# 	back_fruit = fruit_down/size
	# 	back_wall = wall_down/size
	# 	back_body = body_down/size

	# 	left_fruit = fruit_left/size
	# 	left_wall = wall_left/size
	# 	left_body = body_left/size

	# 	right_fruit = fruit_right/size
	# 	right_wall = wall_right/size
	# 	right_body = body_right/size

	# 	front_left_fruit = fruit_up_left
	# 	front_left_wall = wall_up_left
	# 	front_left_body = body_up_left

	# 	left_back_fruit = fruit_left_down
	# 	left_back_wall = wall_left_down
	# 	left_back_body = body_left_down

	# 	back_right_fruit = fruit_down_right
	# 	back_right_wall = wall_down_right
	# 	back_right_body = body_down_right

	# 	right_front_fruit = fruit_right_up
	# 	right_front_wall = wall_right_up
	# 	right_front_body = body_right_up

	# elif right:
	# 	front_fruit = fruit_right/size
	# 	front_wall = wall_right/size
	# 	front_body = body_right/size
	
	# 	back_fruit = fruit_left/size
	# 	back_wall = wall_left/size
	# 	back_body = body_left/size

	# 	left_fruit = fruit_up/size
	# 	left_wall = wall_up/size
	# 	left_body = body_up/size

	# 	right_fruit = fruit_down/size
	# 	right_wall = wall_down/size
	# 	right_body = body_down/size

	# 	front_left_fruit = fruit_right_up
	# 	front_left_wall = wall_right_up
	# 	front_left_body = body_right_up

	# 	left_back_fruit = fruit_up_left
	# 	left_back_wall = wall_up_left
	# 	left_back_body = body_up_left

	# 	back_right_fruit = fruit_left_down
	# 	back_right_wall = wall_left_down
	# 	back_right_body = body_left_down

	# 	right_front_fruit = fruit_down_right
	# 	right_front_wall = wall_down_right
	# 	right_front_body = body_down_right

	# else: #left
	front_fruit = fruit_left/size
	front_wall = wall_left/size
	front_body = body_left/size

	back_fruit = fruit_right/size
	back_wall = wall_right/size
	back_body = body_right/size

	left_fruit = fruit_down/size
	left_wall = wall_down/size
	left_body = body_down/size

	right_fruit = fruit_up/size
	right_wall = wall_up/size
	right_body = body_up/size

	front_left_fruit = fruit_left_down
	front_left_wall = wall_left_down
	front_left_body = body_left_down

	left_back_fruit = fruit_down_right
	left_back_wall = wall_down_right
	left_back_body = body_down_right

	back_right_fruit = fruit_right_up
	back_right_wall = wall_right_up
	back_right_body = body_right_up

	right_front_fruit = fruit_up_left
	right_front_wall = wall_up_left
	right_front_body = body_up_left






	LAYER = [
			front_fruit, front_wall, front_body,
			back_fruit, back_wall, back_body,
			right_fruit, right_wall, right_body,
			left_fruit, left_wall, left_body,
			front_left_fruit, front_left_wall, front_left_body,
			left_back_fruit, left_back_wall, left_back_body,
			back_right_fruit, back_right_wall, back_right_body,
			right_front_fruit, right_front_wall, right_front_body
			]

	# print(LAYER)

	return LAYER
