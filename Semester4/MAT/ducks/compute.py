#!/usr/bin/env python3
import display
import calculation


def compute_program(a: float) -> int:
    time_av: float = calculation.time_average(a)
    display.results(time_av, calculation.dev(a, time_av), a)
    return 0
