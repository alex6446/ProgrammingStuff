import pandas
from django.shortcuts import render, redirect
from django.contrib import messages
from django.core.paginator import Paginator
from django.core.mail import send_mail
from django.views.generic import ListView, DetailView
from django.conf import settings
from .models import (
 	About,
	Event,
	News,
	Teacher,
	Timetable,
	Schedule,
	Student,
	Contact,
	Gallery,
	GalleryImage,
	Achievement,
	Background,
	)
from .forms import ContactForm
import sendgrid
import os
#from sendgrid.helpers.mail import *

def home(request):
	news_list = News.objects.all().order_by('-date_posted')
	paginator = Paginator(news_list, 3)
	page = request.GET.get('page')
	pNews = paginator.get_page(page)

	event_list = Event.objects.all().order_by('-date_posted')
	paginator = Paginator(event_list, 2)
	pEvent = paginator.get_page(page)

	background_list = Background.objects.filter(page='home')
	try:
		background_home = background_list[0].image
	except:
		background_home = None

	context = {
		'events': pEvent,
		# 'events': None,
		'about': About.objects.filter(post_type="welcome"),
		'news': pNews,
		'title': 'Головна',
		'changebg': True,
		'background_home': background_home,
	}
	return render(request, 'core/home.html', context)

def about(request):
	background_list = Background.objects.filter(page='about')
	try:
		background_about = background_list[0].image
	except:
		background_about = None

	# about = About.objects.all()

	# anchor = quote_plus(title)

	context = {
		'title': 'Школа',
		'about_welcome': About.objects.filter(post_type="welcome"),
		'about_info': About.objects.filter(post_type="info"),
		'teachers': Teacher.objects.all(),
		'background_about': background_about,
		# 'changebg': True,
	}
	return render(request, 'core/about.html', context)

def teachers_management(request):
	context = {
		'title': 'Вчителі',
		'teachers': Teacher.objects.filter(teacher_type='management'),
		'changebg': True,
	}
	return render(request, 'core/teachers_management.html', context)

def teachers_primary(request):
	context = {
		'title': 'Вчителі',
		'teachers': Teacher.objects.filter(teacher_type='primary'),
		'changebg': True,
	}
	return render(request, 'core/teachers_primary.html', context)

def teachers_secondary(request):
	context = {
		'title': 'Вчителі',
		'teachers': Teacher.objects.filter(teacher_type='secondary'),
		'changebg': True,
	}
	return render(request, 'core/teachers_secondary.html', context)

def gallery(request):
	background_list = Background.objects.filter(page='gallery')
	try:
		background_gallery = background_list[0].image
	except:
		background_gallery = None

	gallery_list = Gallery.objects.all().order_by('-date_posted')
	paginator = Paginator(gallery_list, 2)
	page = request.GET.get('page')
	pGallery = paginator.get_page(page)
	context = {
		'title': 'Галерея',
		'gallery': pGallery,
		'background_gallery': background_gallery,
		'changebg': True,
	}
	return render(request, 'core/gallery.html', context)

def schedule(request):
	background_list = Background.objects.filter(page='schedule')
	try:
		background_schedule = background_list[0].image
	except:
		background_schedule = None

	time_general_summer = Timetable.objects.filter(table_type='general_summer')
	time_general_winter = Timetable.objects.filter(table_type='general_winter')
	time_extra = Timetable.objects.filter(table_type='extra')

	lessons_general = Schedule.objects.filter(table_type='general')
	lessons_extra = Schedule.objects.filter(table_type='extra')

	context = {
		'title': 'Розклад',
		#'tables': HtmlScheduleTables,
		'time_general_summer': time_general_summer,
		'time_general_winter': time_general_winter,
		'time_extra': time_extra,
		'lessons_general': lessons_general,
		'lessons_extra': lessons_extra,		
		'background_schedule': background_schedule,
		# 'changebg': True,
	}
	return render(request, 'core/schedule.html', context)

