import pydub as pd
import ffmpeg
import pygame
import time


D = pd.AudioSegment.from_wav("Д.wav")
R = pd.AudioSegment.from_wav("Р.wav")
Y = pd.AudioSegment.from_wav("У.wav")
G = pd.AudioSegment.from_wav("Г.wav")

# word = D + R + Y + G
word = D + R + Y + G
word.export("word.wav", format="wav")

pygame.mixer.init()
pygame.mixer.music.load("word.wav")
pygame.mixer.music.play()
time.sleep(1)
