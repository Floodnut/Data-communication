import numpy as np
import cv2

def onChange(value):
    pass


img = np.zeros((300, 1200), np.uint8)
img1 = cv2.imread("mine3.jpg", cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread("read_gray.jpg", cv2.IMREAD_GRAYSCALE)

if (img1 is None) or (img2 is None):
    raise Exception("No Image File")

title = "04_trackbar"
img[:, 0:400] = img1
img[:, 800:1200] = img2

cv2.imshow(title, img)
cv2.createTrackbar("image1", title, 0, 100, onChange)
cv2.createTrackbar("image2", title, 0, 100, onChange)
cv2.setTrackbarPos("image1", title, 100)
cv2.setTrackbarPos("image2", title, 100)

while 1:
    i1 = cv2.getTrackbarPos("image1", title) / 100
    i2 = cv2.getTrackbarPos("image2", title) / 100

    img[:, 400:800] = cv2.addWeighted(img1, i1, img2, i2, 0)
    if cv2.waitKey(30) >= 0:
        break

    cv2.imshow(title, img)

cv2.destroyAllWindows()
