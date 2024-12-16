import pandas as pd
import os
import matplotlib.pyplot as plt
import numpy as np

# Get the directory of the current script
script_dir = os.path.dirname(__file__)
# Construct the relative path to the dataset
csv_path = os.path.join(script_dir, '../data/imu_dataset.csv')

# Load the dataset using the dynamically constructed path
df = pd.read_csv(csv_path)

# Display the first few rows to confirm it loaded correctly
print(df.shape)
print(df.info())
print(df.describe())

# plt.figure(figsize=(8, 6))
# plt.hist(df['acc_x'], bins=30, edgecolor='black', alpha=0.7)
# plt.title("Distribution of acc_x")
# plt.xlabel("acc_x")
# plt.ylabel("Frequency")
# plt.grid(True)
# plt.show()

# df['residual'] = 9.81 - df['acc_x']

# variance_residual = df['residual'].var()
# std_residual = df['residual'].std()

# print(f"Variance of residual: {variance_residual}")
# print(f"Standard Deviation of residual: {std_residual}")

plt.figure(figsize=(8, 6))
plt.hist(df['acc_x'], bins=30, edgecolor='black', alpha=0.7)
plt.title("Distribution of acc_x")
plt.xlabel("Residual")
plt.ylabel("Frequency")
plt.grid(True)
plt.show()