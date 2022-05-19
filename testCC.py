#!/usr/bin/python3.10

import numpy as np
import matplotlib.pyplot as plt

# core.h

# def pbcNC(coord, cell_length):
#     # return coord - cell_length * int(2*coord/cell_length)
#     return cell_length * int(2*coord/cell_length) - coord

# def MinIm(coord, cell_length):
#     if (coord <= -0.5 * cell_length):
#         coord += cell_length
#     elif (coord > 0.5 * cell_length):
#         coord -= cell_length
#     return coord

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
        coord = 2-coord
    return coord

def main():
    ex = 0.2
    ey = 0.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

    ex = 0.2
    ey = -0.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

    ex = -0.2
    ey = 0.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

    ex = -0.2
    ey = -0.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

    ex = 1.2
    ey = 1.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

    ex = 0.2
    ey = 1.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

    ex = 1.2
    ey = 0.3

    cModx = ex % 1
    cPBCMx = rbc(ex, 1)
    #cPBCNCx = pbcNC(ex, 1)
    #cMinImx = MinIm(ex, 1)
    cPBCNLx = pbc(ex, 1)

    cMody = ey % 1
    cPBCMy = rbc(ey, 1)
    #cPBCNCy = pbcNC(ey, 1)
    #cMinImy = MinIm(ey, 1)
    cPBCNLy = pbc(ey, 1)

    print(f'>>>>>>> El valor era ({ex:.1f} ; {ey:.1f})')
    print(f'mod =  ({cModx:.1f} ; {cMody:.1f})')
    print(f'rbc = ({cPBCMx:.1f} ; {cPBCMy:.1f})')
    #print(f'PBC N corta = ({#cPBCNCx:.1f} ; {#cPBCNCy:.1f})')
    #print(f'Min Im = ({#cMinImx:.1f} ; {#cMinImy:.1f})')
    print(f'pbc = ({cPBCNLx:.1f} ; {cPBCNLy:.1f})\n\n')

if __name__ == "__main__":
    main()
