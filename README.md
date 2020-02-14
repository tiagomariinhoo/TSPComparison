# TSPComparison

This project is meant to compare two solutions of the Travelling Salesman Problem, one using Bitmask, which is the more commonly used solution, and another using the Particle Swarm Algorithm.

### Running the project
If you want to execute both PSO and Bitmask and also generate plots you'll need to:
- Open a terminal in the main folder of this project (by default it is the folder this file is in)
- Run `pip install -r requirements.txt` to install the needed dependencies 
  - On linux or mac you might need to use `pip3` instead of `pip`
- Run `python main.py` to execute the code
  - On linux or mac you might need to use `python3` instead of `python`

Note that besides python you'll need a C++ compiler to run the code, as both Bitmask and PSO are implemented in C++.

The default compile commands for PSO and Bitmask use the `g++` command to compile the code, if you're using another C++ compiler, you can change the default compile commands in the `main.py` file at the lines `106` and `107`, but always make sure that the compile output is named `main.exe`

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