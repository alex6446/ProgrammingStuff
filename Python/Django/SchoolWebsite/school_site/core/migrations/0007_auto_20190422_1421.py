# Generated by Django 2.2 on 2019-04-22 11:21

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('core', '0006_auto_20190422_1413'),
    ]

    operations = [
        migrations.CreateModel(
            name='Event',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=150)),
                ('image', models.ImageField(default='event_pics/default.png', upload_to='event_pics')),
                ('content', models.TextField()),
                ('date_posted', models.DateTimeField(default=django.utils.timezone.now)),
            ],
        ),
        migrations.DeleteModel(
            name='Announcement',
        ),
        migrations.AlterField(
            model_name='about',
            name='image',
            field=models.ImageField(default='about_pics/default.png', upload_to='about_pics'),
        ),
    ]
