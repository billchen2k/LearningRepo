# -*- coding: utf-8 -*-
"""
Created on Mon Dec 31 10:31:30 2018

@author: 15156
"""

import pygame
import random
import sys
from pygame.locals import *

snakespeed = 10
UP = 'up'
DOWN = 'down'
RIGHT = 'right'
LEFT = 'left'
win_len = 800  # 窗口的长度
win_high = 500  # 窗口的高度
cell_size = 20
cell_len = int(win_len//cell_size)
cell_high = int(win_high//cell_size)
#定义颜色,后面可以更换
white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
green = (0, 255, 0)
darkgreen = (0, 155, 0)
yellow = (255, 255, 0)
reddark = (150, 0, 0)
blue = (0, 0, 255)
bluedark = (0, 0, 150)
gray = (230, 230, 230)
bgcolor = white  # 由black改为了white，考虑是否需要改为gray
count = 0


def main():
    global win_len, win_high, cell_num, cell_len, cell_high, bgcolor, BASICFONT, displayscreen, snakespeedclock, snakespeed
    pygame.init()  # 初始化背景设置
    displayscreen = pygame.display.set_mode(
        (win_len, win_high))  # 创建一个显示窗口，所有的图形元素都会在这里绘制
    BASICFONT = pygame.font.Font('freesansbold.ttf', 18)
    pygame.display.set_caption('贪吃蛇')  # 这句话是窗口左上角的名称显示
    snakespeedclock = pygame.time.Clock()
    gamestart()
    while True:
        rungame()
        gameover()
#开始建立屏幕，此部分包含在rungame
def rungame():
    #画出屏幕
    global count
    #树莓
    straberryposition_x = random.randint(0, cell_len-1)
    straberryposition_y = random.randint(0, cell_high-1)
    straberryposition = [straberryposition_x, straberryposition_y]
    #蛇
    snakeposition = [[10, 10], [9, 10], [8, 10]]
    head = snakeposition[0]
    direction = RIGHT
    #蛇的运动
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                gameQuit()
            elif event.type == KEYDOWN:
                if (event.key == K_LEFT or event.key == ord('a')) and direction != RIGHT:
                    direction = LEFT
                if (event.key == K_UP or event.key == ord('w')) and direction != DOWN:
                    direction = UP
                if (event.key == K_RIGHT or event.key == ord('d')) and direction != LEFT:
                    direction = RIGHT
                if (event.key == K_DOWN or event.key == ord('s')) and direction != UP:
                    direction = DOWN

        #判断是否吃掉了树莓
        if head == straberryposition:
            straberryposition_x = random.randint(0, cell_len-1)
            straberryposition_y = random.randint(0, cell_high-1)
            straberryposition = [straberryposition_x, straberryposition_y]
            count = count+1

        else:
            del snakeposition[-1]
        #判断蛇死亡的条件：
        if head[0] == -1 or head[0] == cell_len:
            return
        if head[1] == -1 or head[1] == cell_high:
            return
        if head in snakeposition[1:]:
            return
        if direction == RIGHT:
            new_head = [head[0]+1, head[1]]
        if direction == LEFT:
            new_head = [head[0]-1, head[1]]
        if direction == UP:
            new_head = [head[0], head[1]-1]
        if direction == DOWN:
            new_head = [head[0], head[1]+1]

        snakeposition.insert(0, new_head)
        head = new_head
        displayscreen.fill(bgcolor)
        print(snakelevel)
        if snakelevel == 2:
            print(5)
            drawSnakeBarrier(head)
        elif snakelevel == 3:
            print(10)
            global snakespeed
            snakespeed = random.choice([i for i in range(10, 33, 3)])
        drawsnake(snakeposition)
        drawstraberry(straberryposition)
        pygame.display.update()
        snakespeedclock.tick(snakespeed)
#定义开始界面


def gamestart():

    while True:
        displayscreen.fill(bgcolor)
        StartFont = pygame.font.Font('freesansbold.ttf', 35)
        startsurf = StartFont.render('Greddy Snake', True, yellow)
        startrect = startsurf.get_rect()
        startrect.center = (400, 250)
        displayscreen.blit(startsurf, startrect)
        if checkpresskey():
            pygame.event.get()
            return
        presssurf = BASICFONT.render(
            'please press any key to start', True, black)
        pressrect = presssurf.get_rect()
        pressrect.topleft = (500, 400)
        displayscreen.blit(presssurf, pressrect)
        pygame.display.update()
        snakespeedclock.tick(snakespeed)


def checkpresskey():
    global snakelevel
    if len(pygame.event.get(QUIT)) > 0:
        gameQuit()
    keyUpEvents = pygame.event.get(KEYUP)
    if len(keyUpEvents) == 0:
        return None
    if keyUpEvents[0].key == K_ESCAPE:
        gameQuit()
    #设置难度
    H = keyUpEvents[0].key
    if H == K_m:
        snakelevel = 2
    elif H == K_h:
        snakelevel = 3
    else:
        snakelevel = 1
    return keyUpEvents[0].key


def gameQuit():
    pygame.quit()
    sys.exit()

def drawsnake(position):
    for seg in position:
        x = seg[0]*cell_size
        y = seg[1]*cell_size
        snakesegRect = pygame.Rect(x, y, cell_size, cell_size)
        pygame.draw.rect(displayscreen, red, snakesegRect)


def drawwindows():
    for i in range(0, win_len, cell_size):
        pygame.draw.line(displayscreen, green, (i, 0), (i, win_high))
    for i in range(0, win_high, cell_size):
        pygame.draw.line(displayscreen, green, (0, i), (win_len, i))


def drawstraberry(position):
        x = position[0]*cell_size
        y = position[1]*cell_size
        straberryRect = pygame.Rect(x, y, cell_size, cell_size)
        pygame.draw.rect(displayscreen, darkgreen, straberryRect)
#难度为2的障碍物和死亡判定条件附加

def drawSnakeBarrier(head):
    barrier1 = [[14, 4], [14, 5], [14, 6], [14, 7], [
        14, 8], [14, 9], [14, 10], [14, 11], [14, 12]]
    barrier2 = [[32, 22], [14, 21], [14, 20], [14, 19], [14, 18],
                [14, 17], [14, 16], [14, 15], [14, 14], [14, 13]]
    barrier3 = [4]*9
    for i in range(24, 33):
        barrier3[i-24] = [i, barrier3[i-24]]
    barrier4 = [22]*9
    for i in range(14, 23):
        barrier4[i-14] = [i, barrier4[i-14]]
    barrier5 = [23]*19
    for i in range(4, 23):
        barrier5[i-4] = [barrier5[i-4], i]
    barrier = barrier1+barrier2+barrier3+barrier4+barrier5
    drawsnake(barrier)
    if head in barrier:
        gameover()


def gameover():
    global count
    displayscreen.fill(bgcolor)
    pygame.display.update()
    OVERFONT = pygame.font.Font('freesansbold.ttf', 50)
    GAMEsurf = OVERFONT.render('GameOver', True, red)
    GAMErect = GAMEsurf.get_rect()
    GAMErect.midtop = (400, 100)
    #OVERrect=OVERsurf.get_rect()
    #OVERrect.midtop=(560,100)
    presssurf = BASICFONT.render('please press any key to start', True, black)
    pressrect = presssurf.get_rect()
    pressrect.topleft = (500, 400)
    quitsurf = BASICFONT.render('press Esc to quit', True, black)
    quitrect = quitsurf.get_rect()
    quitrect.topleft = (500, 440)
    GRADEsurf = OVERFONT.render('YOUR GRADE:%d' % count, True, yellow)
    GRADErect = GRADEsurf.get_rect()
    GRADErect.midtop = (400, 200)
    displayscreen.blit(GRADEsurf, GRADErect)
    displayscreen.blit(GAMEsurf, GAMErect)
    displayscreen.blit(presssurf, pressrect)
    displayscreen.blit(quitsurf, quitrect)
    #displayscreen.blit(OVERsurf,OVERrect)
    pygame.display.update()
    pygame.time.wait(500)
    checkpresskey()

    while True:
        if checkpresskey():
            pygame.event.get()
            return


if __name__ == '__main__':
    try:
        main()
    except SystemExit:
        pass

    