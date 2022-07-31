#!/usr/bin/env python3
from typing import List
import sys
import compute


def print_helper() -> int:
    print("USAGE")
    print("\t./204ducks a\n")
    print("DESCRIPTION")
    print("\ta\tconstant")
    return 0


def ducks(argc: int, argv: List[str]) -> int:
    if argc == 2 and argv[1] == "-h":
        return print_helper()
    elif argc != 2:
        return 84
    else:
        try:
            a: float = float(argv[1])
            if not (0 <= a <= 2.5):
                return 84
            return compute.compute_program(a)
        except ValueError:
            return 84
