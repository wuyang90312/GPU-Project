import csv
import numpy as np
from matplotlib.pyplot import *

class map_generator:
    def __init__(self, num, size):
        # The size of the map and numbers of pts should be defined by user
        self.num = num
        self.size = size
    
    def randm_geo(self):
        # For now, we are using normal distribution to simulate planet geo locations
        mu, sigma = 0, 0.3
        dim = np.random.normal(mu, sigma, self.num)*self.size
        return dim
    
    def randm_mass(self):
        # For now, we are using uniform distribution to simulate planet mass
        mass_l, mass_h = 1, 100
        mass = np.random.uniform(mass_l, mass_h, self.num)
        return mass
    
    def map_gen(self):
        '''
        The map is a 2D map, so it should have 2 random generators on 
        both dimensions.
        Also, the number of pts were already defined in the init
        '''
        # Insert the points into a tuple
        dim = []
        # create random numbers on both dimensions
        dim1 = self.randm_geo()
        dim2 = self.randm_geo()
        mass = self.randm_mass()
        for i in range(self.num):
            dim.append([float(dim1[i]),float(dim2[i]), float(mass[i])])
        
        return dim

def plot_pts(data, num):
    fig = figure(1)
    colors = ["b"]
    for i in range(num):
        scatter(data[i][0], data[i][1], c = colors, alpha = 0.5)
    #show()
    savefig('galaxy')
    close()

num_pt = 50000
mp = map_generator(num_pt, 400)
result = mp.map_gen()
with open("map.csv", "wb") as f:
    writer = csv.writer(f)
    writer.writerows(result)
plot_pts(result, num_pt)

