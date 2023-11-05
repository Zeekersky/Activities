import cv2
import numpy as np
import matplotlib.pyplot as plt

img1 = cv2.imread('pic_a.jpg')
img2 = cv2.imread('pic_b.jpg')

p1 = np.array([[x,y] for x in range(img1.shape[1]) for y in range(img1.shape[0])])
p2 = np.array([[x,y] for x in range(img2.shape[1]) for y in range(img2.shape[0])])

def normalization(p):
    mean = np.mean(p, axis=0)
    std = np.std(p)
    return (p - mean) / std

normalized_p1 = normalization(p1)
normalized_p2= normalization(p2)

a = np.zeros((p1.shape[0], 9))
for i in range(p1.shape[0]):
    a[i] = [
        normalized_p1[i][0] * normalized_p2[i][0],
        normalized_p1[i][0] * normalized_p2[i][1],
        normalized_p1[i][0],
        normalized_p1[i][1] * normalized_p2[i][0],
        normalized_p1[i][1] * normalized_p2[i][1],
        normalized_p1[i][1],
        normalized_p2[i][0],
        normalized_p2[i][1],
        1
        ]
    
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

def svd(a):
    mat = np.dot(a.T, a)
    eigenValue, eigenVector = eigen_decomposition(mat)
    sorted_index = np.argsort(eigenValue)[::-1]
    eigenValue = eigenValue[sorted_index]
    eigenVector = eigenVector[:, sorted_index]
    tol = np.finfo(float).eps * max(a.shape) * eigenValue[0]
    singularValue = np.sqrt(np.maximum(eigenValue, tol))
    u = np.dot(a, eigenVector) / singularValue
    vt = eigenVector.T
    return u, singularValue, vt


_, _, v = svd(a)
fd = v[-1,:].reshape(3,3)

u, singularValue, vt = svd(fd)
singularValue[2] = 0
f = np.dot(u, np.dot(np.diag(singularValue), vt))

def epipolar(f):
    u,_,vt = svd(f)
    e1 = vt[-1,:]
    _,_,vt = svd(f.T)
    e2 = vt[-1,:]
    return e1/e1[2], e2/e2[2]

e1, e2 = epipolar(f)

t1 = np.array([[1, 0, 0], [0, 1, 0], [-e1[0], -e1[1], 1]])
t2 = np.array([[1, 0, 0], [0, 1, 0], [-e2[0], -e2[1], 1]])

# def perspective(img, t, outputShape):
#     outputImg = np.zeros(outputShape, dtype=np.uint8)
#     for y in range(outputShape[0]):
#         for x in range(outputShape[1]):
#             p = np.dot(np.linalg.inv(t), np.array([x, y, 1]))
#             p = p/p[2]
#             org_x, org_y = int(np.floor(p[0])), int(np.floor(p[1]))
#             if 0 <= org_x < img.shape[1] and 0 <= org_y < img.shape[0]:
#                 outputImg[y,x] = img[org_y, org_x]
#     return outputImg

# rectifiedImg1 = perspective(img1, t1, (img1.shape[0], img1.shape[1]))
# rectifiedImg2 = perspective(img2, t2, (img2.shape[0], img2.shape[1]))


# plt.figure()
# plt.subplot(2,2,1)
# plt.imshow(img1)
# plt.title("Image 1 (original)")
# plt.axis("off")

# plt.subplot(2,2,2)
# plt.imshow(img2)
# plt.title("Image 2 (original)")
# plt.axis("off")

# plt.subplot(2,2,3)
# plt.imshow(rectifiedImg1)
# plt.title("Image 1 (rectified)")
# plt.axis("off")

# plt.subplot(2,2,4)
# plt.imshow(rectifiedImg2)
# plt.title("Image 2 (rectified)")
# plt.axis("off")

# plt.tight_layout()
# plt.show()
    
    
    
    