import pygame
import random
import math
import sys

# Initialize Pygame
pygame.init()
screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))
clock = pygame.time.Clock()

# Define parameters and obstacles
obstacles = [(150, 100), (260, 220)]
start_pos = (50, 50)
goal_pos = (510, 510)
safety_distance = 20


class RRT:
    def __init__(self, start_pos, goal_pos, obstacles, safety_distance):
        self.start_pos = start_pos
        self.goal_pos = goal_pos
        self.obstacles = obstacles
        self.safety_distance = safety_distance
        self.nodes = [start_pos]  # List of nodes in the RRT
        self.path = None  # Stores the final path (if found)

    def sample_point(self):
        if random.random() < 0.8:  # 80% chance for random point
            return (random.uniform(0, screen_width), random.uniform(0, screen_height))
        else:  # 20% chance for goal bias
            return self.goal_pos

    def nearest_neighbor(self, point):
        nearest_node = self.nodes[0]
        nearest_dist = math.inf
        for node in self.nodes:
            dist = math.hypot(point[0] - node[0], point[1] - node[1])
            if dist < nearest_dist:
                nearest_node = node
                nearest_dist = dist
        return nearest_node

    def extend(self, nearest_node, sampled_point):
        step_size = 10
        new_node = (
            nearest_node[0] + step_size * (sampled_point[0] - nearest_node[0]) / math.hypot(
                sampled_point[0] - nearest_node[0], sampled_point[1] - nearest_node[1]
            ),
            nearest_node[1] + step_size * (sampled_point[1] - nearest_node[1]) / math.hypot(
                sampled_point[0] - nearest_node[0], sampled_point[1] - nearest_node[1]
            ),
        )

        if not self.check_collision(nearest_node, new_node):
            self.nodes.append(new_node)
            return True
        else:
            return False

    def check_collision(self, node1, node2):
        for obstacle in self.obstacles:
            if math.hypot(node1[0] - obstacle[0], node1[1] - obstacle[1]) < self.safety_distance:
                return True
            if math.hypot(node2[0] - obstacle[0], node2[1] - obstacle[1]) < self.safety_distance:
                return True
        return False  # No collision detected


def draw_rrt(rrt):
    screen.fill((255, 255, 255))  # Clear the screen

    for obstacle in obstacles:
        pygame.draw.circle(screen, (0, 0, 0), obstacle, safety_distance)

    for node in rrt.nodes:
        pygame.draw.circle(screen, (128, 128, 128), (int(node[0]), int(node[1])), 5)  # Gray for nodes
        
    if rrt.path:  # Draw edges if path found
        for i in range(len(rrt.path) - 1):
            pygame.draw.line(screen, (0, 255, 0), rrt.path[i], rrt.path[i + 1], 10)  # Green for path    

    pygame.draw.circle(screen, (255, 0, 0), start_pos, 10)  # Red for start
    pygame.draw.circle(screen, (0, 0, 255), goal_pos, 10)  # Blue for goal


def main():
    rrt = RRT(start_pos, goal_pos, obstacles, safety_distance)
    path_found = False

    while not path_found:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        new_node = rrt.sample_point()
        nearest_node = rrt.nearest_neighbor(new_node)

        if rrt.extend(nearest_node, new_node):
            if new_node == goal_pos:
                path_found = True
        
        draw_rrt(rrt)
        pygame.display.flip()
        pygame.display.update()
        clock.tick(60)  # Adjust the frame rate


if __name__ == "__main__":
    main()
