from translitua import translit
from transliterate import translit as translit_ru
from urllib.parse import quote_plus

while True:
	title = input()
	# print(translit(translit(convert), RussianSimple))
	# print(translit(convert, RussianSimple))
	# print(translit_ru(convert, 'ru', reversed=True))
	anchor = translit(title)
	anchor = translit_ru(anchor, 'ru', reversed=True)
	for i in anchor:
		if i == ' ':
			anchor = anchor.replace(i, '-')
		elif i == '\'':
			anchor = anchor.replace(i, '')
	anchor = quote_plus(anchor)
	anchor = anchor.lower()
	
	print(anchor.lower())
	