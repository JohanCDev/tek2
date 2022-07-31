#!/usr/bin/env python3
import sys
import process


def print_helper():
    print("USAGE")
    print("\t./209poll pSize sSize p\n")
    print("DESCRIPTION")
    print("\tpSize\tsize of the population")
    print("\tsSize\tsize of the sample (supposed to be representative)")
    print("\tp\tpercentage of voting intentions for a specific candidate")
    return 0


def check_args(argc, argv):
    if argc != 4:
        print("Bad arguments try with -h", file=sys.stderr)
        return "Error"
    try:
        n = int(argv[2])
        N = int(argv[1])
        p = float(argv[3])
    except ValueError:
        print("An argument is not a number", file=sys.stderr)
        return "Error"
    if not 0 <= n <= N:
        print("n is invalid", file=sys.stderr)
        return "Error"
    if not 0 <= p <= 100:
        print("p is invalid", file=sys.stderr)
        return "Error"
    return N, n, p


def main(argc, argv):
    if argc == 2 and argv[1] == "-h":
        return print_helper()
    if check_args(argc, argv) == "Error":
        return 84
    process.process(argc, argv)
