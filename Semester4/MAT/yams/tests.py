#!/usr/bin/env python3
import math
import typing
from typing import List
import compute


def run_tests():
    test_yams_not_thrown()
    test_four_pdf()
    test_straight_pdf()
    test_full_not_thrown()
    test_full_thrown()
    test_pair_thrown()
    print("\033[92mTEST SUCCESSFULLY PASSED\033[0m")


def test_yams_not_thrown():
    dices: List[int] = [0, 0, 0, 0, 0]
    expected_result = 0.01
    result = round(compute.compute_yams(4, dices), 2)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"


def test_four_pdf():
    dices: List[int] = [1, 2, 3, 4, 5]
    expected_result = 1.62
    result = round(compute.compute_four(4, dices), 2)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"


def test_straight_pdf():
    dices: List[int] = [2, 2, 5, 4, 6]
    expected_result = 16.67
    result = round(compute.compute_straight(6, dices), 2)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"


def test_full_not_thrown():
    dices: List[int] = [0, 0, 0, 0, 0]
    expected_result = 0.13
    result = round(compute.compute_full(2, 3, dices), 2)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"


def test_full_thrown():
    dices: List[int] = [2, 3, 2, 3, 2]
    expected_result = 100
    result = round(compute.compute_full(2, 3, dices), 2)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"


def test_pair_thrown():
    dices: List[int] = [1, 2, 3, 4, 5]
    expected_result = 51.77
    result = round(compute.compute_pair(4, dices), 2)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"
