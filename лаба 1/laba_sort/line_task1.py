import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("all_the_results_ins.csv")  
df.columns = df.columns.str.strip()
df = pd.read_csv("all_the_results_ins.csv", sep=';')


print(df.head())



plt.figure(figsize=(10,6))
plt.plot(df['size'], df['o0'], marker='o', linestyle='-', color='blue', label='-O0')
plt.plot(df['size'], df['o1'], marker='s', linestyle='--', color='green', label='-O1')
plt.plot(df['size'], df['o2'], marker='^', linestyle='-.', color='orange', label='-O2')
plt.plot(df['size'], df['o3'], marker='x', linestyle=':', color='red', label='-O3')

plt.title("Insertion Sort Time vs Array Size for Different Optimizations")
plt.xlabel("Array Size (n)")
plt.ylabel("Time (ms)")
plt.grid(True)
plt.legend()
plt.show()

