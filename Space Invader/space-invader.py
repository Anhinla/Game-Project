import pygame
import random
import math
# Everything you want to do with music
from pygame import mixer
#Initialize the pygame 
pygame.init()

#create the screen
screen = pygame.display.set_mode((800,600))
running = True

#background
background = pygame.image.load('backgound.jpg')


#title and icon
pygame.display.set_caption("Space Invaders")
icon = pygame.image.load('spaceship.png')
pygame.display.set_icon(icon)

#player 
playerImg = pygame.image.load('space.png')
playerX = 370
playerY = 480
playerX_change = 0

#Enemy 
enemyImg = []
enemyX =[]
enemyY = []
enemyX_change = []
enemyY_change = []
num_of_enemies = 6

for i in range(num_of_enemies):
    

    enemyImg.append(pygame.image.load('alien.png'))
    enemyX.append(random.randint(0,800-64))
    enemyY.append(random.randint(50,150))
    enemyX_change.append(0.1)
    enemyY_change.append(100)

#Bullet

#ready: you can't see the bullet on the screen
#fire: the bullet is currently moving
bulletImg = pygame.image.load('bullet.png')
bulletX = 0
bulletY = 480
bulletX_change = 0
bulletY_change = 0.5
bullet_state = "ready"

#score 
score =  0
font = pygame.font.Font('freesansbold.ttf',30)
textX = 10
textY = 10
def show_score(x,y):
    score_val = font.render("Score :"+str(score),1,(255, 221, 89))
    screen.blit(score_val,(x,y))

def player(x,y):
    screen.blit(playerImg,(x,y))

def enemy(x,y,i):
    screen.blit(enemyImg[i],(x,y))

def fire_bullet(x,y):
    global bullet_state
    bullet_state = "fire"
    screen.blit(bulletImg,(x+16,y+10))

#check collision
def isCollision(enemyX, enemyY,bulletX, bulletY):
    distance = math.sqrt(math.pow(enemyX-bulletX,2)+math.pow(enemyY-bulletY,2))
    if distance < 27:
        return True
    else:
        return False

#game over
over_font = pygame.font.Font('freesansbold.ttf',100)
def game_over_text():
    over_text = font.render('GAME OVER',True,(255,255,255))
    screen.blit(over_text,(200,250))


#game loop
while running:

    screen.fill((0, 0, 0))
    screen.blit(background,(0,0))
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            running = False
    
    #if keystroke is pressed check whether right or left
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                playerX_change = -0.2
            if event.key == pygame.K_RIGHT:
                playerX_change = 0.2
            if event.key == pygame.K_SPACE:
                if bullet_state is "ready":
                    bullet_Sound = mixer.Sound('laser.wav')
                    bullet_Sound.play()
                    bulletX = playerX
                    fire_bullet(bulletX,bulletY)

        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                playerX_change = 0
    
    playerX += playerX_change
    if playerX<0:
        playerX = 0
    elif playerX > 800-64:
        playerX = 800-64
    for i in range(num_of_enemies):
        #Game over 
        if enemyY[i] > 200:
            for j in range(num_of_enemies):
                enemyY[j] = 2000
            game_over_text()
            break
        enemyX[i] += enemyX_change[i]
        if enemyX[i]<0 or enemyX[i]>800-64:
            enemyX_change[i] = -enemyX_change[i]
            enemyY[i] += 10
        #Collision
        collision = isCollision(enemyX[i],enemyY[i],bulletX,bulletY)
        if collision:
            coll_Sound = mixer.Sound('explosion.wav')
            coll_Sound.play()
            bulletY = 480
            bullet_state = "ready"
            score += 10
            print(score)
            enemyX[i] = random.randint(0,800-64)
            enemyY[i] = random.randint(50,150)

        enemy(enemyX[i],enemyY[i],i)
    #Bullet Movement
    if bulletY <= 0:
        bullet_state = "ready"
        bulletY = 480

    if bullet_state == "fire":
        fire_bullet(bulletX,bulletY)
        bulletY -= bulletY_change

    
    
    player(playerX,playerY)
    show_score(textX,textY)
    
    pygame.display.update()
