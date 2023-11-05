import numpy as np

def linear_kernel(X, Y):
    return np.dot(X, Y.T)

def polynomial_kernel(X, Y, degree=2):
    return (np.dot(X, Y.T) + 1) ** degree

def rbf_kernel(X, Y, sigma=1.0):
    X_norm = np.sum(X**2, axis=-1)
    Y_norm = np.sum(Y**2, axis=-1)
    pairwise_dists = -2 * np.dot(X, Y.T) + (X_norm[:, None] + Y_norm[None, :])
    return np.exp(-pairwise_dists / (2.0 * sigma**2))


with np.load("mnist.npz") as data:
    images, labels = data['x_train'], data['y_train']

def calculate_lbp(image, radius=1, n_points=8):
    height, width = image.shape
    lbp_image = np.zeros((height - 2 * radius, width - 2 * radius), dtype=np.uint8)
    for i in range(radius, height - radius):
        for j in range(radius, width - radius):
            center = image[i, j]
            binary_values = []
            for x in range(i - radius, i + radius + 1):
                for y in range(j - radius, j + radius + 1):
                    if x != i or y != j:
                        binary_values.append(int(image[x, y] >= center))
            lbp_value = sum([v * (2**i) for i, v in enumerate(binary_values)])
            lbp_image[i - radius, j - radius] = lbp_value
    return lbp_image

flattened_images = images.reshape(images.shape[0], -1)

lbp_images = np.array([calculate_lbp(image.reshape(28, 28)) for image in images])


# Compute kernel matrices
linear_kernel_flattened = linear_kernel(flattened_images, flattened_images)
poly_kernel_flattened = polynomial_kernel(flattened_images, flattened_images, degree=2)
rbf_kernel_flattened = rbf_kernel(flattened_images, flattened_images, sigma=1.0)

linear_kernel_lbp = linear_kernel(lbp_images, lbp_images)
poly_kernel_lbp = polynomial_kernel(lbp_images, lbp_images, degree=2)
rbf_kernel_lbp = rbf_kernel(lbp_images, lbp_images, sigma=1.0)

