from json import tool
import networkx as nx
import matplotlib.pyplot as plt

# First open the output file containing the graph
outputFile = open('outputFromConvertor.txt', 'r')
fileContent = outputFile.read()
Lines = fileContent.split('\n')

# Create the digraph
def getNodeColor(val):
    if(val==startNode):
        return 'y' if startNode == finalNode else 'r'
    elif(val==finalNode):
        return 'g'
    else:
        return 'b'

startNode = ""
finalNode = ""
graph = nx.DiGraph()
for line in Lines:
    nodeNumbers = line.split(' ')
    if(nodeNumbers.__len__()==3):
        graph.add_edge(nodeNumbers[0], nodeNumbers[1], label=nodeNumbers[2])
    if(nodeNumbers.__len__()==2):
        startNode = nodeNumbers[0]
        finalNode = nodeNumbers[1]

pos = nx.planar_layout(graph)
node_color = [getNodeColor(v) for v in graph]

nx.draw(graph, pos, with_labels=True, node_color=node_color)
nx.draw_networkx_edge_labels(graph,pos,edge_labels=nx.get_edge_attributes(graph,'label'),label_pos=.66)
plt.show()