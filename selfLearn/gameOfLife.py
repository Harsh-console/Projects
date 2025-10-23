import pygame as pg
import numpy as np

#window setup
RES = WIDTH, HEIGHT = 1200, 600
CELL_SIZE = 10
COLS, ROWS = WIDTH // CELL_SIZE, HEIGHT // CELL_SIZE

pg.init()
screen = pg.display.set_mode(RES)
clock  = pg.time.Clock()

# Random Grid : 1 = alive, 0 = dead
grid = np.random.choice([0, 1], size = (ROWS, COLS))


def update(grid):
    new_grid = grid.copy()
    for i in range(ROWS):
        for j in range(COLS):
            # Count alive neighbors
            neighbors = np.sum(grid[max(i - 1, 0) : min(i + 2, ROWS), max(j-1, 0) : min(j+2, COLS)]) - grid[i, j]

            # Rules of Life
            if grid[i, j] == 1 and (neighbors < 2 or neighbors > 3):
                new_grid[i, j] = 0 # dies
            elif grid[i, j] == 0 and neighbors == 3:
                new_grid[i, j] = 1 # new life
    return new_grid

running = True
while running : 
    clock.tick(100)
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

    screen.fill((0, 0, 0))
    for i in range(ROWS):
        for j in range(COLS):
            if grid[i, j] == 1:
                pg.draw.rect(screen, (0, 255, 0), (j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1))
    grid = update(grid)
    pg.display.flip()

pg.quit()
