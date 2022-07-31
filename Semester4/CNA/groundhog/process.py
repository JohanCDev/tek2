#!/usr/bin/env python3
import sys
import numpy as np
import calculation


def end_prog(weird_values, nb_switch, period, nb_temp):
    if period > nb_temp:
        sys.exit(84)
    print("Global tendency switched", nb_switch, "times")
    print(len(weird_values), "weird values are", weird_values)
    return 0


def print_res(g_value, r_value, s_value, prev_r):
    print("g=", end='')
    if g_value != "nan":
        print("%.2f" % g_value, end='')
    else:
        print("nan", end='')
    print("\t\tr=", end='')
    if r_value != "nan":
        print("%d%%" % r_value, end='')
    else:
        print("nan%", end='')
    print("\t\ts=", end='')
    if s_value != "nan":
        print("%.2f" % s_value, end='')
    else:
        print("nan", end='')
    if prev_r != "nan":
        if int(prev_r) > 0 and int(r_value) < 0 or int(prev_r) < 0 and int(r_value) > 0:
            print("\t\ta switch occurs")
            return 1
    print()
    return 0

def find_anomalies(data):
    anomalies = []

    random_data_std = np.std(data)
    random_data_mean = np.mean(data)
    anomaly_cut_off = random_data_std * 0.75

    lower_limit = random_data_mean - anomaly_cut_off
    upper_limit = random_data_mean + anomaly_cut_off
    for outlier in data:
        if outlier > upper_limit or outlier < lower_limit:
            anomalies.append(outlier)
    return anomalies[:5]


def process(period):
    weird_values = []
    nb_switch = 0
    temperatures = []
    wtemperatures = []
    r_value = 0
    c = 0
    while 1:
        try:
            input_str = input()
            if input_str == "STOP":
                weird_values = find_anomalies(weird_values)
                return end_prog(weird_values, nb_switch, period, len(temperatures))
            value = float(input_str)
            temperatures.append(value)
            wtemperatures.append(value)
            g_value = calculation.g(temperatures, period)
            prev_r = r_value
            r_value = calculation.r(temperatures, period)
            s_value = calculation.s(temperatures, period)
            if c >= 1:
                std = np.std(wtemperatures)
                mean = np.mean(wtemperatures)
                anomaly_cut_off = std * 1.6
                lower_limit  = mean - anomaly_cut_off
                upper_limit = mean + anomaly_cut_off
                if value > upper_limit or value < lower_limit:
                    weird_values.append(value)
                    print("weird value:", value)

            if print_res(g_value, r_value, s_value, prev_r):
                wtemperatures.clear()
                wtemperatures.append(temperatures[-2])
                wtemperatures.append(value)
                nb_switch += 1
                c = 0
            c += 1
        except (ValueError, EOFError, KeyboardInterrupt, KeyError):
            return 84


# A switch occurs only when r change of sign (+ -> - and - -> +) if you look at the example
