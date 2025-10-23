import pygame as pg
import math

RES = WIDTH, HEIGHT = 1200, 600
fps = 300
screen = pg.display.set_mode(RES)

class objClass:
    def __init__(self, x, y, radius, color, angle, lineLength, lineColor, lineWidth, rayLength, rayColor, rayWidth, angle_vel):
        self.x = x
        self.y = y
        self.pos = self.x, self.y
        self.radius = radius
        self.color = color
        self.angle = angle
        self.lineLength = lineLength
        self.lineColor = lineColor
        self.lineWidth = lineWidth
        self.rayLength = rayLength
        self.rayColor = rayColor
        self.rayWidth = rayWidth
        self.angle_vel = angle_vel

    def draw(self):
        pg.draw.circle(screen, self.color, self.pos, self.radius)

    def drawMainLine(self):
        pg.draw.line(screen, self.lineColor, self.pos, endPos(self.pos, self.lineLength, self.angle), self.lineWidth)

    def rotate(self, isRight):
        if(isRight) :
            self.angle += self.angle_vel * dt;
        else:
            self.angle -= self.angle_vel * dt;


##############################FUNCTIONS#############################################
def endPos(pos, length, angle):
    return (pos[0] +length * math.cos(angle), pos[1] + length * math.sin(angle))

clock = pg.time.Clock()

objects = []
objects.append(objClass( WIDTH//2, HEIGHT//2, 30, 'Blue', 0, 200, 'Red', 1, 200, 'Green', 1, 1))

while True:
    screen.fill((255, 255, 255))
    dt = (clock.tick(fps)) / 1000
    for event in pg.event.get():
        if event.type == pg.QUIT:
            pg.quit()
            exit()

    key = pg.key.get_pressed() 

    # draw obj
    for obj in objects:
        obj.draw()
        obj.drawMainLine()
        if(key[pg.K_LEFT]) : obj.rotate(False)
        if(key[pg.K_RIGHT]) : obj.rotate(True)
    pg.display.set_caption(f'fps : {clock.get_fps():.1f}')
    pg.display.flip()
