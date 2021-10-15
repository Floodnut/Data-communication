import cv2
import numpy as np

title2 ="k_flag"
w = 900
h = w * 2 / 3
r = h / 4

cv2.namedWindow(title2)
image = np.full((int(h),int(w),3),(255,255,255),np.uint8)

cv2.ellipse(image, (int(w/2) , int(h/2)), (int(r),int(r)), 0, 0, 180, (255,0,0), -1)                #big red
cv2.ellipse(image, (int(w/2) , int(h/2)), (int(r),int(r)), 0, 180, 360, (0,0,255), -1)              #big blue

cv2.ellipse(image, (int((w/2) - (r/2)) , int(h/2)), (int(r/2),int(r/2)), 0, 0, 180, (0,0,255), -1)  #small red
cv2.ellipse(image, (int((w/2) + (r/2)) , int(h/2)), (int(r/2),int(r/2)), 0, 180, 360, (255,0,0), -1)          #small blue


cv2.imshow(title2, image)

cv2.waitKey(0)
cv2.destroyAllWindows()
