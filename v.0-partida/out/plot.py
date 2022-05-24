#!/usr/bin/python3.10

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from cycler import cycler
# from mpl_toolkits.mplot3d import Axes3D

plt.rcParams["font.weight"] = "bold"
plt.rcParams["font.size"] = 15
#
plt.rcParams["axes.labelweight"] = "bold"
plt.rcParams["axes.linewidth"] = 2
plt.rcParams["axes.prop_cycle"] = cycler('color', ['tab:orange', 'mediumseagreen', 'm', 'y', 'k'])
#
# plt.rcParams['xtick.major.size'] = 10
# plt.rcParams['xtick.major.width'] = 3
# plt.rcParams['ytick.major.size'] = 10
# plt.rcParams['ytick.major.width'] = 3
#
# plt.rcParams["legend.loc"] = 'best'
plt.rcParams["legend.frameon"] = True
plt.rcParams["legend.fancybox"] = True
plt.rcParams["legend.fontsize"] = 10
plt.rcParams["legend.edgecolor"] = 'black'
#
# plt.rcParams["figure.figsize"] = 12.5, 10
# plt.rcParams["figure.autolayout"] = True
#
# plt.rcParams["lines.linewidth"] = 4
# plt.rcParams["lines.markersize"] = 8
# plt.rcParams["lines.linestyle"] = ':'

def main():

    Dep_init = pd.read_csv("Est0_Dep.csv").to_numpy()
    Lib_init = pd.read_csv("Est0_Lib.csv").to_numpy()
    # Dep_end = pd.read_csv("Est1_Dep.csv").to_numpy()
    # Lib_end =  pd.read_csv("Est1_Lib.csv").to_numpy()

    fig = plt.figure()
    # fig.set_size_inches(6, 6)
    ax = fig.add_subplot(projection='3d')
    ax.scatter(Dep_init[:, 0], Dep_init[:, 1], Dep_init[:, 2], label='Li$^0$')
    ax.scatter(Lib_init[:, 0], Lib_init[:, 1], Lib_init[:, 2], label='Li$^+$')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.legend()#loc='center left', bbox_to_anchor=(1, 0.5), ncol = 1)
    ax.grid(False)
    ax.set_title('Estado Inicial')
    fig.set_size_inches(10, 10)

    # axf.scatter(Lib_end[:, 0], Lib_end[:, 1], label='Li$^+$')
    # axf.scatter(Dep_end[:, 0], Dep_end[:, 1], label='Li$^0$')
    # axf.set_xlabel('x')
    # axf.set_ylabel('y')
    # axf.legend(loc='center left', bbox_to_anchor=(1, 0.5), ncol = 1)
    # axf.set_title('Estado Final')

    plt.savefig('Dendritas')
    plt.show()

if __name__ == "__main__":
    main()
