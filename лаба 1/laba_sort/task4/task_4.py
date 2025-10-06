import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("C:/Users/Krist/Desktop/mipt/инф/лаба 1/laba_sort/task4/results_heap.csv", sep=None, engine='python')

# Убираем лишние пробелы в названиях
df.columns = df.columns.str.strip()

# Преобразуем в широкий формат: строки - размер, колонки - case
df_wide = df.pivot(index='size', columns='case', values='heap_ms')

print(df_wide.head())

# Строим график
plt.plot(df_wide.index, df_wide['best'], 'o--', label='Лучший случай')
plt.plot(df_wide.index, df_wide['average'], 's--', label='Средний случай')
plt.plot(df_wide.index, df_wide['worst'], 'd--', label='Худший случай')

plt.title("Heap sort — сравнение случаев")
plt.xlabel("Размер массива")
plt.ylabel("Время (мс)")
plt.legend()
plt.show()
