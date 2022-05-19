#!/usr/bin/python3.10

import numpy as np
import matplotlib.pyplot as plt

# core.h

def pbc(coord, cell_length): # se puede hacer con la función módulo - ver dps la performance
    if (coord < 0):
        coord += cell_length
    elif (coord > cell_length):
        coord -= cell_length
    return coord

def rbc(coord, cell_length):
    if (coord < 0):
        coord = abs(coord)
    elif (coord > cell_length):
        coord = 2 * cell_length - coord
    return coord

def main():
    # params.h

    dt = 1e-6
    nt = 8000   #Número de pasos temporales
    n0 = 5 #77     #comienzo con este numero de li0 depositados sobre la sup
    nm = 10 #50          #Este numero debe mantenerse a lo largo de la ev temporal
    n0max = 600 #numero maximo de particulas li0
    rli0 = 1.67e-10  #radio atomico del li0
    rlim = 1.2e-10   #radio atomico del li+
    d = 1.4e-14      #coef de dif del Li+ en el electrolito
    long = 16.7e-9
    datt = 1.3*rli0/long     #que es rli0/(pi/4)
    q = np.sqrt(2*d*dt)/long   #desplazamiento medio debido a la difusion
    mu = 5.6e-13
    e0_x = 0
    e0_y = -1.7e7
    rx = mu*e0_x*dt/long
    ry = mu*e0_y*dt/long #mu+*E*dt/long es el desplazamiento debido al campo electrico
    seed = np.random.default_rng(2022)

    #dendritas.c

    tita = 0
    gx = 0
    gy = 0
    modd = 0

    #Inicialización de vectores
    ex = np.zeros(nm)
    ey = np.zeros(nm)
    ex_0 = np.zeros(nm)
    ey_0 = np.zeros(nm)

    lix_d = np.zeros(n0)
    liy_d = np.zeros(n0)
    lix_aux = np.zeros(n0max)
    liy_aux = np.zeros(n0max)

    #Inicialmente los vectores de Li0 son iguales al litio depositado
    lix_0 = lix_d
    liy_0 = liy_d

    #Creación de la monocapa de Li0 depositado

    for i in range(n0):
        lix_d[i] = 1.3*rli0*i/long
        liy_d[i] = 0/long

    #Creación de las posiciones iniciales de los iones

    for i in range(nm):
        ex_0[i] = seed.random()
        ey_0[i] = seed.random()

    #Guardo las coordenadas del sistema inicial
    ex_init = ex_0
    ey_init = ey_0

    #Comienza el loop de evolución temporal

    Li0_counter = n0      #Número inicial de Li0

    lix_aux = np.zeros(n0max)
    liy_aux = np.zeros(n0max)

    porcent = 9 #Porcentaje inicial para el contador

    for i in range(nt):
        break_out_of_i = False
        for j in range(nm):
            break_out_of_j = False
            #definición del vector unitario g
            tita = 2*np.pi*seed.random()
            gx = np.cos(tita)
            gy = np.sin(tita)
            #Evolución de la posición de los iones
            ex[j] = ex_0[j] + q*gx + rx
            ey[j] = ey_0[j] + q*gy + ry

            # Meto las PBC en la caja de tamaño 1x1 (normalizada)
            ex[j] = pbc(ex[j], 1)
            ey[j] = rbc(ey[j], 1)

            #definición de la condición Li+-->Li0
            for k in range(Li0_counter):
                if (Li0_counter<=n0):
                    distx = ex[j] - lix_d[k]
                    disty = ey[j] - liy_d[k]
                    dist = np.sqrt(distx*distx + disty*disty)
                elif (Li0_counter>n0):
                    distx = ex[j] - lix_0[k]
                    disty = ey[j] - liy_0[k]
                    dist = np.sqrt(distx*distx + disty*disty)

                if (dist<datt):
                    if (Li0_counter<=n0):
                        modd = np.sqrt((ex[j] - lix_d[k])*(ex[j] - lix_d[k]) + (ey[j] - liy_d[k])*(ey[j] - liy_d[k]))
                        exs = (ex[j]-lix_d[k])*datt/modd + lix_d[k]
                        eys = (ey[j]-liy_d[k])*datt/modd + liy_d[k]
                    elif (Li0_counter>n0):
                        modd = np.sqrt((ex[j] - lix_0[k])*(ex[j] - lix_0[k]) + (ey[j] - liy_0[k])*(ey[j] - liy_0[k]))
                        exs = (ex[j]-lix_0[k])*datt/modd + lix_0[k]
                        eys = (ey[j]-liy_0[k])*datt/modd + liy_0[k]

                    Li0_counter += 1
                    if (Li0_counter==600):
                        break_out_of_i = True
                        break_out_of_j = True
                        print('Se alcanzó la cantidad máxima de Li0')
                        break
                    lix_0 = np.zeros(Li0_counter)
                    liy_0 = np.zeros(Li0_counter)
                    for l in range(n0):
                        lix_aux[l] = lix_d[l]
                        liy_aux[l] = liy_d[l]

                    lix_aux[Li0_counter] = exs
                    liy_aux[Li0_counter] = eys

                    for l in range(Li0_counter):
                        lix_0[l] = lix_aux[l]
                        liy_0[l] = liy_aux[l]

                    #PBC
                    for l in range(Li0_counter):
                        lix_0[l] = pbc(lix_0[l], 1)
                        liy_0[l] = rbc(liy_0[l], 1)
                    #Repongo el ion
                    ex[j] = seed.random()
                    ey[j] = seed.random()
                    #Las PBC
                    ex[j] = pbc(ex[j], 1)
                    ey[j] = rbc(ey[j], 1)

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

    print('Cantidad de Li0 =', Li0_counter)

    #%%

    fig, (axi, axf) = plt.subplots(1,2)

    #Gráfico del sistema inicial

    x = ex_init
    f = ey_init
    y = lix_d
    g = liy_d
    axi.plot(x,f,linestyle='', marker='.', markersize=7,color='#1f77b4', label=' Li$^+$')
    axi.plot(y,g,linestyle='', marker='.', markersize=7,color='#d62728', label=' Li$^0$')
    axi.set_ylim([-0.05,1.05])
    axi.set_xlabel('x')
    axi.set_ylabel('y')
    axi.set_title(' init ')
    axi.legend()

    #Gráfico del sistema final

    x = ex
    f = ey
    y = lix_0
    g = liy_0
    axf.plot(x,f,linestyle='', marker='.', markersize=7,color='#1f77b4', label=' Li$^+$')
    axf.plot(y,g,linestyle='', marker='.', markersize=7,color='#d62728', label=' Li$^0$')
    axf.set_ylim([-0.05,1.05])
    axf.set_xlabel('x')
    axf.set_ylabel('y')
    axf.set_title(' end ')
    axf.legend()

    plt.savefig('muri')

if __name__ == "__main__":
    main()
