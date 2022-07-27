#!/usr/bin/python3.10

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from cycler import cycler

plt.rcParams["font.weight"] = "bold"
plt.rcParams["font.size"] = 15

plt.rcParams["axes.labelweight"] = "bold"
plt.rcParams["axes.linewidth"] = 3

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

plt.rcParams["lines.linewidth"] = 1
plt.rcParams["lines.markersize"] = 10
plt.rcParams["lines.linestyle"] = ':'

def main():

    data = pd.read_csv("MetricasPromediadas.txt").to_numpy()
    NMAX = data[:, 0]

    fig, (ax1, ax2) = plt.subplots(1, 2)

    ax1.scatter(NMAX, data[:, 1], color='coral', marker='o', label='SoA')
    ax1.errorbar(NMAX, data[:, 1], yerr = data[:, 2], capsize=8, color='coral', ecolor='k')
    ax1.scatter(NMAX, data[:, 5], color='coral', marker='v', label='AoS')
    ax1.errorbar(NMAX, data[:, 5], yerr = data[:, 6], capsize=8, color='coral', ecolor='k')
    ax1.set_xlabel('NMAX')
    ax1.set_ylabel('WALL TIME [min]')
    ax1.legend()

    ax2.scatter(NMAX, data[:, 3], color='teal', marker='o', label='SoA')
    ax2.errorbar(NMAX, data[:, 3], yerr = data[:, 4], capsize=8, color='teal',  ecolor='k')
    ax2.scatter(NMAX, data[:, 7], color='teal', marker='v', label='AoS')
    ax2.errorbar(NMAX, data[:, 7], yerr = data[:, 8], capsize=8, color='teal',  ecolor='k')
    ax2.set_xlabel('NMAX')
    ax2.set_ylabel('PFLOPS')
    ax2.legend()

    plt.savefig('Metricas')

if __name__ == "__main__":
    main()
