import pygame
import sys
import time 
from pygame.locals import *
from mini1 import MiniGame1
from mini2 import MiniGame2
from mini3 import MiniGame3
from mini4 import MiniGame4 
from skinselection import SkinSelection  # Import the SkinSelection class


# Setup pygame
pygame.init()
mainClock = pygame.time.Clock()


# Setup window
WINDOWWIDTH = 500
WINDOWHEIGHT = 500
WindowSurface = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT), 0, 32)


pygame.display.set_caption("Cat Life :3")


# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)


# Game state
game_state = "start_menu"


# MiniGame instances (initialized later)
mini_game1 = None
mini_game2 = None
mini_game3 = None
mini_game4 = None


# Load background music
pygame.mixer.music.load('./tunes/background music.mp3')
pygame.mixer.music.play(-1, 0.0)


# Function to handle events for the active mini-game
def handle_mini_game_events(active_game):
    active_game.handle_events()


## variables for timer

#levelstarttime = time.time()

## Function for time 
def time_limit_exceeded(start_time):
    return time.time() - start_time >= 30


endlevelcount = 0 


def draw_start_menu():
    # Load the menu background image
    menu_background = pygame.image.load('menu.png')
    menu_background = pygame.transform.scale(menu_background, (WINDOWWIDTH, WINDOWHEIGHT))  # Scale image to fit window size


    # Blit the menu background onto the window surface
    WindowSurface.blit(menu_background, (0, 0))


    # Add other elements on top of the background
    font = pygame.font.SysFont('arial', 40)
    title = font.render('', True, WHITE)
    start_button = font.render('', True, WHITE)
    WindowSurface.blit(title, (WINDOWWIDTH/2 - title.get_width()/2, WINDOWHEIGHT/2 - title.get_height()/2))
    WindowSurface.blit(start_button, (WINDOWWIDTH/2 - start_button.get_width()/2, WINDOWHEIGHT/2 + start_button.get_height()/2))


    # Update the display
    pygame.display.update()


def draw_game_over_screen():
    # Draw the game over screen
    WindowSurface.fill(BLACK)
    font = pygame.font.SysFont('arial', 40)
    title = font.render('Game Over', True, WHITE)
    restart_button = font.render('R - Restart', True, WHITE)
    quit_button = font.render('Q - Quit', True, WHITE)
    WindowSurface.blit(title, (WINDOWWIDTH/2 - title.get_width()/2, WINDOWHEIGHT/2 - title.get_height()/3))
    WindowSurface.blit(restart_button, (WINDOWWIDTH/2 - restart_button.get_width()/2, WINDOWHEIGHT/1.9 + restart_button.get_height()))
    WindowSurface.blit(quit_button, (WINDOWWIDTH/2 - quit_button.get_width()/2, WINDOWHEIGHT/2 + quit_button.get_height()/2))
    pygame.display.update()


"""def transition_screen(text_lines):
    # Display a transition screen
    WindowSurface.fill(BLACK)
    font = pygame.font.SysFont(None, 36)
    y_offset = WINDOWHEIGHT // 2 - (len(text_lines) * font.get_height()) // 2
    for line in text_lines:
        text_surface = font.render(line, True, WHITE)
        text_rect = text_surface.get_rect(center=(WINDOWWIDTH // 2, y_offset))
        WindowSurface.blit(text_surface, text_rect)
        y_offset += font.get_height()
    pygame.display.flip()
    pygame.time.delay(2000)"""

def minigame_transition_screen(game_state): #intro to fish catching
    if game_state == "mini_game1" :
        transition_screen = pygame.image.load('./art/T1.png')
    elif game_state == "mini_game2" :
        transition_screen = pygame.image.load('./art/T2.png')
    elif game_state == "mini_game3" :
        transition_screen = pygame.image.load('./art/T3.png')
    elif game_state == "mini_game4" :
        transition_screen = pygame.image.load('./art/T4.png')
    elif game_state == "bad" :
        transition_screen = pygame.image.load('./art/bad.png')
    elif game_state == "okay" :
        transition_screen = pygame.image.load('./art/okay.png')
    elif game_state == "good" :
        transition_screen = pygame.image.load('./art/good.png')
    elif game_state == "normal" :
        transition_screen = pygame.image.load('./art/normal.png')
    elif game_state == "skinselectionscreen" :
        transition_screen = pygame.image.load('./art/menu.png')
    elif game_state == "taskcompleted" :
        transition_screen = pygame.image.load('./art/task.png')
        pygame.mixer.music.load('./tunes/goodjob.mp3')
        pygame.mixer.music.play(0, 0.0)
    elif game_state == "notcompleted" :
        transition_screen = pygame.image.load('./art/failed.png')
        pygame.mixer.music.load('./tunes/fail.mp3')
        pygame.mixer.music.play(0, 0.0)
    else : 
        transition_screen = pygame.image.load('./art/great.png')
    transition_screen = pygame.transform.scale(transition_screen, (WINDOWWIDTH, WINDOWHEIGHT))  # Scale image to fit window size
    WindowSurface.blit(transition_screen, (0, 0))  # Draw the background image


    pygame.display.update()
    pygame.time.delay(5000)


