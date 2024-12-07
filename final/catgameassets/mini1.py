import pygame
import sys
import random
from pygame.locals import *


class MiniGame1:
    def __init__(self, window_surface,selected_skin):
        self.WindowSurface = window_surface
        self.mainClock = pygame.time.Clock()
        self.WINDOWWIDTH = 500
        self.WINDOWHEIGHT = 500
        pygame.display.set_caption("Go get 'em kitty! MiniGame1")
       
        # Load background image
        self.background = pygame.image.load('./art/ocean.png')
        self.background = pygame.transform.scale(self.background, (self.WINDOWWIDTH, self.WINDOWHEIGHT))


        self.BLACK = (0, 0, 0)
        self.WHITE = (255, 255, 255)


        self.numberFood = 12
        self.foodCounter = 0
        self.NEWFOOD = 150
        self.FOODSIZE = 20


        self.player = pygame.Rect(300, 100, 50, 50)
        self.playerImage = pygame.image.load(selected_skin + '.png')
        self.playerStretchedImage = pygame.transform.scale(self.playerImage, (50, 40))
        self.foodImage = pygame.image.load('fish.png')


        self.foods = []
        for _ in range(self.numberFood):
            self.foods.append(pygame.Rect(random.randint(0, self.WINDOWWIDTH - self.FOODSIZE),
                                           random.randint(0, self.WINDOWHEIGHT - self.FOODSIZE),
                                           self.FOODSIZE, self.FOODSIZE))


        self.moveLeft = False
        self.moveRight = False
        self.moveUp = False
        self.moveDown = False
        self.MOVESPEED = 4
        self.score = 0
        self.score_increment = 1

## NEW CODE - trying to fix the loop
        #self.game_over = False


        self.font = pygame.font.SysFont(None, 36)


    def handle_events(self):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_LEFT or event.key == K_a:
                    self.moveRight = False
                    self.moveLeft = True
                if event.key == K_RIGHT or event.key == K_d:
                    self.moveRight = True
                    self.moveLeft = False
                if event.key == K_UP or event.key == K_w:
                    self.moveDown = False
                    self.moveUp = True
                if event.key == K_DOWN or event.key == K_s:
                    self.moveDown = True
                    self.moveUp = False
            if event.type == KEYUP:
                if event.key == K_LEFT or event.key == K_a:
                    self.moveLeft = False
                if event.key == K_RIGHT or event.key == K_d:
                    self.moveRight = False
                if event.key == K_UP or event.key == K_w:
                    self.moveUp = False
                if event.key == K_DOWN or event.key == K_s:
                    self.moveDown = False
                if event.key == K_ESCAPE:
                    pygame.quit()
                    sys.exit()
                if event.key == K_x:
                    self.player.top = random.randint(0, self.WINDOWHEIGHT - self.player.height)
                    self.player.left = random.randint(0, self.WINDOWHEIGHT - self.player.width)
                if event.key == K_m:
                    if pygame.mixer.music.get_busy():
                        pygame.mixer.music.stop()
                    else:
                        pygame.mixer.music.play(-1, 0.0)


            if event.type == MOUSEBUTTONUP:
                self.foods.append(pygame.Rect(event.pos[0], event.pos[1], self.FOODSIZE, self.FOODSIZE))


    def update(self):
        self.foodCounter += 3
        if self.foodCounter >= self.NEWFOOD:
            self.foodCounter = 0
            self.foods.append(pygame.Rect(random.randint(0, self.WINDOWWIDTH - self.FOODSIZE),
                                           random.randint(0, self.WINDOWHEIGHT - self.FOODSIZE),
                                           self.FOODSIZE, self.FOODSIZE))


        if self.moveDown and self.player.bottom < self.WINDOWHEIGHT:
            self.player.top += self.MOVESPEED
        if self.moveUp and self.player.top > 0:
            self.player.top -= self.MOVESPEED
        if self.moveLeft and self.player.left > 0:
            self.player.left -= self.MOVESPEED
        if self.moveRight and self.player.right < self.WINDOWWIDTH:
            self.player.right += self.MOVESPEED


        for food in self.foods[:]:
            if self.player.colliderect(food):
                self.foods.remove(food)
                self.score += self.score_increment

                self.playerStretchedImage = pygame.transform.scale(self.playerImage, (self.player.width, self.player.height))
                if pygame.mixer.music.get_busy():
                    pygame.mixer.Sound('./tunes/pickup.wav').play()

    def draw(self):
        # Fill the surface with the background image
        self.WindowSurface.blit(self.background, (0, 0))


        # Draw player and foods on top of the background
        self.WindowSurface.blit(self.playerStretchedImage, self.player)


        for food in self.foods:
            self.WindowSurface.blit(self.foodImage, food)


        score_text = self.font.render(f'Score: {self.score}', True, (200, 130, 200))
        self.WindowSurface.blit(score_text, (10, 10))


    #def run(self):
        #pygame.mixer.music.load('./tunes/background music.mp3')
        #pygame.mixer.music.play(-1, 0.0)
   
        #while 1 < 0: #self.game_over == False:  # this will exit the loop when game_over is True
        #    self.handle_events()
        #    self.update()
        #    self.draw()
        #    pygame.display.update()
        #    self.mainClock.tick(180)


#def main():
#    pygame.init()
#    window_surface = pygame.display.set_mode((500, 500), 0, 32)
#    game = MiniGame1(window_surface)
#    game.run()


#if __name__ == '__main__':
#    main()


