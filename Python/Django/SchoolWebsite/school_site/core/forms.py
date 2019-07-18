from django import forms
from django.core import validators

class ContactForm(forms.Form):
	name = forms.CharField(max_length=150, widget=forms.TextInput(attrs={'placeholder': 'Name'}))
	email = forms.EmailField(widget=forms.TextInput(attrs={'placeholder': 'Email', 'type': 'email'}))
	message = forms.CharField(widget=forms.Textarea(attrs={'placeholder': 'Message'}))


