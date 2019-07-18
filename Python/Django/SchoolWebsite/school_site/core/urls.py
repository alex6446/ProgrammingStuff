from django.urls import path
from . import views
from .views import (
	news_detail, 
	event_detail,
	# teacher_detail,
    gallery_detail,
    achievement_detail, 
	#NewsListView,
	)

urlpatterns = [
    path('', views.home, name='core-home'),
    path('about/', views.about, name='core-about'),
    path('about/teachers-management', views.teachers_management, name='core-about-teachers-management'),
    path('about/teachers-primary', views.teachers_primary, name='core-about-teachers-primary'),
    path('about/teachers-secondary', views.teachers_secondary, name='core-about-teachers-secondary'),
    path('gallery/', views.gallery, name='core-gallery'),
    path('schedule/', views.schedule, name='core-schedule'),
    path('students/', views.students, name='core-students'),
    path('achievements/', views.achievements, name='core-achievements'),
    #path('news/', NewsListView.as_view(), name='core-news'),
    path('news/', views.news, name='core-news'),
    path('contacts/', views.contacts, name='core-contacts'),
    path('post/<int:pk>/', news_detail.as_view(), name='news-detail'),
    path('event/<int:pk>/', event_detail.as_view(), name='event-detail'),
    # path('teacher/<int:pk>/', teacher_detail.as_view(), name='teacher-detail'),
    path('gallery/<int:pk>/', gallery_detail.as_view(), name='gallery-detail'),
    path('achievement/<int:pk>/', achievement_detail.as_view(), name='achievement-detail'),
]