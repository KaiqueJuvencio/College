import numpy as np
#print(np.cos(0.5))
e = np.finfo(float).eps

def func(x):
    return (x*np.cos(x)) - 2*(x**2) + 3 * x - 1

def bisection(a, b, epsilon):
    if func(a) * func(b) >= 0:
        return

    meio = a
    # for i in range(0,10):
    while (b - a) >= epsilon:
        meio = (a + b) / 2

        if func(meio) == 0.0:
            break
        if func(meio) * func(a) < 0:
            b = meio
        else:
            a = meio

    print("Raiz: ", "%.4f" % meio)

a = 1.2
b = 1.3
epsilon = 0.01
bisection(a, b, epsilon)
