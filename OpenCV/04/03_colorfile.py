import cv2

def splitColor(color, splitChannel):
    blue = splitChannel[0]
    green = splitChannel[1]
    red = splitChannel[2]

    if color == "Blue":
        green[:,:] = 0
        red[:,:] = 0

    elif color == "Green":
        red[:, :] = 0
        blue[:, :] = 0

    elif color == "Red":
        blue[:, :] = 0
        green[:, :] = 0

    else:
        raise Exception("Invalid Color")

    mrg = cv2.merge([blue, green, red])
    cv2.imshow(color, mrg)

title = ["Blue", "Green", "Red"]
img = cv2.imread("logo.jpg",cv2.IMREAD_COLOR)

splitBGR1 = cv2.split(img)
splitBGR2 = cv2.split(img)
splitBGR3 = cv2.split(img)

result = splitColor(title[0], splitBGR1)    #show Blue
result = splitColor(title[1], splitBGR2)    #show Green
result = splitColor(title[2], splitBGR3)    #show Blue

cv2.waitKey(0)