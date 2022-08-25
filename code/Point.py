# -*- coding: utf-8 -*-
"""
Created on Thu Jul 15 12:09:16 2021

@author: gomes
"""

import math
import numpy as np

precisionMC = int(1e3)

class Point:
    
    def __init__(self,x,y,z):
        self.x = x
        self.y = y
        self.z = z
        
    def __add__(self, other):
        return Point(self.x+other.x,
                     self.y+other.y,
                     self.z+other.z)
        
    def __sub__(self, other):
        return Point(self.x-other.x,
                     self.y-other.y,
                     self.z-other.z)
    
    def __neg__(self):
        return Point(-self.x,
                     -self.y,
                     -self.z)
    
    def __str__(self):
        return "({}, {}, {})".format(self.x, self.y, self.z)
    
    def __repr__(self):
        return "Point"+str(self)
    
    @staticmethod
    def dot(p1, p2):
        return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z
    
    @staticmethod
    def cross(p1, p2):
        return Point(p1.y*p2.z-p2.y*p1.z,
                     p1.z*p2.x-p2.z*p1.x,
                     p1.x*p2.y-p2.x*p1.y)

    @staticmethod
    def sphere_dist(p1, p2):
        return np.arccos( Point.dot(p1, p2) )

sdist = Point.sphere_dist
dot = Point.dot
cross = Point.cross
    
def angle_to_point(phi, theta):
    # degree to radians
    phi = (phi/90)*(np.pi/2)
    theta = (theta/180)*(np.pi)
    
    # to coordinates
    x = np.cos(phi)*np.cos(theta)
    y = np.cos(phi)*np.sin(theta)
    z = np.sin(phi)
    
    return Point(x, y, z)


def min_radius(point_list, p):
    aout = 100
    for q in point_list:
        aout = min(aout, sdist(p,q))
    return aout

def solveMC(angle_list):
    point_list = []
    for phi, theta in angle_list:
        point_list.append( angle_to_point(phi, theta) )
    
    maxr = 0
    for _ in range(precisionMC):
        rand_phi = np.random.randint(-90, 90)
        rand_theta = np.random.randint(-180, 180)
        
        trialMC = min_radius(point_list, angle_to_point(rand_phi, rand_theta))
        var = 1
        
        while(trialMC > maxr):
            maxr = trialMC
            rand_phi = rand_phi+np.random.normal(0, var)
            rand_theta = rand_theta+np.random.normal(0, var)
            var = var/2
            
            trialMC = min_radius(point_list, angle_to_point(rand_phi, rand_theta))
    
    return maxr
        
    