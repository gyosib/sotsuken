import cv2
import os

def video_to_frames(video, path_output_dir):
	# extract frames from a video and save to directory as 'x.png' where 
	# x is the frame index
	vidcap = cv2.VideoCapture(video)
	count = 0
	while vidcap.isOpened():
		success, image = vidcap.read()
		if success:
			height, width = image.shape[:2]
			tri = image[int(height/4)+18:height,0:width]
			cv2.imwrite(path_output_dir+"/tri/"+str(count)+".png",tri)
			gray = cv2.cvtColor(tri,cv2.COLOR_BGR2GRAY)
			ret, dst = cv2.threshold(gray,33,255,cv2.THRESH_BINARY)
			#dst = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,15,3)
			cv2.imwrite(path_output_dir+"/two/"+str(count)+".png",dst)
			#edge = cv2.Canny(dst,22,45)
			#edge = cv2.Canny(dst,150,100)
			#cv2.imwrite(path_output_dir+"/edge/"+str(count)+".png",edge)
			#fuse = cv2.vconcat([gray,dst,edge])
			fuse = cv2.vconcat([gray,dst])
			cv2.imwrite(path_output_dir+"/"+str(count)+".png",fuse)
			print(count)
			count += 1
		else:
			break
	cv2.destroyAllWindows()
	vidcap.release()

video_to_frames('penguine.mp4', 'out')
