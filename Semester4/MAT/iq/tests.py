#!/usr/bin/env python3
import process
import results
import main


def test_check_args_success():
    ret = main.check_args(3, ["./205", "100", "24"])
    ret2 = main.check_args(2, ["./205", "-h"])
    ret3 = main.check_args(4, ["./205", "100", "24", "90"])
    ret4 = main.check_args(5, ["./205", "100", "24", "90", "95"])
    assert ret == 0
    assert ret2 == 1
    assert ret3 == 0
    assert ret4 == 0


def test_check_args_failure():
    ret = main.check_args(1, ["./205"])
    ret2 = main.check_args(3, ["./205", "100.32", "hello"])
    ret3 = main.check_args(3, ["./205", "34", "35"])
    ret4 = main.check_args(3, ["./205", "-1", "-3"])
    ret5 = main.check_args(6, ["./205", "100", "24", "90", "95", "54"])
    ret6 = main.check_args(5, ["./205", "100", "24", "96", "95"])
    assert ret == -1
    assert ret2 == -1
    assert ret3 == -1
    assert ret4 == -1
    assert ret5 == -1
    assert ret6 == -1


def tests_pdf():
    ret = results.inferior(100, 24, 90)
    assert float(ret) == 33.8
