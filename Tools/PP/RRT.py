import pygame
from RRTbasePY import RRTGraph 
from RRTbasePY import RRTMap

def main(): 
    dimensions = (750, 500)
    start = (150, 350)
    goal = (600, 200)
    obsdim = 31
    iteration = 0
    obstacles = [[250, 325], [375, 125], [375, 375], [250, 175], [500,175], [500, 325]]
    #obstacles = [[250,325], [375,125], [375,375]]
    pygame.init()
    map = RRTMap(start, goal, dimensions, obsdim)
    graph = RRTGraph(start, goal, dimensions, obsdim, obstacles)

    obstacles = graph.addObstacles(obstacles)
    map.drawMap(obstacles)

    running = True  

    while running and (not graph.path_to_goal()):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                running = False

        if iteration % 10 == 0:
            X, Y, Parent = graph.bias(goal)
            pygame.draw.circle(map.map, map.grey, (X[-1], Y[-1]), map.nodeRad + 2, 0)
            pygame.draw.line(map.map, map.blue, (X[-1], Y[-1]), (X[Parent[-1]], Y[Parent[-1]]), map.edgeThickness)
        else:
            X, Y, Parent = graph.expand()
            pygame.draw.circle(map.map, map.grey, (X[-1], Y[-1]), map.nodeRad + 2, 0)
            pygame.draw.line(map.map, map.blue, (X[-1], Y[-1]), (X[Parent[-1]], Y[Parent[-1]]), map.edgeThickness)

        if iteration % 5 == 0:
            pygame.display.update()
        iteration += 1

    map.draw_Path(graph.getPathCoords()) 
    smoothed_path_coords = graph.optimize_path()
    print(smoothed_path_coords)
    map.draw_smoothed_Path(smoothed_path_coords)
    pygame.display.update()
    pygame.event.wait(0)
    pygame.quit()  

if __name__ == '__main__':
    main()
