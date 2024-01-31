import random

V = 5000  # Number of vertices
max_weight = 100  # Maximum weight for edges

# Generate a random graph as a 2D matrix
graph = [[0 if i == j else random.randint(1, max_weight) for j in range(V)] for i in range(V)]

# Write the graph to the file
with open("graph.txt", "w") as file:
    for row in graph:
        file.write(" ".join(map(str, row)) + "\n")

print("Graph with 5000 vertices has been generated and saved to graph.txt.")