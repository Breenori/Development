import math

import numpy as np
import cv2
import matplotlib.pyplot as plt

def perona_malik_anisotropic_diffusion(image, iterations=10, delta_t=0.1, kappa=10):
    for i in range(iterations):
        gradients = np.gradient(image)
        gradient_magnitude = np.sqrt(gradients[0]**2 + gradients[1]**2)
        c = np.exp(-0.5 * (gradient_magnitude / kappa)**2)
        scaled_gradients = c * gradients
        gradient_delta = np.gradient(scaled_gradients[0])[0] + np.gradient(scaled_gradients[1])[1]
        image += delta_t * gradient_delta

    return image

inImg = cv2.imread("sahara.jpg")
inImg = cv2.cvtColor(inImg, cv2.COLOR_BGR2GRAY)
blurred = cv2.GaussianBlur(inImg, (11,11), 0)

# Set how many versions (different kappa)
n = 6
result_images = [None] * 10
plt.figure(figsize=(8, 4))

# first display original and gaussian blurred
cols = 3
plt.subplot(int(math.ceil(n/cols)), cols, 1)
plt.imshow(inImg, cmap='gray')
plt.title(f'Original image')

plt.subplot(int(math.ceil(n/cols)), cols, 2)
plt.imshow(blurred, cmap='gray')
plt.title(f'Gaussian Blur (11,11)')

for i in range(2, n):
    calc_kappa = 2 ** (i - 2)
    result_images[i] = perona_malik_anisotropic_diffusion(inImg.astype(float), iterations=50, kappa=calc_kappa)
    plt.subplot(int(math.ceil(n/cols)), cols, i+1)
    plt.imshow(result_images[i], cmap='gray')
    plt.title(f'K={calc_kappa}')

plt.show()

# now the same with differences
result_diff_images = [None] * 10
plt.figure(figsize=(8, 4))

# first display original and gaussian blurred
plt.subplot(int(math.ceil(n/cols)), cols, 1)
plt.imshow(cv2.subtract(inImg, inImg), cmap='gray')
plt.title(f'Original image')

plt.subplot(int(math.ceil(n/cols)), cols, 2)
plt.imshow(cv2.subtract(inImg, blurred), cmap='gray')
plt.title(f'Gaussian Blur (11,11)')

for i in range(2, n):
    calc_kappa = 2**(i - 2)
    result_diff_images[i] = cv2.subtract(perona_malik_anisotropic_diffusion(inImg.astype(float), iterations=50, kappa=calc_kappa).astype(np.uint8), inImg)
    plt.subplot(int(math.ceil(n/cols)), cols, i+1)
    plt.imshow(result_diff_images[i], cmap='gray')
    plt.title(f'K={calc_kappa}')

plt.show()
