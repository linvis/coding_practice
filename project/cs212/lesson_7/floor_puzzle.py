#!/usr/bin/env python
# -*- coding=utf8 -*-

import itertools

def floor_puzzle():
    # Your code here
    floor = bottom, _, _, _, top = [1, 2, 3, 4, 5]
    orders = list(itertools.permutations(floor))
    for Hopper, Kay, Liskov, Perlis, Ritchie in orders:
        if (Hopper is not top
            and Kay is not bottom
            and Liskov is not top
            and Liskov is not bottom
            and Perlis - Kay > 0
            and abs(Ritchie - Liskov) > 1
            and abs(Liskov - Kay) > 1):
            return [Hopper, Kay, Liskov, Perlis, Ritchie]

print(floor_puzzle())
