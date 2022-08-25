# -*- coding: utf-8 -*-
"""
Created on Tue Jun 29 03:05:51 2021

@author: gomes
"""

import random

n = 60000
s = str(n)+'\n'

for _ in range(n):
    a = random.randint(-50, 50)
    s += str(a)+' '

with open('potions_input.txt', 'w') as file:
    file.write(s)
    
    