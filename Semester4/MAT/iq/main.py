#!/usr/bin/env python3
import sys
import process


def print_helper():
    print("USAGE")
    print("\t./205IQ μ σ [IQ1] [IQ2]\n")
    print("DESCRIPTION")
    print("\tμ\tpredetermined menu")
    print("\tσ\tpredetermined standard deviation")
    print("\tIQ1\tminimum IQ")
    print("\tIQ2\tmaximum IQ")
    return 1


def check_args(argc, argv):
    if argc == 2 and argv[1] == "-h":
        return print_helper()
    if argc < 3 or argc > 5:
        print("Bad arguments try with -h", file=sys.stderr)
        return -1
    for i in range(1, argc):
        if not argv[i].isnumeric():
            return -1
    if int(argv[2]) > int(argv[1]):
        return -1
    if argc == 5 and int(argv[3]) > int(argv[4]):
        return -1
    if argc >= 4 and int(argv[3]) > 200:
        return -1
    if argc == 5 and int(argv[4]) > 200:
        return -1
    if int(argv[1]) > 200 or int(argv[2]) == 0:
        return -1
    return 0


def main(argc, argv):
    args_return = check_args(argc, argv)
    if args_return == -1:
        return 84
    elif args_return == 1:
        return 0
    else:
        return process.process(argc, argv)
