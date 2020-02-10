#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jan 30 15:17:36 2020

@author: chiron
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def func(x,a,mu,sigma):
    return a*np.exp(-(x-mu)**2/(2*sigma**2))

d = np.genfromtxt('/home/chiron/Downloads/tmp/mc1_thermo.txt', unpack=True)

npt_to_exclude = 5000

hist, bin_edges = np.histogram(d[2][npt_to_exclude:], density=True, bins=40)
bin_edges = 0.5*(bin_edges[1:]+bin_edges[:-1])

X_mean = np.mean(d[2][npt_to_exclude:])
X_std = np.std(d[2][npt_to_exclude:])
print(X_mean, X_std)

fig = plt.figure(figsize=(8,10))
axs = fig.subplots(2,1, gridspec_kw={'height_ratios':[0.4,0.6], 'hspace':0.25})

axs[0].set_title('Timeseries of X at T=0.02', color='blue')
axs[0].set_xlabel('MCS')
axs[0].set_ylabel('X')
axs[0].plot(d[2][100:])
axs[0].axvline(npt_to_exclude, color='red')


# try fitting
popt, pcov = curve_fit(func, bin_edges, hist, p0=(100,X_mean,X_std) )

xcont = np.linspace(0.010,0.03,100)

axs[1].set_title('PDF of X with mean_X = {:0.4e}, std_X = {:0.4e}'.format(X_mean, X_std), color='blue')
axs[1].set_xlabel('X')
axs[1].set_ylabel('P(X)')
axs[1].set_xlim([X_mean-0.008,X_mean+0.008])
axs[1].plot(bin_edges, hist, 'o',color='gray', alpha=0.85)
axs[1].plot(xcont, func(xcont,*popt), 'k-')

plt.savefig('X_ts_pdf.pdf')