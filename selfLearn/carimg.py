import pygame as pg
RES = WIDTH, HEIGHT = 1200, 600
screen = pg.display.set_mode(RES)
clock = pg.time.Clock()
fps = 600
carVel = 100

carWidth, carHeight = 150, 100
carImg = pg.image.load('car.png')
carImgScaled = pg.transform.scale(carImg, (carWidth, carHeight))
carImgScaled.set_colorkey((255, 255, 255))
x, y = WIDTH // 10, 3 * HEIGHT // 4

while True:
    dt = (clock.tick(fps)) / 1000;
    for event in pg.event.get():
        if event.type==pg.QUIT:
            pg.quit()
            exit()
    screen.fill((0, 255, 255))
    key = pg.key.get_pressed()
    if(key[pg.K_RIGHT]) : x += carVel * dt
    if(key[pg.K_LEFT]) : x -= carVel * dt

    #draw car
    screen.blit(carImgScaled, (x, y))

    pg.display.set_caption(f"fps : {clock.get_fps():.1f}")
    pg.display.flip()
