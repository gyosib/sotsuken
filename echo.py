import numpy as np
import cv2,matplotlib
import matplotlib.pyplot as plt

img = cv2.imread('free.jpg')
size_x = img.shape[0]
size_y = img.shape[1]
for i in range(0,size_y):
	for j in range(0,size_x):
		print(img[j,i])
