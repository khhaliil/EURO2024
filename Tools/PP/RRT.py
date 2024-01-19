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
    obstacles = [[250,325], [375,125], [375,375]]
    pygame.init()
    map = RRTMap(start, goal, dimensions, obsdim,obstacles)
    graph = RRTGraph(start, goal, dimensions, obsdim, obstacles)

    map.drawMap()

    running = True  
    iteration = 0
    while (running and (not graph.path_to_goal())) and iteration < 100:
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

        if iteration % 50 == 0:
            pygame.display.update()
        iteration += 1
    print(iteration)
    smoothed_path_coords = graph.optimize_path()
    map.drawPath(graph.getPathCoords(),smoothed_path_coords)
    pygame.display.update()
    pygame.event.wait(0)
    pygame.quit()  

if __name__ == '__main__':
    main()
