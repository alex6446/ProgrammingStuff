from translitua import translit
from transliterate import translit as translit_ru
from urllib.parse import quote_plus
from django import template

from django.template.context_processors import request
from urllib.parse import quote_plus
from .models import (
 	About,
 	Student,
 	Achievement,
 	)

def menu(request):

	context = {
		'about_anchors': About.objects.filter(post_type="info"),
		'student_anchors': Student.objects.all(),
		'achievement_anchors': Achievement.objects.all(),
	}
	return context


