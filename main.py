from os import system, remove, mkdir, chdir, getcwd, walk
from json.decoder import JSONDecodeError
from os.path import exists, join
import matplotlib.pyplot as plt
from timeit import timeit
from copy import deepcopy
import networkx as nx
import subprocess
import platform
import json

default_sizes = plt.rcParams['figure.figsize']
plt.rcParams['figure.figsize'] = list(map(lambda x: x*2, default_sizes))
plt.rcParams['font.size'] = 14

if exists("./plots/"):
  chdir("./plots/")
  for root, dirs, files in walk(getcwd(), topdown=False):
    for name in files:
      remove(join(root, name))
    for name in dirs:
      rmdir(join(root, name))
  chdir("..")
else:
  mkdir("./plots/")

benchmarks = {}

def read_graph(filepath):
  edges = []
  with open(filepath, "r") as file:
    flag = True
    for line in file:
      if flag: # First line contains node and edge count only
        flag = False
        continue

      edge_info = line.rstrip().split()
      edge_info = [int(edge_info[0]), int(edge_info[1]), float(edge_info[2])]
      edge_info[2] = {'weight': edge_info[2], 'color': 'black'}
      edges.append(tuple(edge_info))
  return edges

def prepare_folder(folder_name, compile_command):
  print("Running on folder "+folder_name+": ")
  chdir("./"+folder_name)
  
  print("  Deleting previous output files")
  if exists("./output.json"):
    remove("./output.json")
  
  if exists("./main.exe"):
    remove("./main.exe")
  
  print("  Compiling code")
  system(compile_command)
  
  print("  Running executable")
  if platform.system() == "Windows":
    benchmarks[folder_name] = timeit(lambda: system(".\\main.exe < ../in.txt"), number=1)*1000
  else:
    benchmarks[folder_name] = timeit(lambda: system("./main.exe < ../in.txt"), number=1)*1000

  print("  Plotting Graph")
  graph_results(folder_name)

  print()
  chdir("..")

def graph_results(folder_name):
  try:
    new_graph = deepcopy(graph)
    with open("./output.json", "r") as file:
      result = json.loads(file.read())
      
      edges_to_keep = []
      for i in range(len(result["chosen_path"])-1):
        edge = (result["chosen_path"][i], result["chosen_path"][i+1])
        edges_to_keep.append(edge)
      
      edges_to_remove = [(u, v) for u,v in new_graph.edges() if (u, v) not in edges_to_keep]
      new_graph.remove_edges_from(edges_to_remove)
      plt.title("Path's cost is "+str(result["path_cost"]))
    
    edge_data = {(u, v): new_graph[u][v]['weight'] for u,v in new_graph.edges()}
    nx.draw_networkx(new_graph, with_labels=True, edge_color='g', pos=node_positions)
    nx.draw_networkx_edge_labels(new_graph, node_positions, edge_labels=edge_data, label_pos=0.2)
    plt.savefig("../plots/"+folder_name+"'s Path.png", bbox_inches='tight')
    plt.clf()
  except (FileNotFoundError, JSONDecodeError) as e:
    print("  Invalid output.json file (this may have happened because the algorithm could not find an answer to the problem)")

default_edges = read_graph("./in.txt")
graph = nx.DiGraph()
graph.add_edges_from(default_edges)

node_positions = nx.circular_layout(graph)
edge_data = {(u, v): graph[u][v]['weight'] for u,v in graph.edges()}

nx.draw_networkx(graph, with_labels=True, pos=node_positions)
nx.draw_networkx_edge_labels(graph, node_positions, edge_labels=edge_data, label_pos=0.2)
plt.title("Weights are drawn near the edge's destination node")
plt.savefig("./plots/Default Graph.png", bbox_inches='tight')
plt.clf()

prepare_folder("Bitmask", "g++ Main.cpp Bitmask.cpp -o main.exe")
prepare_folder("PSO", "g++ main.cpp ./random/random_engine.cpp ./particle/particle.cpp -o main.exe")

print("Plotting benchmark results")
plt.barh([0, 3], list(benchmarks.values()))
plt.yticks([0, 3], list(benchmarks.keys()))
plt.xlabel("Runtime in miliseconds")
plt.title("Benchmark")
plt.savefig("./plots/Benchmark.png", bbox_inches='tight')
plt.clf()

chdir("./plots")
path = getcwd()
try:
  if platform.system() == "Windows":
    from os import startfile
    startfile(path)
  elif platform.system() == "Darwin":
    subprocess.Popen(["open", path])
  else:
    subprocess.Popen(["xdg-open", path])
except Exception:
  print()
  print("Please check the plots in the plots folder")
chdir("..")