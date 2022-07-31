#!/usr/bin/env python3.10
import math
import matplotlib.pyplot as plt
import numpy as np


def get_tab_basic(mean, std_dev, minimum=0, maximum=201):
    tab = []
    for i in range(minimum, maximum):
        tab.append(calc_gauss(mean, std_dev, i))
    return tab


def calc_gauss(mean, std_dev, x):
    return math.exp(-math.pow(x - mean, 2) / (2 * pow(std_dev, 2))) / (std_dev * math.sqrt(2 * math.pi))


def basic(mean, std_dev):
    tab = get_tab_basic(mean, std_dev)
    for i in range(len(tab)):
        print(i, "%.5f" % tab[i])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(tab)
    ax.set_xlabel("IQ")
    ax.set_ylabel("density")
    ax.set_title("Density for IQ")
    plt.show()


def inferior(mean, std_dev, inf_iq):
    iterator = 0
    result = 0
    while iterator < inf_iq:
        result += calc_gauss(mean, std_dev, iterator)
        iterator += 0.01
    print("%.1f%% of people have an IQ inferior to %d" % (result, inf_iq))
    return "{:.1f}".format(result)


def superior(mean, std_dev, inf_iq, sup_iq):
    iterator = inf_iq
    result = 0
    while iterator < sup_iq:
        result += calc_gauss(mean, std_dev, iterator)
        iterator += 0.01
    print("%.1f%% of people have an IQ between %d and %d" % (result, inf_iq, sup_iq))
    return result


def calc_between_limit(mean, std_dev, inf_iq=0, sup_iq=201):
    iterator = inf_iq
    result = 0
    while iterator < sup_iq:
        result += calc_gauss(mean, std_dev, iterator)
        iterator += 0.01
    print("%.1f%% of people have an IQ between %d and %d" % (result, inf_iq, sup_iq))
    return result
