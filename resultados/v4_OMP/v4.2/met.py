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

    L1 = ['nT=28', 'nT=21', 'nT=14', 'nT=7', 'nT=1', 'AoS']

    data = pd.read_csv("MetricasPromediadas_WALL.txt").to_numpy()
    NMAX = data[:, 0]

    fig, (ax1, ax2) = plt.subplots(1, 2)

    for k in range(len(L1)):
        ax1.scatter(NMAX, data[:, 2*k+1], label=L1[k])
        ax1.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8, ecolor='k')

    ax1.set_xlabel('NMAX')
    ax1.set_ylabel('WALL TIME [min]')
    ax1.legend()

    for k in range(len(L1)-2):
        ax2.scatter(NMAX, data[:, 2*k+1], label=L1[k])
        ax2.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8, ecolor='k')

    ax2.set_xlabel('NMAX')
    ax2.set_ylabel('WALL TIME [min]')
    ax2.legend()

    plt.savefig('Metricas_WALL')

    data = pd.read_csv("MetricasPromediadas_FLOP.txt").to_numpy()

    fig, (ax1, ax2) = plt.subplots(1, 2)

    for k in range(len(L1)):
        ax1.scatter(NMAX, data[:, 2*k+1], label=L1[k])
        ax1.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8, ecolor='k')

    ax1.set_xlabel('NMAX')
    ax1.set_ylabel('PFLOPS')
    ax1.legend()

    for k in range(len(L1)-2):
        ax2.scatter(NMAX, data[:, 2*k+1], label=L1[k])
        ax2.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8, ecolor='k')

    ax2.set_xlabel('NMAX')
    ax2.set_ylabel('PFLOPS')
    ax2.legend()

    plt.savefig('Metricas_FLOP')

    data = pd.read_csv("MetricasPromediadas_tSim.txt").to_numpy()

    fig, (ax1, ax2) = plt.subplots(1, 2)

    for k in range(len(L1)):
        ax1.scatter(NMAX, data[:, 2*k+1], label=L1[k])
        ax1.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8, ecolor='k')

    ax1.set_xlabel('NMAX')
    ax1.set_ylabel('tSim [ms]')
    ax1.legend()

    for k in range(len(L1)-2):
        ax2.scatter(NMAX, data[:, 2*k+1], label=L1[k])
        ax2.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8, ecolor='k')

    ax2.set_xlabel('NMAX')
    ax2.set_ylabel('tSim [ms]')
    ax2.legend()

    plt.savefig('Metricas_tSim')

if __name__ == "__main__":
    main()
