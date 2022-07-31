#!/usr/bin/env python3

import subprocess
from typing import List


def test_pdf_1():
    expected_result: bytes = \
        b'Country: European Union\n' \
        b'Fit1\n' \
        b'\tY = 1.62 X - 2749.67\n' \
        b'\tRoot-mean-square deviation: 5.22\n' \
        b'\tPopulation in 2050: 570.85\n' \
        b'Fit2\n' \
        b'\tX = 0.60 Y + 1707.97\n' \
        b'\tRoot-mean-square deviation: 5.32\n' \
        b'\tPopulation in 2050: 574.54\n' \
        b'Correlation: 0.9820\n'
    check_program(b'', expected_result, ["./207demography", "EUU"], 1)


def test_pdf_2():
    expected_result: bytes = \
        b'Country: Bolivia, Brazil, Peru\n' \
        b'Fit1\n' \
        b'\tY = 3.06 X - 5906.34\n' \
        b'\tRoot-mean-square deviation: 2.22\n' \
        b'\tPopulation in 2050: 359.35\n' \
        b'Fit2\n' \
        b'\tX = 0.33 Y + 1932.53\n' \
        b'\tRoot-mean-square deviation: 2.22\n' \
        b'\tPopulation in 2050: 359.70\n' \
        b'Correlation: 0.9991\n'
    check_program(b'', expected_result, ["./207demography", "BRA", "BOL", "PER"], 3)


def check_program(stdin: bytes, expected_stdout: bytes, params: List[str], nb_country):
    if nb_country == 1:
        res = subprocess.run([params[0], params[1]], input=stdin, capture_output=True)
    if nb_country == 3:
        res = subprocess.run([params[0], params[1], params[2], params[3]], input=stdin, capture_output=True)
    assert res.stdout == expected_stdout, res.stdout

