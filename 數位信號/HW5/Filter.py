import numpy as np
import cv2
#參考資料:https://www.pyimagesearch.com/2016/07/25/convolutions-with-opencv-and-python/

# 讀取圖檔
img = cv2.imread('cat.jpg')

# 顯示圖片
cv2.imshow('cat', img)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

cv2.imshow('gray', gray)

filter = np.array((
    [0, 0, 0],
    [-1, 2, -1],
    [0, 0, 0]), dtype="int")


filterA = np.array((
    [0, -1, 0],
    [0, 2, 0],
    [0, -1, 0]), dtype="int")

filterB = np.array((
    [-1, -1, -1],
    [-1, 8, -1],
    [-1, -1, -1]), dtype="int")

filterC = np.array((
    [1, -2, 1],
    [-2, 4, -2],
    [1, -2, 1]), dtype="int")

kernelBank = (
	("filter", filter),
	("filterA", filterA),
	("filterB", filterB),
	("filterC", filterC),
)

for (kernelName, kernel) in kernelBank:
    # apply the kernel to the grayscale image using both
    # our custom `convole` function and OpenCV's `filter2D`
    # function
    opencvOutput = cv2.filter2D(gray, -1, kernel)
    # show the output images
    cv2.imshow("{}".format(kernelName), opencvOutput)

# 按下任意鍵則關閉所有視窗
cv2.waitKey(0)
cv2.destroyAllWindows()

