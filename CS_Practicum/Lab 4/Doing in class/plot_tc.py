# -*- coding: utf-8 -*-
"""
Created on Wed Sep 20 16:39:34 2023

@author: Akash
"""

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('pypl.txt')
# Separate the data into x and y values
x = data[:, 0]
y = data[:, 1]
z = data[:, 2]


seq = [i for i in range(len(data))]
plt.plot(seq, y, color = 'r', label="Time_Rec")
plt.plot(seq, z, color = 'g', label="Time_DP")
# Add labels and a legend
plt.xlabel('N')
plt.ylabel('Time_Rec')
plt.legend()

plt.title('Time Complexity Comp')

plt.show()




