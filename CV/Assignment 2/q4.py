import os
import numpy as np
from PIL import Image
import math

# Function to calculate gradients using Sobel operators
def calculateGradients(image):
    sobel_x = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
    sobel_y = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
    
    gradient_x = [[0 for _ in range(len(image[0]))] for _ in range(len(image))]
    gradient_y = [[0 for _ in range(len(image[0]))] for _ in range(len(image))]
    
    for i in range(1, len(image) - 1):
        for j in range(1, len(image[0]) - 1):
            gx = (sobel_x[0][0] * image[i - 1][j - 1] + sobel_x[0][1] * image[i - 1][j] + sobel_x[0][2] * image[i - 1][j + 1] +
                  sobel_x[1][0] * image[i][j - 1] + sobel_x[1][1] * image[i][j] + sobel_x[1][2] * image[i][j + 1] +
                  sobel_x[2][0] * image[i + 1][j - 1] + sobel_x[2][1] * image[i + 1][j] + sobel_x[2][2] * image[i + 1][j + 1])
            
            gy = (sobel_y[0][0] * image[i - 1][j - 1] + sobel_y[0][1] * image[i - 1][j] + sobel_y[0][2] * image[i - 1][j + 1] +
                  sobel_y[1][0] * image[i][j - 1] + sobel_y[1][1] * image[i][j] + sobel_y[1][2] * image[i][j + 1] +
                  sobel_y[2][0] * image[i + 1][j - 1] + sobel_y[2][1] * image[i + 1][j] + sobel_y[2][2] * image[i + 1][j + 1])
            
            gradient_x[i][j] = gx
            gradient_y[i][j] = gy
    
    return gradient_x, gradient_y

# Function to calculate HOG features for a cell
def calculateCellHistogram(magnitude, gradient_x, gradient_y, num_bins=9):
    histogram = [0] * num_bins
    bin_width = 180 / num_bins
    
    for i in range(len(magnitude)):
        for j in range(len(magnitude[0])):
            gradient_angle = math.degrees(math.atan2(gradient_y[i][j], gradient_x[i][j])) % 180
            weight = 1 - abs(magnitude[i][j] - 1)  # Tri-linear interpolation
            
            bin_index_low = int(gradient_angle // bin_width) % num_bins
            bin_index_high = (bin_index_low + 1) % num_bins
            
            histogram[bin_index_low] += (1 - (gradient_angle % bin_width) / bin_width) * weight * magnitude[i][j]
            histogram[bin_index_high] += ((gradient_angle % bin_width) / bin_width) * weight * magnitude[i][j]
    
    return histogram

# Function to calculate HOG features for an image
def calculateHOGFeatures(image, cell_size=(8, 8), block_size=(2, 2), num_bins=9):
    gradient_x, gradient_y = calculateGradients(image)
    magnitude = [[math.sqrt(gradient_x[i][j] ** 2 + gradient_y[i][j] ** 2) for j in range(len(gradient_x[0]))] for i in range(len(gradient_x))]
    
    cell_histograms = []
    for i in range(0, len(magnitude), cell_size[0]):
        for j in range(0, len(magnitude[0]), cell_size[1]):
            cell_magnitude = [magnitude[p][j:j+cell_size[1]] for p in range(i, i+cell_size[0])]
            cell_histogram = calculateCellHistogram(cell_magnitude, gradient_x[i:i+cell_size[0]], gradient_y[i:i+cell_size[0]], num_bins)
            cell_histograms.append(cell_histogram)
    
    return [item for sublist in cell_histograms for item in sublist]

# Function to process images from a directory and save HOG features and labels to CSV
def process_images(directory, output_csv):
    features = []
    labels = []
    for filename in os.listdir(directory):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            img_path = os.path.join(directory, filename)
            img = np.array(Image.open(img_path).convert('L'))  # Convert to grayscale
            hog_features = calculateHOGFeatures(img)
            features.append(hog_features)
            label = os.path.splitext(filename)[0]
            labels.append(label)
    
    with open(output_csv, 'w') as f:
        for feature, label in zip(features, labels):
            line = ",".join(map(str, feature)) + "," + label + "\n"
            f.write(line)

# Paths to train, validation, and test directories
train_directory = "Train"
val_directory = "Val"
test_directory = "Test"

# Generate CSV files for train, validation, and test data
process_images(train_directory, "Train.csv")
process_images(val_directory, "Val.csv")
process_images(test_directory, "Test.csv")
