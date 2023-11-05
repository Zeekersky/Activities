import numpy as np
import matplotlib.pyplot as plt
with np.load('mnist.npz', allow_pickle=True) as f:
    x_train, y_train = f['x_train'], f['y_train']
    x_test, y_test = f['x_test'], f['y_test']
    
def power_iteration(matrix, num_iterations=1000):
    vector = np.random.rand(matrix.shape[0])
    for _ in range(num_iterations):
        matrix_vector_product = np.dot(matrix, vector)
        eigenvalue = np.linalg.norm(matrix_vector_product)
        vector = matrix_vector_product / eigenvalue
    return eigenvalue, vector

def eigen_decomposition(matrix):
    eigenvalues = []
    eigenvectors = []
    for _ in range(matrix.shape[0]):
        eigenvalue, eigenvector = power_iteration(matrix)
        eigenvalues.append(eigenvalue)
        eigenvectors.append(eigenvector)
        matrix -= eigenvalue * np.outer(eigenvector, eigenvector)
    eigenvalues = np.array(eigenvalues)
    eigenvectors = np.array(eigenvectors)
    return eigenvalues, eigenvectors.T    


def data_matrix_prep(train_images, bins=256):
    number_images = train_images.shape[0]
    data_mat = np.zeros((number_images, bins))
    for i in range(number_images):
        histogram, _ = np.histogram(train_images[i], bins=bins, range=(0,256))
        histogram = histogram / histogram.sum()
        data_mat[i] = histogram
    return data_mat

def svd_eigen_decomp(x):
    eigenValue, eigenVector = eigen_decomposition(np.dot(x.T, x))
    singular_value = np.sqrt(eigenValue)
    sorted_index = np.argsort(singular_value)[::-1]
    singular_value = singular_value[sorted_index]
    eigenVector = eigenVector[:,sorted_index]
    return eigenVector, singular_value

def recompute_x(x, eigenVector, k):
    top_eigenVector = eigenVector[:,:k]
    # print(top_eigenVector.shape)
    recomp_x = np.dot(x, top_eigenVector)
    recomp_x = np.dot(recomp_x, top_eigenVector.T)
    return recomp_x

x = data_matrix_prep(x_train, bins = 256)

eigenVector, singular_value = svd_eigen_decomp(x)
recompute_errors = []
for k in range(1, min(x.shape)+1):
    recomputed_x = recompute_x(x, eigenVector, k)
    error = np.linalg.norm(x - recomputed_x)
    recompute_errors.append(error)
    
plt.figure()
plt.plot(range(1, min(x.shape)+1), recompute_errors)
plt.xlabel('Number of Singular Vector (k)')
plt.ylabel('Reconstructed Error')
plt.title('SVD Reconstruction Error')
plt.show()