from django.db import models
from django.utils import timezone


class News(models.Model):
	title = models.CharField(max_length=300)
	image = models.ImageField(default='news_pics/default.png', upload_to='news_pics')
	content = models.TextField()
	date_posted = models.DateTimeField(default=timezone.now)
	
	def __str__(self):
		return self.title

class About(models.Model):
	welcome = 'welcome'
	info = 'info'
	TYPES = (
		(welcome, "welcome"),
		(info, "info"),
		)
	post_type = models.CharField(max_length=25, choices=TYPES, default=info)
	title = models.CharField(max_length=300)
	image = models.ImageField(default=None, upload_to='about_pics', blank=True)
	content = models.TextField()

	def __str__(self):
		return self.title

class Event(models.Model):
	title = models.CharField(max_length=300)
	image = models.ImageField(blank=True, upload_to='event_pics')
	content = models.TextField()
	date_posted = models.DateTimeField(default=timezone.now)

	def __str__(self):
		return self.title

class Teacher(models.Model):
	management = 'management'
	primary = 'primary'
	secondary = 'secondary'
	TYPES = (
		(management, "management"),
		(primary, 'primary'),
		(secondary, 'secondary'),
		)

	teacher_type = models.CharField(max_length=25, choices=TYPES, default=secondary)
	content = models.TextField(default=None)

	def __str__(self):
		return self.teacher_type

class Timetable(models.Model):
	general_summer = 'general_summer'
	general_winter = 'general_winter'
	extra = 'extra'
	TYPES = (
		(general_summer, "general_summer"),
		(general_winter, "general_winter"),
		(extra, "extra"),
		)
	title = models.CharField(max_length=300)
	table_type = models.CharField(max_length=25, choices=TYPES, default=general_summer)
	table = models.TextField()

	def __str__(self):
		return self.table_type

class Schedule(models.Model):
	general = 'general'
	extra = 'extra'
	TYPES = (
		(general, "general"),
		(extra, "extra"),
		)
	table_type = models.CharField(max_length=25, choices=TYPES, default=general)
	table = models.ImageField(upload_to="schedule_tables")

	def __str__(self):
		return self.table_type

class Student(models.Model):
	title = models.CharField(max_length=300)
	image = models.ImageField(default=None, upload_to='student_pics', blank=True)
	content = models.TextField()

	def __str__(self):
		return self.title

class Achievement(models.Model):
	title = models.CharField(max_length=300)
	image = models.ImageField(default=None, upload_to='achievement_pics', blank=True)
	content = models.TextField()
	date_posted = models.DateTimeField(default=timezone.now)

	def __str__(self):
		return self.title	

class Contact(models.Model):
	title = models.CharField(max_length=300)
	information = models.TextField()

	def __str__(self):
		return self.title

class Gallery(models.Model):
	title = models.CharField(max_length=300)
	description = models.TextField(blank=True)
	date_posted = models.DateTimeField(default=timezone.now)

	def __str__(self):
		return self.title

class Background(models.Model):
	home = 'home'
	about = 'about'
	gallery = 'gallery'
	schedule = 'schedule'
	students = 'students'
	news = 'news'
	achievements = 'achievements'
	PAGES = (
		(home, "home"),
		(about, "about"),
		(gallery, "gallery"),
		(schedule, "schedule"),
		(students, "students"),
		(news, "news"),
		(achievements, "achievements"),
		)
	page = models.CharField(max_length=25, choices=PAGES, default=home)
	image = models.ImageField(upload_to="backgrounds", default=None)

	def __str__(self):
		return self.page

class GalleryImage(models.Model):
	gallery = models.ForeignKey(Gallery, related_name='images', on_delete=models.SET_NULL, null=True)
	image = models.ImageField()
	title = models.CharField(max_length=300, blank=True)

class AttachedFileNews(models.Model):
	file = models.FileField(upload_to="attached_files", blank=True)
	news = models.ForeignKey(News, related_name='news_files', on_delete=models.SET_NULL, null=True)
	name = models.CharField(max_length=300)

class AttachedFileAbout(models.Model):
	file = models.FileField(upload_to="attached_files", blank=True)
	about = models.ForeignKey(About, related_name='about_files', on_delete=models.SET_NULL, null=True)
	name = models.CharField(max_length=300)

class AttachedFileEvent(models.Model):
	file = models.FileField(upload_to="attached_files", blank=True)
	event = models.ForeignKey(Event, related_name='event_files', on_delete=models.SET_NULL, null=True)
	name = models.CharField(max_length=300)

class AttachedFileTeacher(models.Model):
	file = models.FileField(upload_to="attached_files", blank=True)
	teacher = models.ForeignKey(Teacher, related_name='teacher_files', on_delete=models.SET_NULL, null=True)
	name = models.CharField(max_length=300)

class AttachedFileStudent(models.Model):
	file = models.FileField(upload_to="attached_files", blank=True)
	student = models.ForeignKey(Student, related_name='student_files', on_delete=models.SET_NULL, null=True)
	name = models.CharField(max_length=300)

class AttachedFileAchievement(models.Model):
	file = models.FileField(upload_to="attached_files", blank=True)
	achievement = models.ForeignKey(Achievement, related_name='achievement_files', on_delete=models.SET_NULL, null=True)
	name = models.CharField(max_length=300)

