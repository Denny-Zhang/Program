# 參考資料:https://matplotlib.org/tutorials/introductory/pyplot.html
import matplotlib.pyplot as plt
import numpy as np

t = [np.arange(-5,5.0,0.001),np.arange(-0.008,0.008, 0.0001),np.arange(-0.01,0.01, 0.0001)]
s = [np.cos(2*np.pi*t[0]),3*np.cos(250 * np.pi * t[1] + 125 * np.pi),123*np.cos(456 * np.pi * t[2] + 789 * np.pi)]

for x in range(3):
    plt.figure(x+1)
    plt.plot(t[x], s[x])

title = ['Wave-1','Wave-2','Wave-3']
for x in title:
    plt.figure(title.index(x)+1)
    plt.title(x)
    plt.xlabel("time(s)")
plt.show()
