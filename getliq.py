import numpy as np
import cv2
import os

def video_to_frames():
	image = cv2.imread('./back.png', 1)
	gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)	
	height, width = image.shape[:2]
	ret, dst = cv2.threshold(gray,25,255,cv2.THRESH_BINARY)
	cv2.imwrite("two.png",dst)
	cv2.destroyAllWindows()

video_to_frames()
