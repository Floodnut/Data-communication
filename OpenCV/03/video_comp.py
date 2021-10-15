import cv2

gray_video = cv2.imread("./opencv.png",cv2.IMREAD_GRAYSCALE)

if gray_video is None:
    raise Exception("[Error]: No File")

title = "03_video_comp"
cv2.imshow(title, gray_video)

cv2.imwrite("./test.png",gray_video,(cv2.IMWRITE_PNG_COMPRESSION,0))
cv2.imwrite("./test.jpg",gray_video,[cv2.IMWRITE_JPEG_QUALITY,100])

cv2.waitKey(0)
cv2.destroyAllWindows()
