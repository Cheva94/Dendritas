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

plt.rcParams["figure.figsize"] = 12.5, 10
plt.rcParams["figure.autolayout"] = True

plt.rcParams["lines.linewidth"] = 1
plt.rcParams["lines.markersize"] = 10
plt.rcParams["lines.linestyle"] = ':'

def main():

    L = ['nT=28', 'nT=21', 'nT=14', 'nT=7', 'nT=1']

    data = pd.read_csv("Aceleracion.txt").to_numpy()
    NMAX = data[:, 0]

    fig, ax = plt.subplots()

    for k in range(len(L)-1):
        ax.scatter(NMAX, data[:, 2*k+1], label=L[k])
        ax.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8)

    ax.set_xlabel('NMAX')
    ax.set_ylabel(r'$S_P$')
    ax.legend()

    plt.savefig('Aceleracion')

    data = pd.read_csv("Eficiencia.txt").to_numpy()

    fig, ax = plt.subplots()

    ax.axhline(y=0.6, color='gray', ls=':', lw=3)

    for k in range(len(L)-1):
        ax.scatter(NMAX, data[:, 2*k+1], label=L[k])
        ax.errorbar(NMAX, data[:, 2*k+1], yerr = data[:, 2*k+2], capsize=8)

    ax.set_xlabel('NMAX')
    ax.set_ylim(0.2, 0.9)
    ax.set_ylabel(r'$\epsilon$')
    ax.legend()

    plt.savefig('Eficiencia')

if __name__ == "__main__":
    main()
