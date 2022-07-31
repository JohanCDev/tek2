#!/usr/bin/env python3
import math
import sys


def s(temperatures, period):
    if len(temperatures) >= period:
        final = len(temperatures)
        second = 0
        first = 0

        for i in range(final - period, final):
            first = first + pow(temperatures[i], 2)
            second = second + temperatures[i]
        return math.sqrt(first / period - pow(second / period, 2))
    else:
        return "nan"


def r(temperatures, period):
    if period < len(temperatures):
        second = temperatures[-1]
        first = abs(temperatures[len(temperatures) - period - 1])
        if first == 0:
            return int(1000)
        else:
            return int((round((second - first) / first * 100)))
    else:
        return "nan"


def g(temperatures, period):
    if period < len(temperatures):
        final_g = 0
        i = len(temperatures) - period
        while len(temperatures) > i:
            n = temperatures[i] - temperatures[i - 1]
            final_g += n if n > 0 else 0
            i += 1
        try:
            final_g /= period
            return final_g
        except ZeroDivisionError:
            sys.exit(84)
    else:
        return "nan"
