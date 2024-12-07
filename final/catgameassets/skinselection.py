import pygame
import sys
import random
from pygame.locals import *


class SkinSelection:
    # Cat skin
    cat_skin = {'1': 'cat1.png', '2': 'cat2.png', '3': 'cat3.png'}


    @classmethod
    def skin_selection(cls):
        selected_skin = None
        while selected_skin is None:
            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == KEYDOWN:
                    if event.key == K_1:
                        selected_skin = '1'
                    elif event.key == K_2:
                        selected_skin = '2'
                    elif event.key == K_3:
                        selected_skin = '3'
        return selected_skin


