#!/usr/bin/python3

import sys


class Bot:
    def __init__(self):
        self.botState = BotState()
        self.nb_up = 0
        self.nb_down = 0
        self.iter = 0
        self.bollinger_up = []
        self.bollinger_down = []
        self.obj_reached = False
        self.objective = 2500

    def run(self):
        while True:
            reading = input()
            if len(reading) == 0:
                continue
            self.parse(reading)
            self.iter += 1

    def parse(self, info: str):
        tmp = info.split(" ")
        if tmp[0] == "settings":
            self.botState.update_settings(tmp[1], tmp[2])
        if tmp[0] == "update":
            if tmp[1] == "game":
                self.botState.update_game(tmp[2], tmp[3])
        if tmp[0] == "action":
            self.algo()

    def get_prop_buy(self):
        perc = 1 - self.botState.charts["USDT_BTC"].closes[-2] / self.botState.charts["USDT_BTC"].closes[-1]
        return perc

    def get_prop_sell(self):
        perc = 1 - self.botState.charts["USDT_BTC"].closes[-1] / self.botState.charts["USDT_BTC"].closes[-2]
        if perc < 0.005:
            return 0
        elif perc > 0.2:
            return 0.095
        return perc

    def algo(self):
        if not self.obj_reached:
            dollars = self.botState.stacks["USDT"]
            btc = self.botState.stacks["BTC"]
            current_closing_price = self.botState.charts["USDT_BTC"].closes[-1]
            previous_closing_price = self.botState.charts["USDT_BTC"].closes[-2]
            affordable = dollars / current_closing_price
            if previous_closing_price > current_closing_price:
                self.nb_down += 1
                self.nb_up = 0
            elif previous_closing_price < current_closing_price:
                self.nb_up += 1
                self.nb_down = 0
            if dollars + btc * current_closing_price >= self.objective:
                self.obj_reached = True
                print(f'sell USDT_BTC {btc}', flush=True)
            elif dollars > 5 and self.nb_up >= 2:
                prop_buy = self.get_prop_buy() * 10
                print("Buy proportion " + str(self.get_prop_buy()), file=sys.stderr)
                if prop_buy <= 0:
                    print("no_moves", flush=True)
                else:
                    print(f'buy USDT_BTC {prop_buy * affordable}', flush=True)
            elif btc > 0 and self.nb_down >= 2:
                prop_sell = self.get_prop_sell() * 10
                print("Sell proportion " + str(self.get_prop_sell()), file=sys.stderr)
                if prop_sell == 0:
                    print("no_moves", flush=True)
                else:
                    print(f'sell USDT_BTC {prop_sell * btc}', flush=True)
            else:
                print("no_moves", flush=True)
        else:
            print("no_moves", flush=True)


class Candle:
    def __init__(self, format, intel):
        tmp = intel.split(",")
        for (i, key) in enumerate(format):
            value = tmp[i]
            if key == "pair":
                self.pair = value
            if key == "date":
                self.date = int(value)
            if key == "high":
                self.high = float(value)
            if key == "low":
                self.low = float(value)
            if key == "open":
                self.open = float(value)
            if key == "close":
                self.close = float(value)
            if key == "volume":
                self.volume = float(value)

    def __repr__(self):
        return str(self.pair) + str(self.date) + str(self.close) + str(self.volume)


class Chart:
    def __init__(self):
        self.dates = []
        self.opens = []
        self.highs = []
        self.lows = []
        self.closes = []
        self.volumes = []
        self.indicators = {}

    def add_candle(self, candle: Candle):
        self.dates.append(candle.date)
        self.opens.append(candle.open)
        self.highs.append(candle.high)
        self.lows.append(candle.low)
        self.closes.append(candle.close)
        self.volumes.append(candle.volume)


class BotState:
    def __init__(self):
        self.timeBank = 0
        self.maxTimeBank = 0
        self.timePerMove = 1
        self.candleInterval = 1
        self.candleFormat = []
        self.candlesTotal = 0
        self.candlesGiven = 0
        self.initialStack = 0
        self.transactionFee = 0.1
        self.date = 0
        self.stacks = dict()
        self.charts = dict()
        self.isDown = False
        self.isUp = False

    def update_chart(self, pair: str, new_candle_str: str):
        if not (pair in self.charts):
            self.charts[pair] = Chart()
        new_candle_obj = Candle(self.candleFormat, new_candle_str)
        self.charts[pair].add_candle(new_candle_obj)

    def update_stack(self, key: str, value: float):
        self.stacks[key] = value

    def update_settings(self, key: str, value: str):
        if key == "timebank":
            self.maxTimeBank = int(value)
            self.timeBank = int(value)
        if key == "time_per_move":
            self.timePerMove = int(value)
        if key == "candle_interval":
            self.candleInterval = int(value)
        if key == "candle_format":
            self.candleFormat = value.split(",")
        if key == "candles_total":
            self.candlesTotal = int(value)
        if key == "candles_given":
            self.candlesGiven = int(value)
        if key == "initial_stack":
            self.initialStack = int(value)
        if key == "transaction_fee_percent":
            self.transactionFee = float(value)

    def update_game(self, key: str, value: str):
        if key == "next_candles":
            new_candles = value.split(";")
            self.date = int(new_candles[0].split(",")[1])
            for candle_str in new_candles:
                candle_infos = candle_str.strip().split(",")
                self.update_chart(candle_infos[0], candle_str)
        if key == "stacks":
            new_stacks = value.split(",")
            for stack_str in new_stacks:
                stack_infos = stack_str.strip().split(":")
                self.update_stack(stack_infos[0], float(stack_infos[1]))


if __name__ == "__main__":
    mybot = Bot()
    mybot.run()
