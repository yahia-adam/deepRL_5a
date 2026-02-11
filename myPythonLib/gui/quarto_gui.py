import pygame

# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True
WINDOW_HEIGHT = 400
WINDOW_WIDTH = 400
BLACK = (0, 0, 0)
WHITE = (200, 200, 200)

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")
    

    # Source - https://stackoverflow.com/a/33963521
    # Posted by furas, modified by community. See post 'Timeline' for change history
    # Retrieved 2026-02-11, License - CC BY-SA 4.0


    for y in range(height):
        for x in range(width):
            rect = pygame.Rect(x*block_size, y*block_size, block_size, block_size)
            pygame.draw.rect(window, color, rect)

    # RENDER YOUR GAME HERE

    # flip() the display to put your work on screen
    pygame.display.flip()

    clock.tick(60)  # limits FPS to 60

pygame.quit()