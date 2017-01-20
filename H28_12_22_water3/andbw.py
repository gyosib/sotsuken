import numpy as np
import cv2
import os
import os.path
import csv
import sys
import datetime

#Two data -> 1(white) or 0(black)
def countone(path_input_dir,path_output_dir):
	num_base = 20 #number of base file
	num_con = 500 #number of com
	count_table = [] #count table

	#make count table
	for tmp_counter in range(num_con):
		count_table.append(0)
	

	args = sys.argv

	f_write = open(path_output_dir+args[1],'w')

	for base_count in range(num_base):
		f_base = open(path_input_dir+str(base_count*30)+'.txt','r')
		csvBase = csv.reader(f_base)
		data_base = [v for v in csvBase]
		i = 0
		while(True):
			path = path_input_dir+str(i+int(base_count*30))+'.txt'
			if(not os.path.exists(path) or i >=500):
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
					if(pix == args[2] and pix == row_base[k]):
						count = count + 1
					k = k + 1
				j = j+1
			count_table[i] = count_table[i] + count
			i = i+1
		print(base_count)
		
	for l in range(num_con):
		result = str(l/5000) + ' ' + str(count_table[l]/count_table[0])+'\n'
		f_write.write(result)
		
	f_base.close()
	f_targ.close()
	f_write.close()

countone('out/two/txt/','number/')
cv2.destroyAllWindows()
