import numpy as np
import cv2
import os
import os.path
import csv
import sys
import datetime

#Two data -> 1(white) or 0(black)
def countone(path_input_dir,path_output_dir):
	i = 0
	print(i)

	args = sys.argv

	f_base = open(path_input_dir+args[1]+'.txt','r')
	f_write = open(path_output_dir+args[2],'w')
	csvBase = csv.reader(f_base)
	data_base = [v for v in csvBase]

	result = ''
	while(True):
		i = i+1
		path = path_input_dir+str(i)+'.txt'
		if(not os.path.exists(path)):
			#no File
			break
		f_targ = open(path,'r')
		csvRender = csv.reader(f_targ)
		data_targ = [v for v in csvRender]
		j = 0
		count = 0
		for row in data_targ:
			row_base = data_base[j]
			k = 0
			for pix in row:
				#print([pix,row_base[k]])
				if(pix == '1' and pix == row_base[k]):
					count = count + 1
				k = k + 1
			j = j+1
		print(i)
		result += str(count)+'\n'
	f_write.write(result)
	f_base.close()
	f_targ.close()
	f_write.close()

countone('out/two/txt/','out/two/txt/and/')
cv2.destroyAllWindows()
