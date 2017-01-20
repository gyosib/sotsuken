import numpy as np
import cv2
import os
import os.path
import csv

#Two data -> 1(white) or 0(black)
def img_to_bw(path_input_dir,path_output_dir):
	# extract frames from a video and save to directory as 'x.png' where 
	# x is the frame index
	i = 0
	while(True and i<5000):
		# file path
		path = path_input_dir+str(i)+'.png'
		if(not os.path.exists(path)):
			#no File
			break
		# file open
		f = open(path_output_dir+str(i)+'.txt','w')
		csvWriter = csv.writer(f)
		
		img = cv2.imread(path,cv2.IMREAD_GRAYSCALE)
		height ,width = img.shape[:2]
		pixel_table = [[0 for j in range(width)] for k in range(height)]
		for h in range(0,height):
			for w in range(0,width):
				pixel = img[h,w]
				if(pixel == 255):
					pixel = 1
				pixel_table[h][w] = pixel
		print(i)
		csvWriter.writerows(pixel_table)
		f.close()
		i = i + 1

img_to_bw('out/two/','out/two/txt/')
cv2.destroyAllWindows()
