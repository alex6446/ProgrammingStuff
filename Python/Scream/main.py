import pydub as pd
import ffmpeg
import pygame
import time


pygame.mixer.init()
pygame.mixer.music.load("anton_chihnul.mp3")
for i in range(10):
	pygame.mixer.music.play()
	time.sleep(1)
