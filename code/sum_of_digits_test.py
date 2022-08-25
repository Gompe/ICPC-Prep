# -*- coding: utf-8 -*-
"""
Created on Wed Jun 30 19:43:44 2021

@author: gomes
"""

import random

N = 180
p = .8
b_str = ''
a_str = ''
taken = set()
n = 0
k = 1

def sum_of_digits(num):
    aout = 0
    while(num != 0):
        aout += num%10
        num = num//10
    return aout
        
while n<=N:
    s10 = sum_of_digits(k)
    if random.random() < p and s10 not in taken:
        b_str += "{}\n".format(sum_of_digits(k))
        a_str += "{}\n".format(k)
        n += 1
    else:
        taken.add(s10)
    k+=1
        
with open("sof_input.txt", 'w') as file:
    file.write(str(n)+'\n'+b_str)

with open("sof_output.txt", 'w') as file:
    file.write(a_str)