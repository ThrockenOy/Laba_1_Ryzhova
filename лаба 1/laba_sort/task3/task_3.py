import pandas as pd
import matplotlib.pyplot as plt


df1 = pd.read_csv("C:/Users/Krist/Desktop/mipt/инф/лаба 1/laba_sort/task3/results.csv", sep=';')
df2 = pd.read_csv("results_task2.csv", sep=';')


sizes = df1['size']


plt.figure(figsize=(10,6))
#  (O(n²))
plt.plot(sizes, df1['bubble_ms'], 'o-', label='Bubble (O(n²))')
plt.plot(sizes, df1['insertion_ms'], 's-', label='Insertion (O(n²))')
plt.plot(sizes, df1['shaker_ms'], 's-', label='shaker (O(n²))')
#  (O(n log n))
plt.plot(sizes, df2['merge_ms'], 'o--', label='Merge (O(n log n))')
plt.plot(sizes, df2['quick_ms'], 's--', label='Quick (O(n log n))')
plt.plot(sizes, df2['heap_ms'], 's--', label='Heap (O(n log n))')


plt.yscale('log')  # логарифмическая шкала по времени
plt.xlabel('Array size (N)')
plt.ylabel('Time (ms, log scale)')
plt.title('Comparison of O(n²) and O(n log n) sorting algorithms')
plt.grid(True, which='both', ls='--', alpha=0.6)
plt.legend()
plt.tight_layout()
plt.show()