"""def draw_skin_selection_screen():
    # Draw the skin selection screen
    WindowSurface.fill(BLACK)
    font = pygame.font.SysFont(None, 36)
    text_lines = ["Select Cat Skin:", "1. Ragdoll ", "2. Calico ", "3. Black Cat "]
    y_offset = WINDOWHEIGHT // 2 - (len(text_lines) * font.get_height()) // 2
    for line in text_lines:
        text_surface = font.render(line, True, WHITE)
        text_rect = text_surface.get_rect(center=(WINDOWWIDTH // 2, y_offset))
        WindowSurface.blit(text_surface, text_rect)
        y_offset += font.get_height()
    pygame.display.flip()"""


# Main game loop
# pygame.mixer.music.load('background music.mp3')
# pygame.mixer.music.play(-1, 0.0)


while True:

    if game_state == "start_menu":
        # Draw start menu
        draw_start_menu()


        # Handle events for the start menu
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN and event.key == K_SPACE:
                # Show skin selection screen and get the selected skin
                #draw_skin_selection_screen()
                minigame_transition_screen("skinselectionscreen")
                selected_skin = SkinSelection.skin_selection()
                game_state = "mini_game1"  # Start with MiniGame 1
                ## transition_screen(["Starting MiniGame 1..."])
                minigame_transition_screen(game_state)
    elif game_state.startswith("mini_game"):
        # Initialize MiniGame instances with selected_skin when available
        if game_state == "mini_game1" and mini_game1 is None:
            mini_game2 = MiniGame2(WindowSurface, selected_skin)
            mini_game3 = MiniGame3(WindowSurface, selected_skin)
            mini_game4 = MiniGame4(WindowSurface, selected_skin)
            mini_game1 = MiniGame1(WindowSurface, selected_skin) # keep window title.
            start_time = time.time()

        #print(time_limit_exceeded(start_time))
        #print(game_state)
        if  ( mini_game1.score >= 30 or time_limit_exceeded(start_time) ) and game_state == "mini_game1": 
            game_state = "mini_game2"
            # print("bails bails bails")
            #start_time = time.time()
            mini_game2 = MiniGame2(WindowSurface, selected_skin)
            if mini_game1.score >= 30:
                minigame_transition_screen("taskcompleted")
                endlevelcount += 1
            else:
                minigame_transition_screen("notcompleted")
            pygame.mixer.music.load('./tunes/fishmusic.mp3')
            pygame.mixer.music.play(-1, 0.0)

            minigame_transition_screen(game_state)
            mini_game1.score = 0
            start_time = time.time()


        if  (mini_game2.score >= 30 or mini_game2.toxic_fish_count >= 3 or time_limit_exceeded(start_time) ) and game_state == "mini_game2":
            game_state = "mini_game3"
            mini_game3 = MiniGame3(WindowSurface, selected_skin)
            if mini_game2.toxic_fish_count >= 3:
                minigame_transition_screen("notcompleted") 
            elif mini_game2.score >= 30:
                minigame_transition_screen("taskcompleted")
                endlevelcount += 1
            else: # if youre here then time ran out.
                minigame_transition_screen("notcompleted")
            pygame.mixer.music.load('./tunes/lasermusic.mp3')
            pygame.mixer.music.play(-1, 0.0)
                 
            minigame_transition_screen(game_state)
            mini_game2.toxic_fish_count = 0
            mini_game2.score = 0
            start_time = time.time()

            
            

        if  (mini_game3.score >= 3 or time_limit_exceeded(start_time)) and game_state == "mini_game3":
            game_state = "mini_game4"
            # levelstarttime = time.time()
            mini_game4 = MiniGame4(WindowSurface, selected_skin)
            if mini_game3.score >= 30:
                minigame_transition_screen("taskcompleted")
                endlevelcount += 1
            else:
                minigame_transition_screen("notcompleted")

            pygame.mixer.music.load('./tunes/rainmusic.mp3')
            pygame.mixer.music.play(-1, 0.0)
            minigame_transition_screen(game_state)
            mini_game3.score = 0 
            start_time = time.time()


        # check for game over
        if (mini_game4.game_over or time_limit_exceeded(start_time)) and game_state == "mini_game4":
            if mini_game4.game_over:
                minigame_transition_screen("notcompleted")
            else:
                minigame_transition_screen("taskcompleted")
                endlevelcount += 1
            #transition_screen(["GAME OVER!"])

            #if endlevelcount == 0 :
            #    game_state = "bad"
            match endlevelcount:
                case 0 :
                    game_state = "bad"
                case 1 :
                    game_state = "okay"
                case 2 :
                    game_state = "normal"
                case 3 :
                    game_state = "good"
                case 4 : 
                    game_state = "great"

            minigame_transition_screen(game_state)
            game_state = "game_over"



        # Determine the active mini-game based on the game state
        if game_state == "mini_game1":
            active_game = mini_game1
        elif game_state == "mini_game2":
            active_game = mini_game2
        elif game_state == "mini_game3":
            active_game = mini_game3
        elif game_state == "mini_game4":
            active_game = mini_game4
       
        # Handle events for the active mini-game
        handle_mini_game_events(active_game)
       
        # Update and draw the active mini-game
        active_game.update()
        active_game.draw()
       
        pygame.display.update()
        mainClock.tick(60)  # Ensure the game runs at 60 frames per second
    elif game_state == "game_over":
        # Draw game over screen
        draw_game_over_screen()


        # Handle events for the game over screen
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_r:
                    game_state = "start_menu"
                    endlevelcount = 0 
                    start_time = time.time()
                    pygame.mixer.music.load('./tunes/background music.mp3')
                    pygame.mixer.music.play(-1, 0.0)
