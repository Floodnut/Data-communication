import numpy as np
import cv2

def printAsc(rect):
    for i, (x,y,w,h,a) in enumerate(rect):
        print("Rect[%i]의 크기는 [%a] 입니다." %(i, a))

bounds = np.zeros((5, 5), np.uint16)

start = cv2.randn( bounds[:, :2], 100, 50)
end = cv2.randn( bounds[:, 2:-1], 300, 50)

sizes = cv2.absdiff(start, end)
areas = sizes[:, 0] * sizes[:, 1]

rectObj = bounds.copy()
rectObj[:, 2:-1] = sizes
rectObj[:, -1] = areas

order = cv2.sortIdx(areas, cv2.SORT_EVERY_COLUMN).flatten() #SORT_EVERY_COLUMN로 인해 오름차순으로 출력됩니다.
#order = np.flip(order)

printAsc(rectObj[order.astype('int')])


