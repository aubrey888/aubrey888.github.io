import pygame
import sys
import random
from pygame.locals import *




class MiniGame4:
    def __init__(self, window_surface, selected_skin):
        self.WindowSurface = window_surface
        self.mainClock = pygame.time.Clock()
        self.WINDOWWIDTH = 500
        self.WINDOWHEIGHT = 500
        pygame.display.set_caption("Hola! Kitty! MiniGame4")



        # Load background image
        self.background = pygame.image.load('./art/background.png')
        self.background = pygame.transform.scale(self.background, (self.WINDOWWIDTH, self.WINDOWHEIGHT))


        self.BLACK = (0, 0, 0)
        self.WHITE = (255, 255, 255)
        self.BLUE = (0, 0, 255)


        # player
        self.player = pygame.Rect(300, 100, 50, 50)
        self.playerImage = pygame.image.load(selected_skin + '.png')
        self.playerStretchedImage = pygame.transform.scale(self.playerImage, (50, 40))


        # blue squares
        self.square_size = 5
        self.square_speed = 2
        self.squares = []


        # movement variables
        self.moveLeft = False
        self.moveRight = False
        self.moveUp = False
        self.moveDown = False
        self.MOVESPEED = 4

        self.game_over = False



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


    def update(self):
        # Create new blue square
        if random.randint(0, 10) == 0:  # Adjust frequency of square creation
            new_square = pygame.Rect(random.randint(0, self.WINDOWWIDTH - self.square_size),
                                     0, self.square_size, self.square_size)
            self.squares.append(new_square)


        # Move player
        if self.moveDown and self.player.bottom < self.WINDOWHEIGHT:
            self.player.top += self.MOVESPEED
        if self.moveUp and self.player.top > 0:
            self.player.top -= self.MOVESPEED
        if self.moveLeft and self.player.left > 0:
            self.player.left -= self.MOVESPEED
        if self.moveRight and self.player.right < self.WINDOWWIDTH:
            self.player.right += self.MOVESPEED


        # Move existing squares
        for square in self.squares[:]:
            square.top += self.square_speed


            # Check collision with player
            if square.colliderect(self.player):
                # Player collided with square, end the game
                print("Game Over - You touched a blue square!")
                self.game_over = True

                #pygame.quit()
                #sys.exit()


            # Remove squares that have gone past the bottom of the window
            if square.top > self.WINDOWHEIGHT:
                self.squares.remove(square)


    def draw(self):
        self.WindowSurface.blit(self.background, (0, 0))
        self.WindowSurface.blit(self.playerStretchedImage, self.player)
        for square in self.squares:
            pygame.draw.rect(self.WindowSurface, self.BLUE, square)


    def run(self):
        #pygame.mixer.music.load('./tunes/rainmusic.mp3')
        #pygame.mixer.music.play(-1, 0.0)
        while True:
            self.handle_events()
            self.update()
            self.draw()
            pygame.display.update()
            self.mainClock.tick(60)  # 60 frames per second




"""def main():
    pygame.init()
    window_surface = pygame.display.set_mode((500, 500), 0, 32)
    gamefour = MiniGame4(window_surface)
    gamefour.run()




if __name__ == '__main__':
    main()"""
