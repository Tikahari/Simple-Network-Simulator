import numpy as np
from matplotlib import pyplot as plt
import sys
import random
import math

class Data:
    def __init__(self, grid, filename):
        self.lower = grid
        self.upper = 2*grid
        self.filename = filename
        self.nodes = []
        self.x = []
        self.y = []
        self.z = []
    def createMesh(self):
        x = np.linspace(self.lower, self.upper, self.upper)
        y = np.linspace(self.lower, self.upper, self.upper)
        self.x, self.y = np.meshgrid(x,y)
    def setElevation(self):
        # randomize elevation
        self.z = np.random.random((self.upper, self.upper))
        # print(self.z)
    def plotElevation(self):
        # elevation map
        plt.contourf(self.x, self.y, self.z, cmap = 'jet')  
        plt.colorbar() 
        plt.show() 
    def getNodes(self, n):
        i = 0
        while i < n:
            a = random.randrange(self.lower, self.upper)
            b = random.randrange(self.lower, self.upper)
            if [a,b] in self.nodes:
                continue
            self.nodes.append([a,b,self.z[a][b]])
            i += 1
    def writeNodes(self):
        with open(self.filename, "w") as f:
            for node in self.nodes:
                # print(node)
                f.write('%d %d %d\n' % (node[0],node[1],node[2]*self.lower))
    def writeGridVal(self):
        with open("./data/gridval.txt", "w") as f:
            f.write(str(self.upper))
if __name__ == '__main__':
    data = Data(int(sys.argv[1]), "./data/nodes.txt")
    data.createMesh()
    data.setElevation()
    data.getNodes(math.floor(data.upper/2))
    data.writeNodes()
    data.writeGridVal()