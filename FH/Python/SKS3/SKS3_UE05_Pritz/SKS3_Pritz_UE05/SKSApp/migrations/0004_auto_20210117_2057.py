# Generated by Django 3.1.4 on 2021-01-17 19:57

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('SKSApp', '0003_auto_20210117_1047'),
    ]

    operations = [
        migrations.AddField(
            model_name='scriptlangsadd',
            name='field',
            field=models.TextField(default=''),
        ),
        migrations.AlterField(
            model_name='scriptlangs',
            name='name',
            field=models.CharField(max_length=50),
        ),
        migrations.AlterField(
            model_name='scriptlangsadd',
            name='info',
            field=models.TextField(default=''),
        ),
    ]
