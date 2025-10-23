import pygame as pg
import random

WIDTH, HEIGHT = 1200, 600
screen = pg.display.set_mode((WIDTH, HEIGHT))
clock = pg.time.Clock()

class Block():
    def __init__(self, x, y, w = 50, h = 50, color=(100, 100, 100)):
        self.color = color
        self.w = w
        self.h = h
        self.x = x
        self.y = y
        self.rect = pg.Rect(self.x, self.y, self.w, self.h)
    
    def draw(self, surface):
        pg.draw.rect(surface, self.color, self.rect)

blocks = []
ground = []
block_set = [blocks, ground]
tile_size = 50
man_img = pg.transform.scale(pg.image.load('man.png'), (tile_size*10, tile_size*3))
man_img.set_colorkey((255, 255, 255))
man_x, man_y = 0, 0
fps = 600
man_velx = 100
man_vely = 100
running = True

for i in range(0, WIDTH // tile_size):
    ground.append(Block(i * tile_size, HEIGHT - tile_size, tile_size, tile_size, (255, 165, 0)))

for i in range(1, WIDTH // tile_size):
    blocks.append(Block(i * tile_size, HEIGHT - tile_size - random.randint(1, 4) * tile_size, tile_size, tile_size, (255, 165, 0)))

while running:
    dt = (clock.tick(fps)) / 1000;

    for event in pg.event.get():
        if event.type == pg.QUIT:
            pg.quit()
            running = False
            exit()
    # move player
    #man_x += man_velx * dt
    #if(man_x >= WIDTH -
    keys = pg.key.get_pressed()
    if keys[pg.K_RIGHT] : man_x += man_velx * dt
    if keys[pg.K_LEFT] : man_x -= man_velx * dt
    if keys[pg.K_UP] : man_y -= man_vely * dt
    if keys[pg.K_DOWN] : man_y += man_vely * dt


    #display
    screen.fill((0, 255, 255))
    screen.blit(man_img, (man_x, man_y))
    for block_block in block_set:
        for block in block_block:
            block.draw(screen)

    pg.display.set_caption(f'fps : {clock.get_fps():.1f}')
    pg.display.flip()
