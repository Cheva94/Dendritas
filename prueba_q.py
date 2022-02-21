# -*- coding: utf-8 -*-
"""
Created on Mon Feb 21 10:39:43 2022

@author: Muri
"""
import numpy as np

#progamita de prueba para los q

lista = []

for i in range(100):
    eys = np.random.rand()
    q0 = int(eys*100)
    q = q0 + (100-2*q0) -1
    lista.append([eys,q0,q]) 