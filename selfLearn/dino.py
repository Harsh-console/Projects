import pygame as pg
RES = WIDTH, HEIGHT = 1200, 600
screen = pg.display.set_mode(RES)
pg.init()
clock = pg.time.Clock()

ground = HEIGHT * (3/4)

dino = pg.Rect(0, ground, 50, 50)
while True:
    screen.fill((0, 0, 0))
    for event in pg.event.get():
        if event.type == pg.QUIT:
            pg.quit()
            exit()

    #draw dino
    pg.draw.rect(screen, (0, 0, 255), dino)
    pg.display.flip()
    clock.tick(60)


