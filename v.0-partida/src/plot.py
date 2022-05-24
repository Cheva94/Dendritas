#!/usr/bin/python3.10

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from cycler import cycler

plt.rcParams["font.weight"] = "bold"
plt.rcParams["font.size"] = 35

plt.rcParams["axes.labelweight"] = "bold"
plt.rcParams["axes.linewidth"] = 3
plt.rcParams["axes.prop_cycle"] = cycler('color', ['tab:orange', 'mediumseagreen', 'm', 'y', 'k'])

plt.rcParams['xtick.major.size'] = 10
plt.rcParams['xtick.major.width'] = 3
plt.rcParams['ytick.major.size'] = 10
plt.rcParams['ytick.major.width'] = 3

plt.rcParams["legend.loc"] = 'best'
plt.rcParams["legend.frameon"] = True
plt.rcParams["legend.fancybox"] = True
plt.rcParams["legend.fontsize"] = 20
plt.rcParams["legend.edgecolor"] = 'black'

plt.rcParams["figure.figsize"] = 25, 10
plt.rcParams["figure.autolayout"] = True

plt.rcParams["lines.linewidth"] = 4
plt.rcParams["lines.markersize"] = 8
plt.rcParams["lines.linestyle"] = ':'

def main():

    Li0_init = pd.read_csv("Est0_Dep.csv").to_numpy()
    LiM_init = pd.read_csv("Est0_Lib.csv").to_numpy()
    Li0_end = pd.read_csv("Est1_Dep.csv").to_numpy()
    LiM_end =  pd.read_csv("Est1_Lib.csv").to_numpy()

    fig, (axi, axf) = plt.subplots(1,2)

    axi.scatter(LiM_init[:, 0], LiM_init[:, 1], label='Li$^+$', zorder=5)
    axi.scatter(Li0_init[:, 0], Li0_init[:, 1], label='Li$^0$', zorder=0)
    axi.set_xlabel('x')
    axi.set_ylabel('y')
    axi.legend(loc='center left', bbox_to_anchor=(1, 0.5), ncol = 1)
    axi.set_title('Estado Inicial')

    axf.scatter(LiM_end[:, 0], LiM_end[:, 1], label='Li$^+$', zorder=5)
    axf.scatter(Li0_end[:, 0], Li0_end[:, 1], label='Li$^0$', zorder=0)
    axf.set_xlabel('x')
    axf.set_ylabel('y')
    axf.legend(loc='center left', bbox_to_anchor=(1, 0.5), ncol = 1)
    axf.set_title('Estado Final')

    plt.savefig('Dendritas')

if __name__ == "__main__":
    main()
