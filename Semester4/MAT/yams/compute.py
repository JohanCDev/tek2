#!/usr/bin/env python3
import math
from typing import List
import sys


def get_number_of_faces(nb_to_find: int, dices: List[int]) -> int:
    nb_total = 0
    for i in range(len(dices)):
        if dices[i] == nb_to_find:
            nb_total += 1
    return nb_total


def get_binomial(a: int, b: int) -> float:
    result = (math.factorial(a) / (math.factorial(b) * math.factorial(a - b))) * pow((1 / 6), b) * pow((5 / 6), (a - b))
    return result


def compute_all(quantity: int, number_to_find: int, dices: List[int]) -> float:
    result = 0.0
    occurrence = get_number_of_faces(number_to_find, dices)
    if quantity <= occurrence:
        result = 1
    else:
        for i in range(quantity - occurrence, 6 - occurrence):
            result += get_binomial(5 - occurrence, i)
    return result


def calculate_straight(number: int, dices: List[int]) -> float:
    correctDices = 0
    for i in range(number - 4, number + 1):
        if get_number_of_faces(i, dices) >= 1:
            correctDices += 1
    result: float = math.factorial(5 - correctDices) / math.pow(6, 5 - correctDices)
    return result


def calculate_full(number1: int, number2: int, dices: List[int]) -> float:
    result: float = 1.0
    n: int = 3 - get_number_of_faces(number1, dices)
    p: int = 2 - get_number_of_faces(number2, dices)
    if n < 0:
        n = 0
    elif p < 0:
        p = 0
    l: int = n + p
    result = (math.factorial(l) / (math.factorial(n) * math.factorial(l - n))) / math.pow(6, l)
    return result


def compute_yams(nb: int, dices: List[int]) -> float:
    result = compute_all(5, nb, dices) * 100
    print("Chances to get a " + str(nb) + " yams: " + "%.2f" % result + "%")
    return result


def compute_pair(nb: int, dices: List[int]) -> float:
    result = compute_all(2, nb, dices) * 100
    print("Chances to get a " + str(nb) + " pair: " + "%.2f" % result + "%")
    return result


def compute_three(nb: int, dices: List[int]) -> float:
    result = compute_all(3, nb, dices) * 100
    print("Chances to get a " + str(nb) + " three-of-a-kind: " + "%.2f" % result + "%")
    return result


def compute_four(nb: int, dices: List[int]) -> float:
    result = compute_all(4, nb, dices) * 100
    print("Chances to get a " + str(nb) + " four-of-a-kind: " + "%.2f" % result + "%")
    return result


def compute_straight(nb: int, dices: List[int]) -> float:
    if nb != 5 and nb != 6:
        sys.stderr.write("Invalid straight\n")
        exit(84)
    result = calculate_straight(nb, dices) * 100
    print("Chances to get a " + str(nb) + " straight: " + "%.2f" % result + "%")
    return result


def compute_full(nb, nb2, dices: List[int]) -> float:
    if nb == nb2:
        sys.stderr.write("Invalid full (same numbers)\n")
        exit(84)
    result = calculate_full(nb, nb2, dices) * 100
    print("Chances to get a " + str(nb) + " full of " + str(nb2) + ": %.2f" % result + "%")
    return result
