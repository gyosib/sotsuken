import numpy as np
import cv2
import os

def video_to_frames():
	param = 25
	image1 = cv2.imread('./0-1.png', 1)
	image2 = cv2.imread('./0-2.png', 1)
	image3 = cv2.imread('./0-3.png', 1)
	gray1 = cv2.cvtColor(image1,cv2.COLOR_BGR2GRAY)	
	gray2 = cv2.cvtColor(image2,cv2.COLOR_BGR2GRAY)	
	gray3 = cv2.cvtColor(image3,cv2.COLOR_BGR2GRAY)	
	height, width = image1.shape[:2]
	ret1, dst1 = cv2.threshold(gray1,param,255,cv2.THRESH_BINARY)
	ret2, dst2 = cv2.threshold(gray2,param,255,cv2.THRESH_BINARY)
	ret3, dst3 = cv2.threshold(gray3,param,255,cv2.THRESH_BINARY)
	cv2.imwrite("two1.png",dst1)
	cv2.imwrite("two2.png",dst2)
	cv2.imwrite("two3.png",dst3)
	cv2.destroyAllWindows()

video_to_frames()
