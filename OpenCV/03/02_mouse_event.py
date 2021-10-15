import numpy as np
import cv2

def onMouse(event, x, y, flags, param):

    if event == cv2.EVENT_LBUTTONDOWN:
        cv2.rectangle(image, (x-15,y-15),(x+15,y+15),(0,100,100),2)
        cv2.imshow('mouse_event',image)
    elif event == cv2.EVENT_RBUTTONDOWN:
        cv2.circle(image, (x, y), 20,(150,0,50),2)
        cv2.imshow('mouse_event', image)

image = np.zeros((500,700),np.uint8)
image.fill(255)

title2 ="mouse_event"

cv2.namedWindow(title2, cv2.WINDOW_NORMAL)
cv2.imshow(title2, image)
cv2.resizeWindow(title2, 700, 500)

cv2.setMouseCallback(title2, onMouse,image)

cv2.waitKey(0)
cv2.destroyAllWindows()
