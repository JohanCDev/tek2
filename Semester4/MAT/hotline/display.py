#!/usr/bin/env python3
from typing import List
import time
import calculations


def binomial(base_value: int) -> None:
    overload: int = 0
    k: float = base_value / (8 * 60 * 60)
    print("Binomial distribution:")
    start = time.time()
    for i in range(0, 51):
        result = calculations.binomial(i, k)
        if i < 26:
            overload += result
        print(i, "->", "%.3f" % result, end="")
        if (i + 1) % 5 and i < 50:
            print("\t", end="")
        else:
            print()
    end = time.time()
    print("Overload: ", "%.1f%%" % ((1 - overload) * 100))
    print("Computation time: %.2f ms\n" % ((end - start) * 1000), sep='')


def poisson(base_value: int) -> None:
    overload: int = 0
    n: float = (base_value / (8 * 60 * 60)) * 3500
    print("Poisson distribution:")
    start = time.time()
    for i in range(0, 51):
        result = calculations.poisson(n, i)
        if i < 26:
            overload += result
        print(i, "->", "%.3f" % result, end="")
        if (i + 1) % 5 and i < 50:
            print("\t", end="")
        else:
            print()
    end = time.time()
    print("Overload: ", "%.1f%%" % ((1 - overload) * 100))
    print("Computation time: %.2f ms" % ((end - start) * 1000), sep='')


def combinations(n: int, k: int) -> None:
    print(str(k) + "-combinations of a set of size " + str(n) + ":")
    print(str(calculations.get_binomial(n, k)))
