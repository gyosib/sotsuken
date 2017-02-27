import cv2
import numpy as np

def getred(img1, img2):
	img = cv2.imread("test.png")
	height = img.shape[0]
	width = img.shape[1]

	cv2.rectangle(img,(0,0),(width,height),(0,0,255),-1)
	#cv2.imshow('image', img2)
	#cv2.waitKey(0)
	#cv2.destroyAllWindows()
	for h in range(0,height):
		for w in range(0,width):
			pixel1 = img1[h,w]
			pixel2 = img2[h,w]
			if(pixel1 == pixel2):
				img[h,w] = img1[h,w]
	return img

def export_movie():
# 入力する動画と出力パスを指定。
	target = "out/two/"
	result = "redglass.avi"

# 動画の読み込みと動画情報の取得
	#img = cv2.imread(target+"0.png",cv2.IMREAD_GRAYSCALE)
	img = cv2.imread(target+"0.png", 0)
	img0 = img
	fps    = 10
	if len(img.shape) == 3:
		height, width, channels = img.shape[:3]
	else:
		height, width = img.shape[:2]
		channels = 1

# 形式はMP4Vを指定
	fourcc = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D')

# 出力先のファイルを開く
	out = cv2.VideoWriter(result, int(fourcc), fps, (int(width), int(height)))

# 最初の1フレームを読み込む
	if not img is None:
		num = 1
	else:
		sys.exit(1)

# フレームの読み込みに成功している間フレームを書き出し続ける
	while (not img is None and num < 100):

# 読み込んだフレームを書き込み
		#out.write(cv2.cvtColor(getred(img0, img),cv2.COLOR_GRAY2RGB))
		out.write(getred(img0, img))

# 次のフレームを読み込み
		img = cv2.imread(target+str(num)+".png", 0)
		num = num + 1


if __name__ == '__main__':
	export_movie()
