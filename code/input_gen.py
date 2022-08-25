# -*- coding: utf-8 -*-
"""
Created on Mon Jun 28 16:59:09 2021

@author: gomes
"""

import random

with open('random_string.txt', 'w') as file:
    
    t = 10
    s = '';
    s += str(t) + '\n'
    for _ in range(t):
        n = random.randint(1, 1000)
        s+= str(n) + '\n'
        for _ in range(n):
            s += random.choice(['0', '1'])
        s+='\n'
    file.write(s)
        