def students(request):
	background_list = Background.objects.filter(page='students')
	try:
		background_students = background_list[0].image
	except:
		background_students = None

	context = {
		'title': 'Учням',
		'student_articles': Student.objects.all(),
		'background_students': background_students,
	}
	return render(request, 'core/students.html', context)

def achievements(request):
	background_list = Background.objects.filter(page='achievements')
	try:
		background_achievements = background_list[0].image
	except:
		background_achievements = None

	achievement_list = Achievement.objects.all().order_by('-date_posted')
	paginator = Paginator(achievement_list, 2)
	page = request.GET.get('page')
	pAchievements = paginator.get_page(page)

	context = {
		'title': 'Досягнення',
		'achievements': pAchievements,
		'background_achievements': background_achievements,
	}
	return render(request, 'core/achievements.html', context)

def news(request):
	background_list = Background.objects.filter(page='news')
	try:
		background_news = background_list[0].image
	except:
		background_news = None

	news_list = News.objects.all().order_by('-date_posted')
	paginator = Paginator(news_list, 4)
	page = request.GET.get('page')
	pNews = paginator.get_page(page)

	context = {
		'title': 'Новини',
		'events': Event.objects.all().order_by('-date_posted'),
		# 'events': None,
		'news': pNews,
		'background_news': background_news,
		'changebg': True,
	}
	return render(request, 'core/news.html', context)

def contacts(request):
	if request.method == 'POST':
		form = ContactForm(request.POST)
		if form.is_valid():
			# send email
			sender_name = form.cleaned_data['name']
			sender_email = form.cleaned_data['email']

			subject = "Сайт ЗОШ №2"
			message = "{0} отправил(а) вам сообщение:\n\n{1}".format(
				sender_name,
				form.cleaned_data['message'])
			sg = sendgrid.SendGridAPIClient(api_key=os.environ.get('SENDGRID_API_KEY'))
			data = {
				"personalizations": [{
					"to": [{
						"email": settings.EMAIL_HOST_USER
						}],
					"subject": subject
			    }],
				"from": {
					"email": sender_email
				},
				"content": [{
					"type": "text/plain",
					"value": message
				}]
				}
			response = sg.client.mail.send.post(request_body=data)

			messages.success(request, f'Повідомлення відправлено!')
			return redirect('core-contacts')
		else:
			messages.error(request, f'Під час відправлення повідомлення виникла помилка.')
	else:
		form = ContactForm()

	context = {
		'title': 'Контакти',
		'form': form,
		'info': Contact.objects.all(),
		'background_contacts': True,
	}
	return render(request, 'core/contacts.html', context)

class news_detail(DetailView):
	model = News

	def get_object(self):
		object = super(DetailView, self).get_object()
		self.title = object.title
		return object

	def get_context_data(self, **kwargs):
		context = super().get_context_data(**kwargs)
		context['title'] = self.title
		return context
	
class event_detail(DetailView):
	model = Event

	def get_object(self):
		object = super(DetailView, self).get_object()
		self.title = object.title
		return object

	def get_context_data(self, **kwargs):
		context = super().get_context_data(**kwargs)
		context['title'] = self.title
		return context

# class teacher_detail(DetailView):
# 	model = Teacher

# 	def get_object(self):
# 		object = super(DetailView, self).get_object()
# 		self.title = object.name
# 		return object

# 	def get_context_data(self, **kwargs):
# 		context = super().get_context_data(**kwargs)
# 		context['title'] = self.title
# 		return context

class gallery_detail(DetailView):
	model = Gallery

	def get_object(self):
		object = super(DetailView, self).get_object()
		self.title = object.title
		return object

	def get_context_data(self, **kwargs):
		context = super().get_context_data(**kwargs)
		context['title'] = self.title
		# context['test'] = "BINGO"
		return context

class achievement_detail(DetailView):
	model = Achievement

	def get_object(self):
		object = super(DetailView, self).get_object()
		self.title = object.title
		return object

	def get_context_data(self, **kwargs):
		context = super().get_context_data(**kwargs)
		context['title'] = self.title
		return context
