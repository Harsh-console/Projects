from settings import *
import moderngl as mgl
import pygame as pg
import sys

class VoxelEngine:
    def __init__(self):
        pg.init()
        pg.display.gl_set_attribute(pg.GL_CONTEXT_MAJOR_VERSION, 3)
        pg.display.gl_set_attribute(pg.GL_CONTEXT_MINOR_VERSION, 4)
        pg.display.gl_set_attribute()
        pg.display.gl_set_attribute()
    
    def update(self):
        pass
    
    def render(self):
        pass

    def handle_events(self):
        pass

    def run(self):
        pass

if __name__ == "__main__":
    app = VoxelEngine()
    app.run()
