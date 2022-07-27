#!/usr/bin/python3.10

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from cycler import cycler

plt.rcParams["font.weight"] = "bold"
plt.rcParams["font.size"] = 15

plt.rcParams["axes.labelweight"] = "bold"
plt.rcParams["axes.linewidth"] = 3
# plt.rcParams["axes.prop_cycle"] = cycler('color', ['tab:orange', 'mediumseagreen', 'k'])

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

    fig, (ax1, ax2) = plt.subplots(1, 2)

    ax1.scatter(data[:, 0], data[:, 1], color='coral')
    ax1.errorbar(data[:, 0], data[:, 1], yerr = data[:, 2], capsize=8, color='coral', ecolor='k')
    # ax1.bar(data[:, 0], data[:, 1], yerr = data[:, 2], capsize=8, color='coral', width=200)
    ax1.set_xlabel('NMAX')
    ax1.set_xscale('log')
    ax1.set_ylabel('WALL TIME [min]')

    ax2.scatter(data[:, 0], data[:, 3], color='teal')
    ax2.errorbar(data[:, 0], data[:, 3], yerr = data[:, 4], capsize=8, color='teal',  ecolor='k')
    # ax2.bar(data[:, 0], data[:, 3], yerr = data[:, 4], capsize=8, color='teal', width=200)
    ax2.set_xlabel('NMAX')
    ax2.set_xscale('log')
    ax2.set_ylabel('PFLOPS')

    plt.savefig('Metricas')

if __name__ == "__main__":
    main()
