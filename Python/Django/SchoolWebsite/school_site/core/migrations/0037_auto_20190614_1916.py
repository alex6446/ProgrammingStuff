# Generated by Django 2.2.2 on 2019-06-14 16:16

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('core', '0036_achievement_image'),
    ]

    operations = [
        migrations.AlterField(
            model_name='achievement',
            name='image',
            field=models.ImageField(blank=True, default=None, upload_to='achievement_pics'),
        ),
    ]
