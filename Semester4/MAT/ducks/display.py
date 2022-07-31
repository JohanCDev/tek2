#!/usr/bin/env python3
import math
import calculation


def print_time(total_time: float) -> None:
    print(int(total_time / 60), end='')
    print("m ", end='')
    print(int(total_time % 60 / 10), end='')
    print(int(total_time % 10), end='')
    print("s")


def print_time_average(time_av: float) -> None:
    print("Average return time: ", end='')
    seconds = "{:.0f}".format(math.ceil((time_av - int(time_av)) * 60))
    print(str(int(time_av)) + "m ", end='')
    if float(seconds) == 0:
        print("00", end='')
    elif float(seconds) < 10:
        print("0", end='')
    if int(seconds) == 49:
        seconds = "50"
    print(seconds + "s")


def results(time_av: float, std_dev: float, a: float) -> None:
    print_time_average(time_av)
    print("Standard deviation: " + str(round(std_dev, 3)))
    print("Time after which 50% of the ducks are back: ", end='')
    print_time(calculation.ducks_return(a, 0.5))
    print("Time after which 99% of the ducks are back: ", end='')
    print_time(calculation.ducks_return(a, 0.99))
    one_percent_ducks = (calculation.integral(a, 1, 0) - calculation.integral(a, 0, 0)) * 100
    two_percent_ducks = (calculation.integral(a, 2, 0) - calculation.integral(a, 0, 0)) * 100
    print("Percentage of ducks back after 1 minute: %.1f%%" % one_percent_ducks)
    print("Percentage of ducks back after 2 minutes: %.1f%%" % two_percent_ducks)
