from datetime import datetime

birth = input()
current = input()

birth_date = datetime.strptime(birth, "%d.%m")
current_date = datetime.strptime(current, "%d.%m.%Y")
birth_full = datetime(current_date.year, birth_date.month, birth_date.day)
birth_full_next = datetime(current_date.year+1, birth_date.month, birth_date.day)

if (birth_full - current_date).days >= 0:
	print((birth_full - current_date).days)
else:
	print((birth_full_next - current_date).days)
