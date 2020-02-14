# TSPComparison

This project is meant to compare two solutions of the Travelling Salesman Problem, one using Bitmask, which is the more commonly used solution, and another using the Particle Swarm Algorithm.

### Running the project
If you want to execute both PSO and Bitmask and also generate plots you'll need to:
- Open a terminal in the main folder of this project (by default it is the folder this file is in)
- Run `pip install -r requirements.txt` to install the needed dependencies 
  - On linux or mac you might need to use `pip3` instead of `pip`
- Run `python main.py` to execute the code
  - On linux or mac you might need to use `python3` instead of `python`

### Executing only a specific algorithm
To execute only one of them just go to their folders and check their `README.md` files

### Editing the input graph
The input can be found and edited in the `in.txt` file. The input works as follows:
- The first line contains two integers, the number of nodes followed by the number of edges for the graph
- Each line after that represents one of the edges of your graph, where we have:
  - origin node
  - destination node
  - weight of the edge
- Note that nodes are named from 0 to n-1, where n is your number of nodes