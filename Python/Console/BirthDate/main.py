from datetime import datetime

def is_high(year):
	if year % 4 == 0:
		if year % 100 == 0:
			if year % 400 == 0:
				return True
		else:
			return True
	return False

def count_days(month, day, high):
	global days_usual
	global days_high
	current_length = day
	for i in range(month-1):
		if not high:
			current_length += days_usual[i]
		else:
			current_length += days_high[i]
	return current_length

birth = input()
current = input()

birth_date = datetime.strptime(birth, "%d.%m")
current_date = datetime.strptime(current, "%d.%m.%Y")

days_usual = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
days_high = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

high = is_high(current_date.year)
next_high = is_high(current_date.year+1)
year_length = 365
if high:
	year_length = 366

current_length = count_days(current_date.month, current_date.day, high)
birth_length = count_days(birth_date.month, birth_date.day, high)
birth_next_length = count_days(birth_date.month, birth_date.day, next_high)

if current_length < birth_length:
	days_left = birth_length - current_length
else:
	days_left = birth_next_length + year_length - current_length

print(days_left)
