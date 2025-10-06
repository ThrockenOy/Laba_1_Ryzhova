
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results_task2.csv", sep=';')

df.columns = df.columns.str.strip()

print(df.head())
print("Columns:", df.columns)

plt.figure(figsize=(10,6))
plt.plot(df['size'], df['merge_ms'], marker='o', linestyle='-', color='blue', label='merge Sort')
plt.plot(df['size'], df['quick_ms'], marker='s', linestyle='--', color='green', label='quick Sort')
plt.plot(df['size'], df['heap_ms'], marker='^', linestyle='-.', color='red', label='heap Sort')

plt.title("Sorting Algorithms Time vs Array Size")
plt.xlabel("Array Size (n)")
plt.ylabel("Time (ms)")
plt.grid(True)
plt.xticks(df['size'])
plt.legend()  
plt.show()
'''
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("results_task2.csv", sep=';')

df.columns = df.columns.str.strip()

print(df.head())
print("Columns:", df.columns)


df['merge_norm'] = df['merge_ms'] / (df['size'] * np.log2(df['size']))
df['quick_norm'] = df['quick_ms'] / (df['size'] * np.log2(df['size']))
df['heap_norm']  = df['heap_ms']  / (df['size'] * np.log2(df['size']))

plt.figure(figsize=(10,6))
plt.plot(df['size'], df['merge_ms'], marker='o', linestyle='-', color='blue', label='merge Sort')
plt.plot(df['size'], df['quick_ms'], marker='s', linestyle='--', color='green', label='quick Sort')
plt.plot(df['size'], df['heap_ms'], marker='^', linestyle='-.', color='red', label='heap Sort')

plt.title("t / (N log N) vs N for O(N log N) Sorting Algorithms")
plt.xlabel("t / (N log N)")
plt.ylabel("Time (ms)")
plt.yscale('log')
plt.grid(True)
plt.xticks(df['size'])
plt.legend()
'''
plt.show()
