import pygame, random, math

# --- Setup ---
WIDTH, HEIGHT = 800, 600
NUM_BOIDS = 50
MAX_SPEED = 4
VISION = 60
ALIGN_STRENGTH = 0.05
COHESION_STRENGTH = 0.01
SEPARATION_STRENGTH = 0.05

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

GRID_SIZE = 80  # each cell covers this much area

def make_grid(boids):
    grid = {}
    for b in boids:
        cell = (int(b.pos.x // GRID_SIZE), int(b.pos.y // GRID_SIZE))
        grid.setdefault(cell, []).append(b)
    return grid


# --- Boid class ---
class Boid:
    def __init__(self):
        self.pos = pygame.Vector2(random.uniform(0, WIDTH),
                                  random.uniform(0, HEIGHT))
        angle = random.uniform(0, math.tau)
        self.vel = pygame.Vector2(math.cos(angle), math.sin(angle)) * MAX_SPEED

    def update(self, boids, grid):
        # Determine which cell the boid is in
        cell_x, cell_y = int(self.pos.x // GRID_SIZE), int(self.pos.y // GRID_SIZE)

        neighbors = []
        # Check this cell + 8 surrounding cells
        for dx in (-1, 0, 1):
            for dy in (-1, 0, 1):
                nearby = grid.get((cell_x + dx, cell_y + dy))
                if nearby:
                    for n in nearby:
                        if n is not self and self.pos.distance_to(n.pos) < VISION:
                            neighbors.append(n)

        # The rest of your boid rules (alignment, cohesion, etc.) stay the same...
        if not neighbors:
            self.pos += self.vel
            return

        avg_vel = pygame.Vector2()
        avg_pos = pygame.Vector2()
        separation = pygame.Vector2()

        for n in neighbors:
            avg_vel += n.vel
            avg_pos += n.pos
            diff = self.pos - n.pos
            if diff.length() > 0:
                separation += diff / (diff.length() ** 2)

        avg_vel /= len(neighbors)
        avg_pos /= len(neighbors)

        self.vel += (avg_vel - self.vel) * ALIGN_STRENGTH
        self.vel += (avg_pos - self.pos) * COHESION_STRENGTH
        self.vel += separation * SEPARATION_STRENGTH

        if self.vel.length() > MAX_SPEED:
            self.vel.scale_to_length(MAX_SPEED)

        self.pos += self.vel

        if self.pos.x < 0: self.pos.x += WIDTH
        if self.pos.x > WIDTH: self.pos.x -= WIDTH
        if self.pos.y < 0: self.pos.y += HEIGHT
        if self.pos.y > HEIGHT: self.pos.y -= HEIGHT

    def draw(self, surf):
        # Small triangle representing the boid
        angle = self.vel.angle_to(pygame.Vector2(1, 0))
        points = [pygame.Vector2(10, 0), pygame.Vector2(-5, 3), pygame.Vector2(-5, -3)]
        rotated = [self.pos + p.rotate(-angle) for p in points]
        pygame.draw.polygon(surf, (0, 255, 200), rotated)

# --- Simulation loop ---
boids = [Boid() for _ in range(NUM_BOIDS)]
running = True
while running:
    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            running = False

    screen.fill((15, 15, 20))
    grid = make_grid(boids)

    for b in boids:
        b.update(boids, grid)
        b.draw(screen)

    pygame.display.flip()
    clock.tick(60)

pygame.quit()


