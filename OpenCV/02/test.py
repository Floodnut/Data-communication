import cv2
import numpy as np

img = np.zeros((300,400),np.uint8) #400*300 화소에 0을 채움
img.fill(200) # 0으로 채워진 img에 0~255의 값 중 200으로 채움

#위에서 작성한 img를 창으로 띄움
cv2.imshow("title", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
