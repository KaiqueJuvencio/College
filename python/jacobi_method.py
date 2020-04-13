import time
import timeit
import numpy
np = numpy
ini = timeit.default_timer()
def jacobi(A, b, ini, e=0.1, iteracoes=500):
    D = np.diag(np.diag(A))
    LU = A - D
    x = ini
    for i in range(iteracoes):
        D_inv = np.diag(1 / np.diag(D))
        x_n = np.dot(D_inv, b - np.dot(LU, x))
        if np.linalg.norm(x_n - x) < e:
            return x_n
        x = x_n
    return x

# Sistema Linear
A = np.array([
    [1, 1, 0, 1],
    [2, 1, -1, 1],
    [4, -1, -2, 2],
    [3, -1, -1, 2]
])
b = np.array([2, 1, 0, -3])

x_init = np.zeros(len(b))

x = jacobi(A, b, x_init)
fim = timeit.default_timer()
print("Tempo de execução: ", fim - ini)
print('Resultado:', x)



