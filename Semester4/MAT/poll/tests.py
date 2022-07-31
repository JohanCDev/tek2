#!/usr/bin/env python3
import subprocess
import sys
from typing import List


def test_pdfs_1():
    expected_result: bytes = \
        b'Population size:\t\t10000\n' \
        b'Sample size:\t\t\t500\n' \
        b'Voting intentions:\t\t42.24%\n' \
        b'Variance:\t\t\t0.000464\n' \
        b'95% confidence interval:\t[38.02%; 46.46%]\n' \
        b'99% confidence interval:\t[36.68%; 47.80%]\n'
    check_program(b'', expected_result, ["./209poll", "10000", "500", "42.24"])


def test_pdf_2():
    expected_result: bytes = \
        b'Population size:\t\t10000\n' \
        b'Sample size:\t\t\t100\n' \
        b'Voting intentions:\t\t45.00%\n' \
        b'Variance:\t\t\t0.002450\n' \
        b'95% confidence interval:\t[35.30%; 54.70%]\n' \
        b'99% confidence interval:\t[32.23%; 57.77%]\n'
    check_program(b'', expected_result, ["./209poll", "10000", "100", "45"])


def test_3():
    expected_result: bytes = \
        b'Population size:\t\t1\n' \
        b'Sample size:\t\t\t0\n' \
        b'Voting intentions:\t\t45.00%\n' \
        b'Variance:\t\t\t0.000000\n' \
        b'95% confidence interval:\t[45.00%; 45.00%]\n' \
        b'99% confidence interval:\t[45.00%; 45.00%]\n'
    check_program(b'', expected_result, ["./209poll", "1", "0", "45"])


def test_4():
    expected_result: bytes = \
        b'Bad arguments try with -h\n'
    res = subprocess.run(["./209poll", "1", "0", "45", "90"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_5():
    expected_result: bytes = \
        b'Bad arguments try with -h\n'
    res = subprocess.run(["./209poll", "1", "0"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_6():
    expected_result: bytes = \
        b'An argument is not a number\n'
    res = subprocess.run(["./209poll", "lol", "0", "45"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_7():
    expected_result: bytes = \
        b'An argument is not a number\n'
    res = subprocess.run(["./209poll", "1", "lol", "45"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_8():
    expected_result: bytes = \
        b'An argument is not a number\n'
    res = subprocess.run(["./209poll", "1", "0", "lol"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_9():
    expected_result: bytes = \
        b'n is invalid\n'
    res = subprocess.run(["./209poll", "1", "2", "45"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_10():
    expected_result: bytes = \
        b'p is invalid\n'
    res = subprocess.run(["./209poll", "1", "0", "101"], input=b'', capture_output=True)
    assert res.stderr == expected_result


def test_11():
    expected_result: bytes = \
        b'USAGE\n' \
        b'\t./209poll pSize sSize p\n\n' \
        b'DESCRIPTION\n' \
        b'\tpSize\tsize of the population\n' \
        b'\tsSize\tsize of the sample (supposed to be representative)\n' \
        b'\tp\tpercentage of voting intentions for a specific candidate\n'
    res = subprocess.run(["./209poll", "-h"], input=b'', capture_output=True)
    assert res.stdout == expected_result


def check_program(stdin: bytes, expected_stdout: bytes, params: List[str]):
    res = subprocess.run([params[0], params[1], params[2], params[3]], input=stdin, capture_output=True)
    assert res.stdout == expected_stdout, res.stdout

