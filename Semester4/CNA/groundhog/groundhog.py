#!/usr/bin/env python3
import sys
import process


def print_helper():
    print("SYNOPSIS")
    print("\t./groundhog period\n")
    print("DESCRIPTION")
    print("\tperiod\tthe number of days defining a period")


def main(argc, argv):
    if argc == 2 and argv[1] == "-h":
        print_helper()
        return 0
    elif argc == 2 and argv[1].isnumeric():
        return process.process(int(argv[1]))
    else:
        return 84


if __name__ == '__main__':
    sys.exit(main(len(sys.argv), sys.argv))
