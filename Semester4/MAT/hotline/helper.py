#!/usr/bin/env python3
import tests


def print_helper() -> None:
    print("USAGE")
    print("\t./203hotline [n k | d]\n")
    print("DESCRIPTION")
    print("\tn\tn value for the computation of C(n, k)")
    print("\tk\tk value for the computation of C(n, k)")
    print("\td\taverage duration of calls (in seconds)")


def two_args(arg: str) -> int:
    if arg == "-h":
        print_helper()
    if arg == "-t":
        tests.run_tests()
    return 84
