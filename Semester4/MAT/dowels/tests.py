#!/usr/bin/env python3
import subprocess
from typing import List


def test_pdf():
    expected_result: bytes = \
        b'Enter next value: \tNumber of values:\t12001\n' \
        b'\tStandard deviation:\t4362.84\n' \
        b'\tArithmetic mean:\t297514.13\n' \
        b'\tRoot mean square:\t297546.11\n' \
        b'\tHarmonic mean:\t\t297912.09\n' \
        b'\n' \
        b'Enter next value: '
    check_program(b'299042', expected_result, ["./206neutrinos", "12000", "297514", "297912", "4363"])


def check_program(stdin: bytes, expected_stdout: bytes, params: List[str]):
    res = subprocess.run([params[0], params[1], params[2], params[3], params[4]], input=stdin, capture_output=True)
    assert res.stdout == expected_stdout
