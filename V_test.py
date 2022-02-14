# -*- coding: utf-8 -*-
"""
Created on Sat Feb 12 18:39:00 2022

@author: Muris
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator

#Pruebita del ejercicio de voltaje del Landau

N_iter=1000

Nx = 100
Ny = 100

malla = np.zeros([Nx+1,Ny+1])

#Condiciones de borde

malla[:,0] = 100

for k in range(N_iter): 
    for i in range(1,Nx,1):
        for j in range(1,Ny,1):
            malla[i,j] = (malla[i+1,j]+malla[i-1,j]+malla[i,j+1]+malla[i,j-1])/4 
            
#Grafico
plt.figure(10)
plt.pcolormesh(malla[:,:])
plt.xlabel('y [mm]')
plt.ylabel('z [mm]')
 

plt.show()