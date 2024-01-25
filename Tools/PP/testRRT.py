from RRTbasePY import RRTGraph

def find_path_coordinates(prohibited_zone, dimensions=(750, 500), start=(50, 600), goal=(622, 93), obsdim=31, obstacles=[[250, 325], [375, 125], [375, 375], [250, 175], [500,175], [500, 325]] ):
    graph = RRTGraph(start, goal, dimensions, obsdim, obstacles)
    iteration = 0

    while not graph.path_to_goal():
        if iteration % 10 == 0:
            X, Y, Parent = graph.bias(goal)
        else:
            X, Y, Parent = graph.expand()

        iteration += 1

    smoothed_path_coords = graph.optimize_path()
    return smoothed_path_coords

if __name__ == '__main__':
    path_coordinates = find_path_coordinates()
    print("Path Coordinates:", path_coordinates)
