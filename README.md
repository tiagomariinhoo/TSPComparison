# TSPComparison

This project is meant to compare two solutions of the Travelling Salesman Problem, one using Bitmask, which is the more commonly used solution, and another using the Particle Swarm Algorithm.

### Running the project
If you want to execute both PSO and Bitmask and also generate plots, just run `python main.py` in this main folder.

### Executing only a specific algorithm
To execute only one of them just go to their folders and check their README files

### Editing the input graph
The input can be found and edited in the `in.txt` file. The input works as follows:
- The first line contains two integers, the number of nodes followed by the number of edges for the graph
- The following lines represent each of the edges of your graph, where we have:
  - origin node
  - destination node
  - weight of the edge
