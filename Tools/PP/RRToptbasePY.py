import numpy as np
import matplotlib.pyplot as plt

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.parent = None
        self.cost = 0.0

def distance(node1, node2):
    return np.sqrt((node1.x - node2.x)**2 + (node1.y - node2.y)**2)

def generate_random_node(x_max, y_max):
    return Node(np.random.uniform(0, x_max), np.random.uniform(0, y_max))

def nearest_node(nodes, random_node):
    distances = [distance(node, random_node) for node in nodes]
    return nodes[np.argmin(distances)]

def steer(node, random_node, max_step_size):
    d = distance(node, random_node)
    if d < max_step_size:
        return random_node
    else:
        scale = max_step_size / d
        return Node(node.x + (random_node.x - node.x) * scale, node.y + (random_node.y - node.y) * scale)

def is_collision_free(node, obstacles):
    # Simple collision check, replace with your collision detection logic
    return True

def rrt_star(start, goal, x_max, y_max, max_iterations=500, max_step_size=5.0):
    nodes = [start]

    for _ in range(max_iterations):
        random_node = generate_random_node(x_max, y_max)
        nearest = nearest_node(nodes, random_node)
        new_node = steer(nearest, random_node, max_step_size)

        if is_collision_free(new_node, obstacles):
            near_nodes = [node for node in nodes if distance(node, new_node) < max_step_size]
            min_cost_node = nearest
            min_cost = nearest.cost + distance(nearest, new_node)

            for near_node in near_nodes:
                cost = near_node.cost + distance(near_node, new_node)
                if cost < min_cost and is_collision_free(near_node, obstacles):
                    min_cost = cost
                    min_cost_node = near_node

            new_node.parent = min_cost_node
            new_node.cost = min_cost
            nodes.append(new_node)

    return nodes

def visualize_rrt(nodes, start, goal, obstacles):
    plt.scatter([node.x for node in nodes], [node.y for node in nodes], color='blue', s=5, label='RRT Nodes')
    plt.scatter(start.x, start.y, color='green', marker='o', label='Start')
    plt.scatter(goal.x, goal.y, color='red', marker='o', label='Goal')
    
    for node in nodes:
        if node.parent:
            plt.plot([node.x, node.parent.x], [node.y, node.parent.y], color='blue', linewidth=0.5)

    plt.legend()
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('RRT* Path Planning')
    plt.show()

# Example usage:
start_node = Node(10, 10)
goal_node = Node(90, 90)
obstacles = []  # Add your obstacles here

rrt_nodes = rrt_star(start_node, goal_node, 100, 100)
visualize_rrt(rrt_nodes, start_node, goal_node, obstacles)
