import numpy as np
import cv2
import sys

argvs = sys.argv

img = cv2.imread("iron/two/0.png",1)
img1 = cv2.imread("iron/two/"+argvs[1]+".png",cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread("iron/two/"+argvs[2]+".png",cv2.IMREAD_GRAYSCALE)

height = img.shape[0]
width = img.shape[1]

cv2.rectangle(img,(0,0),(width,height),(0,0,255),-1)
for h in range(0,height):
	for w in range(0,width):
		pixel1 = img1[h,w]
		pixel2 = img2[h,w]
		if(pixel1 == pixel2):
			img[h,w] = img1[h,w]

cv2.imwrite(argvs[1]+"and"+argvs[2]+".png",img)
