#!/usr/bin/env python3
from typing import List
import helper
import display


def process(argc: int, argv: List[str]) -> int:
    if argc == 2:
        if argv[1].isnumeric() and int(argv[1]) > 0:
            display.binomial(int(argv[1]))
            display.poisson(int(argv[1]))
            return 0
        else:
            return helper.two_args(argv[1])
    elif argc == 3:
        if argv[1].isnumeric() and argv[2].isnumeric() and int(argv[1]) > 0 and 0 < int(argv[2]) < int(argv[1]):
            display.combinations(int(argv[1]), int(argv[2]))
            return 0
    return 84
