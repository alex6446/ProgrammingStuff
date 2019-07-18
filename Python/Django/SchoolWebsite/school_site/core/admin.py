from django.contrib import admin
from django.conf import settings
from django.db import models
from tinymce.widgets import TinyMCE
import os
from .models import (
	News,
	About,
	Event,
	Teacher,
	Timetable,
	Schedule,
	Student,
	Contact,
	Gallery,
	GalleryImage,
	Achievement,
	Background,
	AttachedFileNews,
	AttachedFileAbout,
	AttachedFileEvent,
	AttachedFileTeacher,
	AttachedFileStudent,
	AttachedFileAchievement,
	)


class CustomAdmin(admin.ModelAdmin):
	formfield_overrides = {
		models.TextField: {'widget': TinyMCE()},
		}

class GalleryImageInline(admin.TabularInline):
	model = GalleryImage
	extra = 1

class GalleryAdmin(CustomAdmin):
	inlines = [ GalleryImageInline, ]

class AttachedFileNewsInline(admin.TabularInline):
	model = AttachedFileNews
	extra = 1

class AttachedFileNewsAdmin(CustomAdmin):
	inlines = [ AttachedFileNewsInline, ]

class AttachedFileAboutInline(admin.TabularInline):
	model = AttachedFileAbout
	extra = 1

class AttachedFileAboutAdmin(CustomAdmin):
	inlines = [ AttachedFileAboutInline, ]

class AttachedFileEventInline(admin.TabularInline):
	model = AttachedFileEvent
	extra = 1

class AttachedFileEventAdmin(CustomAdmin):
	inlines = [ AttachedFileEventInline, ]

class AttachedFileTeacherInline(admin.TabularInline):
	model = AttachedFileTeacher
	extra = 1

class AttachedFileTeacherAdmin(CustomAdmin):
	inlines = [ AttachedFileTeacherInline, ]

class AttachedFileStudentInline(admin.TabularInline):
	model = AttachedFileStudent
	extra = 1

class AttachedFileStudentAdmin(CustomAdmin):
	inlines = [ AttachedFileStudentInline, ]

class AttachedFileAchievementInline(admin.TabularInline):
	model = AttachedFileAchievement
	extra = 1

class AttachedFileAchievementAdmin(CustomAdmin):
	inlines = [ AttachedFileAchievementInline, ]



admin.site.register(News, AttachedFileNewsAdmin)
admin.site.register(About, AttachedFileAboutAdmin)
admin.site.register(Event, AttachedFileEventAdmin)
admin.site.register(Teacher, AttachedFileTeacherAdmin)
admin.site.register(Student, AttachedFileStudentAdmin)
admin.site.register(Timetable, CustomAdmin)
admin.site.register(Schedule, CustomAdmin)
admin.site.register(Contact, CustomAdmin)
admin.site.register(Gallery, GalleryAdmin)
admin.site.register(Achievement, AttachedFileAchievementAdmin)
admin.site.register(Background)

