import cv2
import os

def video_to_frames(video, path_output_dir):
	#Get video (mp4)
	vidcap = cv2.VideoCapture(video)
	count = 0
	while vidcap.isOpened():
		#Get a frame from video
		success, image = vidcap.read()
		if success:
			#Get info with frame
			height, width = image.shape[:2]
			#Trimming frame & Save
			tri = image[int(height/4)+18:height,0:width]
			cv2.imwrite(path_output_dir+"/tri/"+str(count)+".png",tri)
			#Binarization frame & Save
			gray = cv2.cvtColor(tri,cv2.COLOR_BGR2GRAY)
			ret, dst = cv2.threshold(gray,33,255,cv2.THRESH_BINARY)
			cv2.imwrite(path_output_dir+"/two/"+str(count)+".png",dst)
			#Union above two image & Save
			fuse = cv2.vconcat([gray,dst])
			cv2.imwrite(path_output_dir+"/"+str(count)+".png",fuse)
			print(count)
			count += 1
		else:
			break
	cv2.destroyAllWindows()
	vidcap.release()

video_to_frames('penguine.mp4', 'out')
