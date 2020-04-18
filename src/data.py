import numpy as np
from matplotlib import pyplot as plt
import sys
import random

class Data:
    def __init__(self, grid, filename):
        self.lower = -1*grid
        self.upper = grid
        self.density = 2*grid
        self.filename = filename
        self.nodes = []
        self.x = []
        self.y = []
    def createMesh(self):
        x = np.linspace(self.lower, self.upper, self.density)
        y = np.linspace(self.lower, self.upper, self.density)
        self.x, self.y = np.meshgrid(x,y)
    def setElevation(self):
        # randomize elevation
        random_data = np.random.random((self.density, self.density)) 
        # elevation map
        plt.contourf(x_1, y_1, random_data, cmap = 'jet')  
        plt.colorbar() 
        plt.show() 
    def getNodes(self, n):
        i = 0
        while i < n:
            a = random.randrange(self.lower, self.upper)
            b = random.randrange(self.lower, self.upper)
            if [a,b] in self.nodes:
                continue
            self.nodes.append([a,b])
            i += 1
    def writeNodes(self):
        with open(self.filename, "w") as f:
            for node in self.nodes:
                print(node)
                f.write('%d,%d\n' % (node[0],node[1]))
        return

if __name__ == '__main__':
    print(-1*sys.argv[1], sys.argv[2])
    data = Data(int(sys.argv[1]), sys.argv[2])
    data.createMesh()
    data.getNodes(10*data.upper)
    data.writeNodes()
    sys.exit()