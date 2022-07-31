#!/usr/bin/env python3
import math
import sys


def calc_variance(N, n, p):
    percent = float(p / 100)
    variance = percent * (1 - percent)
    try:
        res = (variance / n) * ((N - n) / (N - 1))
    except ZeroDivisionError:
        return 0
    return res


def clamp(i):
    return min(max(i, 0), 1)


def interval(x, i):
    return 100 * clamp(x - i), 100 * clamp(x + i)


def calc_interval(N, n, p, inter):
    final_p = p / 100
    val = 0
    if inter == 95:
        val = 1.96
    elif inter == 99:
        val = 2.58
    return interval(final_p, val * math.sqrt(calc_variance(N, n, p)))


def print_res(N, n, p):
    variance = calc_variance(N, n, p)
    first95, second95 = calc_interval(N, n, p, 95)
    first99, second99 = calc_interval(N, n, p, 99)
    print("Population size:\t\t" + str(N))
    print("Sample size:\t\t\t" + str(n))
    print("Voting intentions:\t\t%.2f%%" % p)
    print("Variance:\t\t\t%.6f" % variance)
    print('95%% confidence interval:\t[%.2f%%; %.2f%%]' % (first95, second95))
    print('99%% confidence interval:\t[%.2f%%; %.2f%%]' % (first99, second99))


def process(argc, argv):
    N = int(argv[1])
    n = int(argv[2])
    p = float(argv[3])
    print_res(N, n, p)
    return 0

