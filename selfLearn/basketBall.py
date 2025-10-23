import pygame, math, sys

# --- CONFIG ---
WIDTH, HEIGHT = 800, 400
HALF_HEIGHT = HEIGHT // 2
FOV = math.pi / 3
HALF_FOV = FOV / 2
NUM_RAYS = 200
MAX_DEPTH = 20
DELTA_ANGLE = FOV / NUM_RAYS
DIST = NUM_RAYS / (2 * math.tan(HALF_FOV))
PROJ_COEFF = 3 * DIST * 40
SCALE = WIDTH // NUM_RAYS

# --- MAP (1=wall, 0=empty) ---
world_map = {
    (1,1),(1,2),(1,3),(1,4),(1,5),
    (2,1),(3,1),(4,1),(5,1),
    (5,2),(5,3),(5,4),(5,5),
    (2,5),(3,5),(4,5),
}

# --- PLAYER ---
player_pos = [3.0, 3.0]
player_angle = 0
player_speed = 0.04

# --- INIT ---
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# --- FUNCTIONS ---
def mapping(a, b):
    return int(a), int(b)

def ray_casting(screen, player_pos, player_angle):
    cur_angle = player_angle - HALF_FOV
    xo, yo = player_pos
    for ray in range(NUM_RAYS):
        sin_a = math.sin(cur_angle)
        cos_a = math.cos(cur_angle)
        for depth in range(1, MAX_DEPTH * 100):
            depth /= 100
            x = xo + depth * cos_a
            y = yo + depth * sin_a
            if mapping(int(x), int(y)) in world_map:
                # Fix fish-eye
                depth *= math.cos(player_angle - cur_angle)
                proj_height = PROJ_COEFF / (depth + 0.0001)

                c = 255 / (1 + depth ** 2 * 0.1)
                color = (c, c, c)
                pygame.draw.rect(screen, color,
                    (ray * SCALE, HALF_HEIGHT - proj_height // 2, SCALE, proj_height))
                break
        cur_angle += DELTA_ANGLE

# --- MAIN LOOP ---
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # movement
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        player_angle -= 0.04
    if keys[pygame.K_RIGHT]:
        player_angle += 0.04
    if keys[pygame.K_w]:
        player_pos[0] += player_speed * math.cos(player_angle)
        player_pos[1] += player_speed * math.sin(player_angle)
    if keys[pygame.K_s]:
        player_pos[0] -= player_speed * math.cos(player_angle)
        player_pos[1] -= player_speed * math.sin(player_angle)

    # draw
    screen.fill((0, 0, 0))
    pygame.draw.rect(screen, (100,100,100), (0,0,WIDTH,HALF_HEIGHT))  # ceiling
    pygame.draw.rect(screen, (60,60,60), (0,HALF_HEIGHT,WIDTH,HALF_HEIGHT))  # floor

    ray_casting(screen, player_pos, player_angle)
    pygame.display.flip()
    clock.tick(60)

