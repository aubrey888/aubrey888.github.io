import random
import time

def Intro():
    print('land full of dragons... two dragons')
    print()

def Cave():
    cave = '' ##local variable - empty string
    while cave != '1' and cave != '2' :
        print('Which cave will u go into?')
        cave = input('Pick a cave: ')
    return cave

def Check(chosencave):
    print('You approach the cave...')
    time.sleep(2) ## This waits two seconds

    print('It is dark and spooky...')
    time.sleep(2)
    
    print('A large dragon jumps out in front of you! He opens his jaws and...')
    time.sleep(2)


    friendlyCave = random.randint(1,2)
    if chosencave == str(friendlyCave):
        print('Treasure!')
    else :
        print('you got eaten by a dragon')


Intro()

playAgain = 'yes'
while playAgain == 'yes' : 
    choice = Cave()
    Check(choice)

    print('Do you want to play again?')
    playAgain = input('yes or no: ')

