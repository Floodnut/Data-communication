import numpy as np
import cv2

W = 400
H = 300
base = np.full((H, W, 3), (255, 0, 0), np.uint8)
title = "04_PC_Camera"
cam = cv2.VideoCapture(0)
if not cam.isOpened():
    raise Exception("No Cam")

while 1:
    ret, frame = cam.read()
    if not ret: break

    frame = cv2.resize(frame, dsize=(W, H), interpolation=cv2.INTER_AREA)

    base[30:270, 30:350] = frame[30:270, 30:350]
    cv2.rectangle(base, (30, 30), (350, 270), (0, 0, 255), 2)

    cv2.imshow(title, base)

    if cv2.waitKey(30) >=0: break

cam.release()
cv2.destroyAllWindows()