import numpy as np

X = np.array([[1, 2, 3], 
              [4, 5, 6]])
              
# Scatter matrix
scatter_matrix = X @ X.T
print("Scatter Matrix:\n", scatter_matrix)
