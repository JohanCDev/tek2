#!/usr/bin/env python3
import sys
import process


def print_helper():
    print("USAGE")
    print("\t./208dowels O0 O1 O2 O3 O4 O5 O6 O7 O8\n")
    print("DESCRIPTION")
    print("\tOi\tsize of the observed class")
    return 1


def check_args_values(argv):
    sum = 0
    try:
        for i in range(1, 10):
            if int(argv[i]) < 0:
                print("Argument " + str(i) + " is inferior to 0", file=sys.stderr)
                return False
            sum += int(argv[i])
    except ValueError:
        return False
    if sum != 100:
        print(sum)
        print("You must pass arguments equal to 100", file=sys.stderr)
        return False
    return True


def check_args(argc, argv):
    if argc == 2 and argv[1] == "-h":
        return print_helper()
    if argc != 10:
        print("Bad number of args, try with -h", file=sys.stderr)
        return 84
    if not check_args_values(argv):
        return 84
    return 0


def main(argc, argv):
    args_return = check_args(argc, argv)
    if args_return == 84:
        return 84
    elif args_return == 1:
        return 0
    else:
        return process.process(argc, argv)
