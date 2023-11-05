import cv2
import numpy as np
import os
import pandas as pd

def rgb_to_gray(image):
    R, G, B = image[:,:,0], image[:,:,1], image[:,:,2]
    gray = 0.299 * R + 0.587 * G + 0.114 * B
    gray = np.clip(gray, 0, 255)
    gray = gray.astype(np.uint8)
    return gray

def calculate_lbp(image):
    gray = rgb_to_gray(image)
    lbp_image = np.zeros_like(gray)
    for i in range(1, gray.shape[0] - 1):
        for j in range(1, gray.shape[1] - 1):
            center = gray[i, j]
            code = 0
            code = code | ((gray[i-1, j-1] > center) << 7)
            code = code | ((gray[i-1, j] > center) << 6)
            code = code | ((gray[i-1, j+1] > center) << 5)
            code = code | ((gray[i, j+1] > center) << 4)
            code = code | ((gray[i+1, j+1] > center) << 3)
            code = code | ((gray[i+1, j] > center) << 2)
            code = code | ((gray[i+1, j-1] > center) << 1)
            code = code | ((gray[i, j-1] > center) << 0)
            lbp_image[i-1, j-1] = code
    return lbp_image

def histogram(data, bins=256, range=[0, 256]):
    hist = np.zeros(bins, dtype=np.int)
    for value in data:
        hist[value] += 1
    return hist

def extract_lbp_features(directory):
    features = []
    labels = []
    for filename in os.listdir(directory):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            img_path = os.path.join(directory, filename)
            img = cv2.imread(img_path)
            lbp_image = calculate_lbp(img)
            hist = histogram(lbp_image.ravel(), bins=256, range=[0, 256])
            hist = hist.astype("float")
            hist /= (hist.sum() + 1e-6)
            label = os.path.splitext(filename)[0]
            features.append(hist)
            labels.append(label)
                
    return np.array(features), np.array(labels)

train_directory = "Train"
val_directory = "Val"
test_directory = "Test"

train_features, train_labels = extract_lbp_features(train_directory)
val_features, val_labels = extract_lbp_features(val_directory)
test_features, test_labels = extract_lbp_features(test_directory)

train_df = pd.DataFrame(data=train_features)
train_df["label"] = train_labels
train_df.to_csv("Train.csv", index=False)

val_df = pd.DataFrame(data=val_features)
val_df["label"] = val_labels
val_df.to_csv("Val.csv", index=False)

test_df = pd.DataFrame(data=test_features)
test_df["label"] = test_labels
test_df.to_csv("Test.csv", index=False)

