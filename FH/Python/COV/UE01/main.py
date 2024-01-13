import numpy as np

# Given points
Pi = np.array([
    [0.5, -1, 0.1, -3, 4, 7, 5, -6],
    [3, -7, 6, 2, 2, 3, -8, 14]
]).T

# Correlated points
P_i = np.array([
    [3.23276, 10.5156, -1.81063, -6.13936, 15.3104, 22.7094, 27.7362, -28.6905],
    [1.85478, -31.9384, 10.546, -5.25041, 3.0516, 10.0762, -27.2918, 25.7473]
]).T

# Initialize variables to keep track of the best transformation parameters
best_s, best_rot, best_Tx, best_Ty = 1.0, 0.0, 0.0, 0.0
min_error = float('inf')

# Create a range of values to search for each parameter
scale_range = np.linspace(0.9, 1.1, 21)  # Scale factor range
rotation_range = np.linspace(-np.pi, np.pi, 361)  # Rotation angle range (-180 to 180 degrees)
Tx_range = np.linspace(-5, 5, 201)  # Translation in x range
Ty_range = np.linspace(-5, 5, 201)  # Translation in y range

# Brute-force search
for s in scale_range:
    for rot in rotation_range:
        for Tx in Tx_range:
            for Ty in Ty_range:
                # Calculate the transformation matrix
                transformation_matrix = np.array([
                    [s * np.cos(rot), -s * np.sin(rot), Tx],
                    [s * np.sin(rot), s * np.cos(rot), Ty],
                ])

                # Apply the transformation to Pi
                Pi_transformed = np.dot(transformation_matrix, np.vstack((Pi.T, np.ones(Pi.shape[0])))).T

                # Calculate the error (squared Euclidean distance)
                error = np.sum((Pi_transformed - P_i) ** 2)

                # Check if this set of parameters results in a smaller error
                if error < min_error:
                    best_s, best_rot, best_Tx, best_Ty = s, rot, Tx, Ty
                    min_error = error
                    print(error)

# The best transformation parameters are in best_s, best_rot, best_Tx, and best_Ty
print("Best Scale (s):", best_s)
print("Best Rotation (rot):", best_rot)
print("Best Translation in X (Tx):", best_Tx)
print("Best Translation in Y (Ty):", best_Ty)
