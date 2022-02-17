#-*- coding: utf-8 -*-
"""
Created on Mon Feb 14 10:03:43 2022

@author: Muri
"""

import numpy as np 
import matplotlib.pyplot as plt


# Inicialización de variables

dt = 1e-6
n0 = 77     #comienzo con este numero de li0 depositados sobre la sup
n0max = 600 #numero maximo de particulas li0
rli0 = 1.67e-10  #radio atomico del li0
rlim = 1.2e-10   #radio atomico del li+
nm = 50          #Este numero debe mantenerse a lo largo de la ev temporal
D = 1.4e-14      #coef de dif del Li+ en el electrolito
tita = 0
gx = 0
gy = 0
x=0
y=0
Long = 16.7e-9
datt = 1.3*rli0/Long     #que es rli0/(pi/4)
q = np.sqrt(2*D*dt)/Long   #desplazamiento medio debido a la difusion

alfa = 0
mod_li0 = 0

Rli_mx = 0
Rli_my = 0
Rli_0x = 0
Rli_0y = 0
modd = 0

u = 5.6e-13

#Variables de la malla de voltaje y campo
N_iter = 1000
nmalla = 100
dx = Long/(nmalla*Long)
dy = Long/(nmalla*Long)

#Defino y calculo el voltaje V0
Vm = 10 #Volts
V0 = np.zeros([nmalla+1,nmalla+1])
V =  np.zeros([nmalla+1,nmalla+1])

V0[:,0] = Vm #Condición de borde

for k in range(N_iter): 
    for i in range(1,nmalla,1):
        for j in range(1,nmalla,1):
            V0[i,j] = (V0[i+1,j]+V0[i-1,j]+V0[i,j+1]+V0[i,j-1])/4
            
#Defino y Calculo el campo E0
E0_x = np.zeros([nmalla+1,nmalla+1])
E0_y = np.zeros([nmalla+1,nmalla+1])
E_x = np.zeros([nmalla+1,nmalla+1])
E_y = np.zeros([nmalla+1,nmalla+1])

for j in range(0,nmalla+1,1):
    for i in range(1,nmalla,1):
        E0_x[i,j] = -(V0[i+1,j]-V0[i-1,j])/dx
     
for j in range(0,nmalla+1,1): #Defino el campo en x respetando las PBC 
    E0_x[0,j] = -(V0[1,j]-V0[nmalla,j])/dx
    E0_x[nmalla,j] = - (V0[0,j]-V0[nmalla-1,j])/dx
    
for j in range(1,nmalla,1):
    for i in range(0,nmalla+1,1):
        E0_y[i,0] = -V0[i,1]/dy
        E0_y[i,j] = -(V0[i,j+1]-V0[i,j-1])/dy
        E0_y[i,nmalla] = V0[i,nmalla-1]/dy
        

#Inicialización de vectores 
ex = np.zeros(nm)
ey = np.zeros(nm)
ex_0 = np.zeros(nm)
ey_0 = np.zeros(nm)
lix_d = np.zeros(n0)
liy_d = np.zeros(n0)
lix_aux = np.zeros(n0max)
liy_aux = np.zeros(n0max)

#Creación de la monocapa de Li0 depositado

for i in range(n0):
    lix_d[i] = 1.3*rli0*i/Long
    liy_d[i] = 0/Long

#Creación de las posiciones iniciales de los iones

dx = rli0/(2*Long)
dy = rli0/(2*Long)

for i in range(nm):
    ex_0[i] = np.random.rand()
    ey_0[i] = np.random.rand()
    ex_0[i] = ex_0[i] % 1
    if (ey_0[i]<0):
        ey_0[i] = abs(ey_0[i])
    elif (ey_0[i]>1):
        ey_0[i] = 1-ey_0[i]
    

#Guardo las coordenadas del sistema inicial
ex_init = ex_0
ey_init = ey_0
 
#Calculo los vectores rx y ry

rx = np.zeros(nm)
ry = np.zeros(nm)

indices = [] #Me guardo los indices que entran

#Bueno empiezo a escribir a ver kionda
Rcut = 0.007 #1/100 (escala de las separaciones)/2*raiz(2)
Rcut2 = Rcut*Rcut

for i in range(nm):
    for j in range(nmalla+1):
        for k in range(nmalla+1):
            d1 = ex_0[i] - j*0.01
            d2 = ey_0[i] - k*0.01
            dist2 = d1*d1 + d2*d2
            div = 1
            if dist2<=Rcut2:
                indices.append((j,k))
                div = div+1
                rx[i] = u*E0_x[j,k]*dt/(Long*div)
                ry[i] = u*E0_x[j,k]*dt/(Long*div)
                

#mu+*E*dt/Long es el desplazamiento debido al campo electrico

        
#Comienza el loop de evolución temporal


m = n0      #Número inicial de Li0
nt = 8000   #Número de pasos temporales


