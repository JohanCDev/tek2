#!/usr/bin/env python3

import calculations
import sys

def run_tests():
    test_combinations_pdf()

def test_combinations_pdf():
    expected_result: int = 30664510802988208300
    result: int = calculations.get_binomial(100, 18)
    assert result == expected_result, str(result) + "% is different from " + str(expected_result) + "%"