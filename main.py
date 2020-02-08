from os import walk, system, remove, mkdir, chdir, getcwd, startfile
from json.decoder import JSONDecodeError
import matplotlib.pyplot as plt
from os.path import exists
from timeit import timeit
import networkx as nx
import subprocess
import platform
import json

if not exists("./plots/"):
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
      edge_info[2] = {'weight': edge_info[2], 'color': 'black'}
      edges.append(tuple(edge_info))
  return edges

def prepare_folder(folder_name, compile_command):
  print("Running on folder "+folder_name+": ")
  chdir("./"+folder_name)

  print("  Deleting previous output files")
  if(exists("./output.json")):
    remove("./output.json")
    remove("./main.exe")
  
  print("  Compiling code")
  system(compile_command)
  
  print("  Running executable")
  benchmarks[folder_name] = timeit(lambda: system(".\\main.exe < ../in.txt"), number=1)*1000

  print("  Plotting Graph")
  graph_results(folder_name)

  print()
  chdir("..")

def graph_results(folder_name):
  try:
    remove("../plots/"+folder_name+"'s Path.png")
    new_graph = graph
    with open("./output1.json", "r") as file:
      result = json.loads(file.read())

      for i in range(len(result["chosen_path"])-1):
        edge = (str(result["chosen_path"][i]), str(result["chosen_path"][i+1]))
        new_graph[edge[0]][edge[1]]['color'] = 'green'
      
      edges_to_remove = [(u, v) for u,v in new_graph.edges() if new_graph[u][v]['color'] == 'black']
      new_graph.remove_edges_from(edges_to_remove)

    nx.draw_shell(new_graph, with_labels=True, edge_color='g')
    plt.title(folder_name+"'s best path")
    plt.savefig("../plots/"+folder_name+"'s Path.png")
    plt.clf()
  except (FileNotFoundError, JSONDecodeError) as e:
    print("  Output JSON file not found (this may have happened because the algorithm didn't find an answer to the problem)")

# chdir("./plots/")
# for root, dirs, files in os.walk(getcwd(), topdown=False):
#     for name in files:
#         os.remove(os.path.join(root, name))
#     for name in dirs:
#         os.rmdir(os.path.join(root, name))

default_edges = read_graph("./in.txt")
graph = nx.DiGraph()
graph.add_edges_from(default_edges)
nx.draw(graph, with_labels=True)
plt.savefig("./plots/Default Graph.png")
plt.clf()

prepare_folder("PSO", "g++ main.cpp ./random/random_engine.cpp ./particle/particle.cpp -o main")
prepare_folder("Bitmask", "g++ Main.cpp Bitmask.cpp -o main")

print("Plotting benchmark results")
plt.barh([0, 3], list(benchmarks.values()))
plt.yticks([0, 3], list(benchmarks.keys()))
plt.xlabel("Runtime in miliseconds")
plt.title("Benchmark")
plt.savefig("./plots/Benchmark.png")
plt.clf()
print()
print("Please check the plots in the plots folder")

chdir("./plots")
path = getcwd()
if platform.system() == "Windows":
  startfile(path)
elif platform.system() == "Darwin":
  subprocess.Popen(["open", path])
else:
  subprocess.Popen(["xdg-open", path])
chdir("..")