#Inicialmente los vectores de Li0 son iguales al litio depositado
lix_0 = lix_d
liy_0 = liy_d


lix_aux = np.zeros(n0max)
liy_aux = np.zeros(n0max)

porcent = 9 #Porcentaje inicial para el contador

exys = []

for i in range(nt):
    break_out_of_i = False
    for j in range(nm):
        break_out_of_j = False
        tita = 2*np.pi*np.random.rand()
        #Definición del vector unitario g
        gx = np.cos(tita)
        gy = np.sin(tita)
        #Evolución de la posición de los iones
        ex[j] = ex_0[j] + q*gx + rx[j]
        ey[j] = ey_0[j] + q*gy + ry[j]
        #Meto las PBC en la caja de tamaño 1x1 (normalizada)
        ex[j] = ex[j] % 1
        if (ey[j]<0):
            ey[j] = abs(ey[j])
        elif (ey[j]>1):
            ey[j] = 2-ey[j]
    
        #Definición de la condición Li+-->Li0
        for k in range(m):
            if (m<=n0):
                distx = ex[j] - lix_d[k]
                disty = ey[j] - liy_d[k]
                dist = np.sqrt(distx*distx + disty*disty)
            elif (m>n0):
                distx = ex[j] - lix_0[k]
                disty = ey[j] - liy_0[k]
                dist = np.sqrt(distx*distx + disty*disty)
                
            if (dist<datt):
                if (m<=n0):
                    modd = np.sqrt((ex[j] - lix_d[k])*(ex[j] - lix_d[k]) + (ey[j] - liy_d[k])*(ey[j] - liy_d[k]))
                    exs = (ex[j]-lix_d[k])*datt/modd + lix_d[k]
                    eys = (ey[j]-liy_d[k])*datt/modd + liy_d[k]
                elif (m>n0):
                    modd = np.sqrt((ex[j] - lix_0[k])*(ex[j] - lix_0[k]) + (ey[j] - liy_0[k])*(ey[j] - liy_0[k]))
                    exs = (ex[j]-lix_0[k])*datt/modd + lix_0[k]
                    eys = (ey[j]-liy_0[k])*datt/modd + liy_0[k]
                
                exys.append([exs,eys])
                m = m+1
                if (m==n0max):
                    break_out_of_i = True
                    break_out_of_j = True
                    print('Se alcanzó la cantidad máxima de Li0')
                    break
                lix_0 = np.zeros(m)
                liy_0 = np.zeros(m)
                for l in range(n0):
                    lix_aux[l] = lix_d[l]
                    liy_aux[l] = liy_d[l]
                    
                lix_aux[m] = exs
                liy_aux[m] = eys
                
                for l in range(m):
                    lix_0[l] = lix_aux[l]
                    liy_0[l] = liy_aux[l]
                    
                #PBC
                for l in range(m):
                    lix_0[l] = lix_0[l] % 1
                    if (liy_0[l]<0):
                        liy_0[l] = abs(liy_0[l])
                    elif (liy_0[l]>1):
                        liy_0[l] = 2-liy_0[l]
                #Repongo el ion
                ex[j] = np.random.rand()
                ey[j] = np.random.rand()
                #Las PBC
                ex[j] = ex[j] % 1
                if (ey[j]<0):
                    ey[j] = abs(ey[j])
                elif (ey[j]>1):
                    ey[j] = 2-ey[j]
        if break_out_of_j: break
                
    t = (i+1)*dt
    ex_0 = ex
    ey_0 = ey
    #Agrego el pocentaje de corrida del programa
    ip = int((i/nt)*100)
    if (ip > porcent):
        if (ip % 10 == 0):
            print(ip,'%')
        porcent = ip
    if break_out_of_i: break
    
print('Cantidad de Li0 =', m)
              
#%%  
         
#Gráfico del sistema inicial

plt.figure(10)
x = ex_init
f = ey_init
y = lix_d
g = liy_d
ax = plt.subplot(111)
ax.plot(x,f,linestyle='', marker='.', markersize=7,color='#1f77b4', label=' Li$^+$')
ax.plot(y,g,linestyle='', marker='.', markersize=7,color='#d62728', label=' Li$^0$')
plt.ylim([-0.05,1.05])
plt.xlabel('x')
plt.ylabel('y')
plt.title(' init ')
ax.legend()      
ax.set_aspect('equal', adjustable='box')

#Gráfico del sistema final
        
plt.figure(20)
x = ex
f = ey
y = lix_0
g = liy_0
ax = plt.subplot(111)
ax.plot(x,f,linestyle='', marker='.', markersize=7,color='#1f77b4', label=' Li$^+$')
ax.plot(y,g,linestyle='', marker='.', markersize=7,color='#d62728', label=' Li$^0$')
plt.ylim([-0.05,1.05])
plt.xlabel('x')
plt.ylabel('y')
plt.title(' ')
ax.legend()
ax.set_aspect('equal', adjustable='box')


plt.show()