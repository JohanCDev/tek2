#!/usr/bin/env python3.10
import results
import matplotlib.pyplot as plt
import numpy as np


def process(argc, argv):
    mean = int(argv[1])
    std_dev = int(argv[2])
    if argc == 3:
        results.basic(mean, std_dev)
    elif argc == 4:
        qi1 = int(argv[3])
        val = results.calc_between_limit(mean, std_dev, qi1)
        print("%.1f%% of people have an IQ inferior to %d" % (100 - val, qi1))
        base_tab = results.get_tab_basic(mean, std_dev)
        qi1_arr = np.full(len(base_tab), qi1)
        plt.plot(base_tab)
        plt.plot(qi1_arr, base_tab, "r")
        plt.show()
    elif argc == 5:
        qi1 = int(argv[3])
        qi2 = int(argv[4])
        val = results.calc_between_limit(mean, std_dev, qi1, qi2)
        print("%.1f%% of people have an IQ between %d and %d" % (val, qi1, qi2))
        base_tab = results.get_tab_basic(mean, std_dev)
        qi1_arr = np.full(len(base_tab), qi1)
        qi2_arr = np.full(len(base_tab), qi2)
        plt.plot(base_tab)
        plt.plot(qi1_arr, base_tab, "r")
        plt.plot(qi2_arr, base_tab, "g")
        plt.show()
    return 0
