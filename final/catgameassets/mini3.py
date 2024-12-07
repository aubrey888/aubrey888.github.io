import pygame
import sys
import random
from pygame.locals import *


class MiniGame3:
    def __init__(self, window_surface,selected_skin):
        self.WindowSurface = window_surface
        self.mainClock = pygame.time.Clock()
        self.WINDOWWIDTH = 500
        self.WINDOWHEIGHT = 500
        pygame.display.set_caption("Get it kitty! MiniGame3")


        # Load background image
        self.background = pygame.image.load('./art/background.png')
        self.background = pygame.transform.scale(self.background, (self.WINDOWWIDTH, self.WINDOWHEIGHT))


        self.BLACK = (0, 0, 0)
        self.WHITE = (255, 255, 255)
        self.RED = (255, 0, 0)

        self.score = 0

        # player
        self.player = pygame.Rect(300, 100, 50, 50)
        self.playerImage = pygame.image.load(selected_skin +'.png')
        self.playerStretchedImage = pygame.transform.scale(self.playerImage, (50, 40))


        # laser
        self.laser_size = 15
        self.laser = pygame.Rect(random.randint(0, self.WINDOWWIDTH - self.laser_size),
                                  random.randint(0, self.WINDOWHEIGHT - self.laser_size),
                                  self.laser_size, self.laser_size)
        self.laser_speed = 3
        self.speed_decrease_rate = 0.0001  # Adjust as needed
        self.laser_direction = random.choice(['up', 'down', 'left', 'right'])


        # movement variables
        self.moveLeft = False
        self.moveRight = False
        self.moveUp = False
        self.moveDown = False
        self.MOVESPEED = 4


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
        if self.laser_speed > 0:
            self.laser_speed -= self.speed_decrease_rate


        if self.player.colliderect(self.laser):
            # Player caught the laser, end the game
            print("You caught the laser!")
            self.score = 30
            ##pygame.quit()
            ## sys.exit()


        # move player
        if self.moveDown and self.player.bottom < self.WINDOWHEIGHT:
            self.player.top += self.MOVESPEED
        if self.moveUp and self.player.top > 0:
            self.player.top -= self.MOVESPEED
        if self.moveLeft and self.player.left > 0:
            self.player.left -= self.MOVESPEED
        if self.moveRight and self.player.right < self.WINDOWWIDTH:
            self.player.right += self.MOVESPEED


        # move laser
        if self.laser_direction == 'up' and self.laser.top >= 0:
            self.laser.top -= self.laser_speed
        elif self.laser_direction == 'down' and self.laser.bottom < self.WINDOWHEIGHT:
            self.laser.top += self.laser_speed
        elif self.laser_direction == 'left' and self.laser.left > 0:
            self.laser.left -= self.laser_speed
        elif self.laser_direction == 'right' and self.laser.right < self.WINDOWWIDTH:
            self.laser.left += self.laser_speed


        # update laser direction if it hits window edges
        if self.laser.top < 0 or self.laser.bottom > self.WINDOWHEIGHT or self.laser.left < 0 or self.laser.right > self.WINDOWWIDTH:
            self.laser_direction = random.choice(['up', 'down', 'left', 'right'])


        # calculate distance between player and laser
        distance_x = self.player.centerx - self.laser.centerx
        distance_y = self.player.centery - self.laser.centery
        distance = ((distance_x ** 2) + (distance_y ** 2)) ** 0.5


        # if player is within a certain distance, move laser away from player
        if distance < 100:
            if distance != 0:
                self.laser.left -= (self.laser_speed * distance_x / distance)
                self.laser.top -= (self.laser_speed * distance_y / distance)


    def draw(self):
        self.WindowSurface.blit(self.background, (0,0))
        self.WindowSurface.blit(self.playerStretchedImage, self.player)
        pygame.draw.rect(self.WindowSurface, self.RED, self.laser)


    def run(self):
        #pygame.mixer.music.load('./tunes/lasermusic.mp3')
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
    gamethree = MiniGame3(window_surface)
    gamethree.run()


if __name__ == '__main__':
    main()
"""