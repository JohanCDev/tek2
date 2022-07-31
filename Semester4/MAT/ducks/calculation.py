#!/usr/bin/env python3
import math
import typing
import sys


def integral(a, t, mode) -> float:
    if mode == 0:
        return -a * math.exp(-t) - (4 - 3 * a) / 2 * math.exp(-2 * t) - (2 * a - 4) / 4 * math.exp(-4 * t)
    else:
        return a * math.exp(-t) + (4 - 3 * a) * math.exp(-2 * t) + (2 * a - 4) * math.exp(-4 * t)


def time_average(a: float) -> float:
    result: float = 0.0
    t: float = 0.0
    while t < 100:
        result += integral(a, t, 1) * t / 10000
        t += 0.0001
    return result


def dev(a: float, time_av: float) -> float:
    result: float = 0.0
    t: float = 0.0
    while t < 100:
        result += pow(t - time_av, 2) * integral(a, t, 1) / 1000
        t += 0.001
    result = math.sqrt(result)
    return result


def ducks_return(a: float, time: float) -> float:
    t = 0.0
    try:
        while t < 1000:
            if integral(a, t / 60, 0) - integral(a, 0, 0) >= time:
                return t
            t += 0.002
    except ValueError:
        sys.exit(84)