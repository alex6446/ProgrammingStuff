from translitua import translit
from transliterate import translit as translit_ru
from urllib.parse import quote_plus
from django import template

register = template.Library()

@register.filter
def conv_link(value):
	anchor = translit(value)
	anchor = translit_ru(anchor, 'ru', reversed=True)
	for i in anchor:
		if i == ' ':
			anchor = anchor.replace(i, '-')
		elif i == '\'':
			anchor = anchor.replace(i, '')
	anchor = quote_plus(anchor)
	anchor = anchor.lower()
	return anchor

