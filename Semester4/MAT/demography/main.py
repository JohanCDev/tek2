#!/usr/bin/env python3


import csv
import sys
import os
import math
import helper
import numpy as np


filename = "./207demography_data.csv"
years = []


def get_sum_years():
    year = 1960
    while year <= 2017:
        years.append(year)
        year += 1
    return years


def get_countries_name(data):
    countries = []
    i = 0
    while i < len(data):
        countries.append(data[i][0])
        i += 1
    return countries


def get_countries_code(data):
    countries = []
    i = 0
    while i < len(data):
        countries.append(data[i][1])
        i += 1
    return countries


def countries_loader(data, index):
    countries = []
    i = 0
    k = 0
    while i < len(data):
        if k >= len(index):
            break
        if i == index[k]:
            countries.append(data[i])
            k += 1
        i += 1
    return countries


def csv_loader():
    data = []
    with open(filename, 'r') as csv_file:
        reader = csv.reader(csv_file, delimiter=';')
        next(reader)
        for row in reader:
            data.append(row)
        return data


def compare_country(argv, countries_code, countries_name):
    i = 0
    k = 0
    first = 1
    countries_index = []
    countries_name_list = []
    while i < len(countries_code):
        if k >= len(argv):
            break
        if argv[k] == countries_code[i] and first == 1:
            countries_name_list.append(countries_name[i])
            countries_index.append(i)
            k += 1
            i = 0
            first = 0
        elif argv[k] == countries_code[i]:
            countries_name_list.append(countries_name[i])
            countries_index.append(i)
            k += 1
            i = 0
        if i == len(countries_code) - 1:
            sys.exit(84)
        i += 1
    countries_name_list.sort()
    countries_index.sort()
    print("Country: ", end='')
    print(countries_name_list[0], end='')
    for i in range(1, len(countries_name_list)):
        print(f', {countries_name_list[i]}', end='')
    print("")
    return countries_index


def get_lst_tot_pop(countries):
    total_countries = [0] * 58
    for i in range(0, len(countries), 1):
        for k in range(2, len(countries[i]), 1):
            total_countries[k - 2] += int(countries[i][k])
    return total_countries


def get_a_b(sums):
    a = (sums[0] * sums[2] - sums[1] * sums[3]) / (len(years) * sums[2] - sums[1] ** 2)
    b = ((len(years) * sums[3]) - (sums[0] * sums[1])) / (len(years) * sums[2] - math.pow(sums[1], 2))
    return a, b


def get_sums1(lst_pop):
    sums = [0, 0, 0, 0]
    sums[0] = sum(lst_pop)
    sums[1] = sum(years)
    for i in range(0, len(lst_pop), 1):
        sums[2] += pow(years[i], 2)
        sums[3] += lst_pop[i]*years[i]
    return sums


def get_sums_2(lst_pop):
    sums = [0, 0, 0, 0]
    sums[0] = sum(years)
    sums[1] = sum(lst_pop)
    for i in range(0, len(lst_pop)):
        sums[2] += pow(lst_pop[i], 2)
        sums[3] += lst_pop[i] * years[i]
    return sums


def fit1(lst_tot_pop):
    print("Fit1")
    res = 0
    sums = get_sums1(lst_tot_pop)
    a, b = get_a_b(sums)
    if a >= 0:
        print("\tY = ", format(b * 0.000001, ".2f"), " X + ", format(a * 0.000001, ".2f"), sep="")
    else:
        print("\tY = ", format(b * 0.000001, ".2f"), " X - ", format(a * (-0.000001), ".2f"), sep="")
    for i in range(0, len(lst_tot_pop)):
        func = years[i] * b + a
        res += ((func - lst_tot_pop[i]) ** 2 / len(lst_tot_pop))
    print("\tRoot-mean-square deviation: ", format(math.sqrt(res) * 0.000001, ".2f"), sep="")
    print("\tPopulation in 2050: ", format((2050 * b + a) * 0.000001, ".2f"), sep="")


def fit2(lst_tot_pop):
    print("Fit2")
    res = 0
    sums = get_sums_2(lst_tot_pop)
    a, b = get_a_b(sums)
    if a >= 0:
        print("\tX = ", format(b * 1000000, ".2f"), " Y + ", format(a, ".2f"), sep="")
    else:
        print("\tX = ", format(b, ".2f"), " Y - ", format(a * -1, ".2f"), sep="")
    for i in range(0, len(lst_tot_pop)):
        func = (years[i] - a) / b
        res += ((func - lst_tot_pop[i]) ** 2 / len(lst_tot_pop))
    print("\tRoot-mean-square deviation: ", format(math.sqrt(res) * 0.000001, ".2f"), sep="")
    print("\tPopulation in 2050: ", format(((2050 - a) / b * 0.000001), ".2f"), sep="")


def main(argc, argv):
    data = csv_loader()
    if argc <= 1:
        exit(84)
    if argc == 2 and argv[1] == "-h":
        helper.print_helper()
        sys.exit(0)
    countries_code = get_countries_code(data)
    countries_name = get_countries_name(data)
    countries_index = compare_country(argv[1:], countries_code, countries_name)
    countries = countries_loader(data, countries_index)
    global years
    years = get_sum_years()
    lst_tot_pop = get_lst_tot_pop(countries)
    fit1(lst_tot_pop)
    fit2(lst_tot_pop)
    print("Correlation: " + str(format(np.corrcoef(lst_tot_pop, years)[0][1], ".4f")))
