#!/usr/bin/env python3
import typing
import math
import sys


def get_binomial(n: int, k: int) -> int:
    try:
        return math.factorial(n) // (math.factorial(k) * math.factorial(n - k))
    except ArithmeticError:
        sys.exit(84)


def binomial(k: int, p: int) -> int:
    n: int = 3500
    binomial_res = get_binomial(n, k)
    return binomial_res * (p ** k) * ((1 - p) ** (n - k))


def poisson(x: int, k: int) -> int:
    try:
        return (math.exp(x * (-1)) * x ** k) / (math.factorial(k))
    except ArithmeticError:
        sys.exit(84)
