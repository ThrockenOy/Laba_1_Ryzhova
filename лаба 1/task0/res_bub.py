'''
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv", sep=';')

df.columns = df.columns.str.strip()

print(df.head())
print("Columns:", df.columns)

plt.figure(figsize=(10,6))
plt.plot(df['size'], df['bubble_ms'], marker='o', linestyle='-', color='blue', label='Bubble Sort')
plt.plot(df['size'], df['insertion_ms'], marker='s', linestyle='--', color='green', label='Insertion Sort')
plt.plot(df['size'], df['shaker_ms'], marker='^', linestyle='-.', color='red', label='Shaker Sort')

plt.title("Sorting Algorithms Time vs Array Size")
plt.xlabel("Array Size (n)")
plt.ylabel("Time (ms)")
plt.grid(True)
plt.xticks(df['size'])
plt.legend()  # показываем легенду
plt.show()

'''
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


df = pd.read_csv("results.csv", sep=';')

df.columns = df.columns.str.strip()

print(df.head())
print("Columns:", df.columns)

# Двойной логарифмический график для проверки O(n^2)
ln_n = np.log(df['size'])
ln_t_bubble = np.log(df['bubble_ms'])
ln_t_insertion = np.log(df['insertion_ms'])
ln_t_shaker = np.log(df['shaker_ms'])

plt.figure(figsize=(10,6))
plt.plot(ln_n, ln_t_bubble, marker='o', linestyle='-', color='blue', label='Bubble Sort')
plt.plot(ln_n, ln_t_insertion, marker='s', linestyle='--', color='green', label='Insertion Sort')
plt.plot(ln_n, ln_t_shaker, marker='^', linestyle='-.', color='red', label='Shaker Sort')

plt.title("Double Logarithmic Plot (ln Time vs ln Array Size)")
plt.xlabel("ln(Array Size)")
plt.ylabel("ln(Time, ms)")
plt.grid(True)
plt.legend()
plt.show()
