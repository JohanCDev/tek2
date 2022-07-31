#!/usr/bin/env python3
from typing import List
import math


def display_helper() -> None:
    print("USAGE")
    print("\t./202unsold.py a b")
    print("DESCRIPTION")
    print("\ta\tconstant computed from the past results")
    print("\tb\tconstant computed from the past results")

Law_X = list()
Law_Y = list()

def check_args(args: List[str], nb_args: int) -> bool:
    if nb_args == 2 and args[1] == "-h":
        display_helper()
        return False
    elif nb_args == 3 and args[1].isnumeric() and args[2].isnumeric() and int(args[1]) > 50 and int(args[2]) > 50:
        return True
    else:
        return False


def get_marginal(x, y, a, b):
    result = (a - x) * (b - y) / ((5 * a - 150) * (5 * b - 150))
    return result


def print_second_part(a: int, b: int) -> None:
    print("z\t20\t30\t40\t50\t60\t70\t80\t90\t100\np(Z=z)", end='')
    for z in range(2, 11):
        sum_res = 0.0
        for y in range(1, 6):
            for x in range(1, 6):
                res = get_marginal(x * 10, y * 10, a, b)
                if x + y == z and y < 6:
                    sum_res += res
        print("\t%0.3f" % sum_res, end='')
    print()


def process(argc: int, argv: List[str]) -> int:
    if check_args(argv, argc):
        print("--------------------------------------------------------------------------------")
        compute_first_part(argv)
        print("--------------------------------------------------------------------------------")
        print_second_part(int(argv[1]), int(argv[2]))
        print("--------------------------------------------------------------------------------")
        compute_third_part()
        print("--------------------------------------------------------------------------------", end='')
        return 0
    return 84


def fill_tab(a, b):
    size = 5
    array = [[0 for x in range(0, size)] for x in range(0, size)]
    for y in range(0, size):
        for x in range(0, size):
            array[y][x] = ((a - ((x + 1) * 10)) * (b - ((y + 1) * 10))) / (((5 * a) - 150) * ((5 * b) - 150))
    return array


def compute_first_part(args) -> None:
    a = int(args[1])
    b = int(args[2])
    print("\t\tX=10\tX=20\tX=30\tX=40\tX=50\tY law")
    tab_result = fill_tab(a, b)
    for y in range(0, 5):
        print("Y=" + str((y + 1) * 10), end='\t')
        for x in range(0, 5):
            print("%0.3f" % tab_result[y][x], end='\t')
        print("%0.3f" % sum(tab_result[y]))
        Law_Y.append(sum(tab_result[y]))
    print("X law", end='\t')
    for x in range(0, 5):
        res_col = 0
        for y in range(0, 5):
            res_col += tab_result[y][x]
        print("%0.3f" % res_col, end='\t')
        Law_X.append(res_col)
    print("%0.3f" % 1)


def compute_third_part():
    exp_x = 0.0
    exp_y = 0.0
    res_x = 0.0
    res_y = 0.0
    for i in range(0, 5):
        res_x += Law_X[i] * ((i + 1) * 10)
        res_y += Law_Y[i] * ((i + 1) * 10)
    for i in range(0, 5):
        exp_x += ((i + 1) * 10 - res_x) * ((i + 1) * 10 - res_x) * Law_X[i]
        exp_y += ((i + 1) * 10 - res_y) * ((i + 1) * 10 - res_y) * Law_Y[i]
    print("expected value of X:\t" + "%0.1f" % res_x)
    print("variance of X:\t\t" + "%0.1f" % exp_x)
    print("expected value of Y:\t" + "%0.1f" % res_y)
    print("variance of Y:\t\t" + "%0.1f" % exp_y)
    print("expected value of Z:\t" + "%0.1f" % (res_x + res_y))
    print("variance of Z:\t\t" + "%0.1f" % (exp_x + exp_y))
