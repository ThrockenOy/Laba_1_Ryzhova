
import matplotlib.pyplot as plt
import numpy as np

def f(x):
    return x**2

def df(x):
    return 2*x

def F(x):
    return x**3 / 3


x = np.linspace(0, 1, 100)

y = f(x)
y_prime = df(x)
y_primitive = F(x)


plt.plot(x, y, label="f(x) = x^2")
plt.plot(x, y_prime, label="f'(x) = 2x")
plt.plot(x, y_primitive, label="F(x) = x^3/3")

plt.xlabel("x")
plt.ylabel("y")
plt.title("Графики функции, производной и первообразной")
plt.legend()
plt.grid(True)

plt.show()

'''
import matplotlib.pyplot as plt
import numpy as np

# функция и аналитическая площадь
def f(x):
    return x**2

exact_area = 1/3  # аналитическая площадь интеграла от 0 до 1

# список количества прямоугольников
N_values = [1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000]

areas = []

# считаем площадь методом левых прямоугольников
for N in N_values:
    dx = 1.0 / N
    S = 0.0
    for i in range(N):
        x = i * dx  # левый край
        S += f(x) * dx
    areas.append(S)

# строим график
plt.plot(N_values, areas, marker='o', label="Приближение методом прямоугольников")
plt.axhline(y=exact_area, color='r', linestyle='--', label="Аналитическая площадь")
plt.xlabel("Количество прямоугольников N")
plt.ylabel("Вычисленная площадь")
plt.title("Сходимость метода прямоугольников к аналитической площади")
plt.xscale("log")  # логарифмическая ось, чтобы было нагляднее
plt.legend()
plt.grid(True)
plt.show()
'''
'''
import matplotlib.pyplot as plt
import numpy as np


def f(x):
    return x**2

square = 1/3  


N_values = [1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000]

s_float = []
s_double = []

for N in N_values:
    dx_f = np.float32(1.0 / N)
    dx_d = 1.0

    S_f = np.float32(0.0)
    S_d = 0.0

    for i in range(N):
        x_f = np.float32(i) * dx_f
        S_f += np.float32(f(x_f) * dx_f)

        x_d = i * dx_d / N
        S_d += f(x_d) * dx_d / N

    s_float.append(S_f)
    s_double.append(S_d)


plt.plot(N_values, s_float, marker='o', label=" Площадь float")
plt.plot(N_values, s_double, marker='x', label="Площадь double")
plt.axhline(y=square, color='r', linestyle='--', label="Аналитическая площадь")
plt.xlabel("Количество прямоугольников N")
plt.ylabel("Вычисленная площадь")
plt.title("Сравнение точности float и double")
plt.xscale("log")
plt.legend()
plt.grid(True)
plt.show()
'''
