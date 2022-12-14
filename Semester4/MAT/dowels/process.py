#!/usr/bin/env python3

import sys
from math import pow, sqrt, factorial

class BadArgumentError(Exception):
    def __init__(self, message, errors = "BadArgumentError"):
        super().__init__(message)
        self.errors = errors

class Dowels():
    """  """
    distribution = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [.00, .02, .06, .15, .27, .45, .71, 1.07, 1.64, 2.71, 3.84, 5.41, 6.63],
        [.02, .21, .45, .71, 1.02, 1.39, 1.83, 2.41, 3.22, 4.61, 5.99, 7.82, 9.21],
        [.11, .58, 1.01, 1.42, 1.87, 2.37, 2.95, 3.66, 4.64, 6.25, 7.81, 9.84, 11.34],
        [.30, 1.06, 1.65, 2.19, 2.75, 3.36, 4.04, 4.88, 5.99, 7.78, 9.49, 9.84, 11.34],
        [.55, 1.61, 2.34, 3.00, 3.66, 4.35, 5.13, 6.06, 7.29, 9.24, 11.07, 11.67, 13.28],
        [.7, 2.20, 3.07, 3.83, 4.57, 5.35, 6.21, 7.23, 8.56, 10.64, 12.59, 15.03, 16.81],
        [1.24, 2.83, 3.82, 4.67, 5.49, 6.35, 7.28, 8.38, 9.80, 12.02, 14.07, 16.62, 18.48],
        [1.65, 3.49, 4.59, 5.53, 6.42, 7.34, 8.35, 9.52, 11.03, 13.36, 15.51, 18.17, 20.09],
        [2.09, 4.17, 5.38, 6.39, 7.63, 8.34, 9.41, 10.66, 12.24, 14.68, 16.92, 19.68, 21.67],
        [2.56, 4.87, 6.18, 7.27, 8.30, 9.34, 10.47, 11.78, 13.44, 15.99, 18.31, 21.16, 23.21]]
    fit_validity = ""
    offset_right = 0
    offset_left = 0
    result = list()
    tab = list()
    tmp = list()

    def __init__(self, param):
        """ initialise Dowels's instance and check little errors """
        self.argument = [int(i) for i in param]
        self.param = [int(i) for i in param]
        if sum(self.param) != 100:
            raise BadArgumentError("You must pass arguments equal to 100")
        if sum(1 for number in self.param if number < 0) > 0:
            raise BadArgumentError("You must pass valid positive number")

    def sort_tab(self):
        """ Fuse all integer less than 10 in the first case and reverse it """
        while self.param[0] < 10:
            self.param[0] = self.param[0] + self.param[1]
            self.param.remove(self.param[1])
            self.offset_left += 1
        self.param.reverse()
        while self.param[0] < 10:
            self.param[0] = self.param[0] + self.param[1]
            self.param.remove(self.param[1])
            self.offset_right += 1
        self.param.reverse()

    def compute_value(self):
        """  """
        self.probability = sum([i * self.param[i] for i in range(len(self.param))]) / pow(10, 4)
        self.sort_tab()
        for i in range(8):
            self.tmp.append((factorial(100) / (factorial(i) * factorial(100 - i))) * 100
                * pow(1 - self.probability, 100 - i) * pow(self.probability, i))
        self.tmp.append(100 - sum(i for i in self.tmp))
        self.result.append(sum(self.tmp[:self.offset_left + 1]))
        self.result += (i for i in self.tmp[self.offset_left + 1:])
        self.save = self.result[len(self.result) - 1 - self.offset_right:]
        self.result = self.result[:len(self.result) - 1 - self.offset_right]
        self.result.append(sum(i for i in self.tmp[(len(self.tmp) - 1 - self.offset_right):]))
        self.freedom_degree = len(self.result) - 2
        self.sum_square = sum(pow(self.param[i] - self.result[i], 2)
            / self.result[i] for i in range(len(self.result)))
        if self.distribution[self.freedom_degree][0] > self.sum_square:
            self.fit_validity = "P > 99%"
        else:
            for i in range(len(self.distribution)):
                if self.distribution[self.freedom_degree][i] > self.sum_square:
                    if i == 0:
                        self.fit_validity = "99% > P > 90%"
                    elif i > 0 and i <= 10:
                        self.fit_validity = str(100 - i * 10) + "% < P < " + str(100 - (i - 1) * 10) + "%"
                    else:
                        if i == 10:
                            self.fit_validity = "5% < P < 2%"
                        elif i == 11:
                            self.fit_validity = "2% < P < 1%"
                    return
            self.fit_validity = "P < 1%"

    def print_value(self):
        """ print all computed value into the tab """
        print("   x\t| 0", end='')
        print("-%d" % self.offset_left if self.offset_left > 0 else "", end='')
        for i in range(self.offset_left + 1, len(sys.argv) - 1 - self.offset_right):
            print("\t| %d" % i, end='')
        print("+\t| total\n  Ox\t| ", end='')
        print("\t| ".join("%d" % i for i in self.param) + "\t|100")
        print("  Tx\t| ", end='')
        print("\t| ".join("%.1f" % i for i in self.result) + "\t| 100")
        print("Distribution:\t\t\tB(100, %.4f)" % self.probability)
        print("Chi-squared:\t\t\t%.3f" % self.sum_square)
        print("Degrees of freedom:\t\t%d" % self.freedom_degree)
        print("Fit validity:\t\t\t%s" % self.fit_validity)


# Do not put more information in this function, it's must be clearer as possible
def process(argc, argv):
    """ Main function who perform program's core action like arguments resolution """
    obj = Dowels(argv[1:])
    obj.compute_value()
    obj.print_value()
