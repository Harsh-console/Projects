import pygame as pg
import math

# Constants
RES = WIDTH, HEIGHT = 1200, 600
fps = 30
back_color = (0, 0, 0)
BLUE = (0, 0, 255)
fov = math.pi / 3 # in Radians
h_fov = fov / 2
depth = 500 # in pixels
numRay = 30
speed = 4

# MAP
gameMap = [
[1, 1, 1, 1, 1, 1, 1, 1],
[1, 0, 0, 0, 1, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 1, 1],
[1, 0, 0, 0, 0, 0, 0, 1],
[1, 0, 0, 0, 0, 0, 0, 1],
[1, 1, 1, 1, 1, 1, 1, 1],
        ]
ROWS = len(gameMap)
COLS = len(gameMap[0])
tileX = WIDTH // COLS
tileY = HEIGHT // ROWS

walls = []
for row in range(ROWS):
    for col in range(COLS):
        if gameMap[row][col]:
            rect = pg.Rect(col * tileX, row * tileY, tileX, tileY)
            walls.append(rect)

screen = pg.display.set_mode(RES)
clock = pg.time.Clock()

class Circle:
    def __init__(self, rad, color, x, y, angle, linecolor, linelength, raycolor):
        self.rad = rad
        self.color = color
        self.x = x
        self.y = y
        self.velX = 2
        self.velY = 2
        self.accX = 1
        self.accY = 1
        self.linecolor = linecolor
        self.linelength = linelength
        self.angle = angle
        self.rotVel = 0.1
        self.raycolor = raycolor
    def draw(self):
        pg.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.rad)
        pg.draw.line(screen, self.linecolor, (self.x, self.y), (self.x + self.linelength * math.cos(self.angle), self.y + self.linelength * math.sin(self.angle)), 2)

    def drawRays(self):
        for i in range(numRay):
            rayAngle = self.angle - h_fov + (i * fov / numRay)
            for step in range(depth) :
                xPos = int((self.x + step * math.cos(rayAngle)) / tileX)
                yPos = int((self.y + step * math.sin(rayAngle)) / tileY)
                if gameMap[yPos][xPos] : 
                    break
            pg.draw.line(screen, self.raycolor, (self.x, self.y), (self.x + step * math.cos(rayAngle), self.y + step * math.sin(rayAngle)), 1)

def circle_rect_collision(circle, rect):
    #find closest point on rect from circle centre
    closest_x = max(rect.left, min(circle.x, rect.right))
    closest_y = max(rect.top, min(rect.bottom, circle.y))

    dx = circle.x - closest_x
    dy = circle.y - closest_y
    return (dx ** 2 + dy ** 2 ) < circle.rad ** 2

obj = Circle(20, 'Red', WIDTH // 2, HEIGHT // 2, 0, "Yellow", 100, 'Pink')

running = True
while running :

    screen.fill(back_color)
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

    key = pg.key.get_pressed()
    """
    # Inputs
    if(key[pg.K_w]) : obj.velY -= obj.accY
    if(key[pg.K_s]) : obj.velY += obj.accY
    if(key[pg.K_d]) : obj.velX += obj.accX
    if(key[pg.K_a]) : obj.velX -= obj.accX
    if(key[pg.K_RIGHT]) : obj.angle += obj.rotVel
    if(key[pg.K_LEFT]) : obj.angle -=  obj.rotVel 
    # move object
    obj.x += obj.velX
    obj.y += obj.velY
    """
    # use probable movement in obj position dx and dy
    dx = 0
    dy = 0
    
    if(key[pg.K_w]) : dy -= speed
    if(key[pg.K_s]) : dy += speed
    if(key[pg.K_d]) : dx += speed
    if(key[pg.K_a]) : dx -= speed
    if(key[pg.K_RIGHT]) : obj.angle += obj.rotVel
    if(key[pg.K_LEFT]) : obj.angle -=  obj.rotVel

    # Check for Collision with Walls
    obj.x += dx
    for wall in walls:
        if circle_rect_collision(obj, wall):
            obj.x -= dx
            break
    obj.y += dy
    for wall in walls:
        if circle_rect_collision(obj, wall):
            obj.y -= dy
            break

    # Draw Map
    for wall in walls:
        pg.draw.rect(screen, 'Green', wall)

    # Draw Object
    obj.draw()
    obj.drawRays()

    pg.display.flip()
    clock.tick(fps)
    pg.display.set_caption(f"fps: {clock.get_fps():.1f}")
