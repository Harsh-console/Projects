import pygame as pg
import sys
RES = WIDTH, HEIGHT = 1200, 600
fps = 60
rad = 30
pg.init()       
screen = pg.display.set_mode(RES)
clock = pg.time.Clock()
running = True
x = WIDTH // 2
y = HEIGHT // 2
font = pg.font.Font(None, 24)
gravX = 0 # right
gravY = 1 # down
gravVelx = gravVely = 0.2
while True:
    screen.fill((0, 255, 255))
    text = font.render(f"GravX : {gravX:.1f}, GravY : {gravY:.1f}", True, (255, 255, 255))
    screen.blit(text, (WIDTH // 3, HEIGHT //20))
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
            pg.quit()
            exit()
    if not running : break

    # Input
    key = pg.key.get_pressed()
    if(key[pg.K_UP]):
        gravY -= gravVely
    if(key[pg.K_DOWN]):
        gravY += gravVely
    if(key[pg.K_RIGHT]):
        gravX += gravVelx
    if(key[pg.K_LEFT]):
        gravX -= gravVelx

    # Apply Gravity
    x += gravX
    y += gravY

    # Check Boundary Conditions
    if(x < rad):
        x = rad
    if(y < rad):
        y = rad
    if(x > WIDTH - rad):
        x = WIDTH - rad
    if ( y > HEIGHT - rad):
        y = HEIGHT - rad

    # Draw Circle
    pg.draw.circle(screen, (255, 0, 0), (x, y), rad)

    clock.tick(fps)
    pg.display.flip()

print("Thank YOU!")    
