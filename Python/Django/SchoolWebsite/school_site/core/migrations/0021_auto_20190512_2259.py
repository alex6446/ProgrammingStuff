# Generated by Django 2.2 on 2019-05-12 19:59

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('core', '0020_auto_20190512_2254'),
    ]

    operations = [
        migrations.RenameField(
            model_name='attachedfile',
            old_name='teacher_files',
            new_name='teacher',
        ),
    ]
