import numpy as np
import cv2
from pykeyboard import *
import time


img = cv2.imread('game18.png')
# gray = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)
# role = cv2.imread('role_front.png',0)

# res = cv2.matchTemplate(gray,role,cv2.TM_CCORR_NORMED)
# min_val , max_val ,min_loc , max_loc = cv2.minMaxLoc(res)
# cv2.imshow('re',res)
# print('min_v:{} ,max_v:{} , min_loc:{}, max_loc{}'.format(min_val, max_val ,min_loc , max_loc ))

# canny = gray.copy()
# canny = cv2.GaussianBlur(gray,(5,5),0)          #地圖用高斯再中間值模糊
# midblur = cv2.medianBlur(canny,33)
# canny = cv2.blur(canny,(25,25))


hsv = cv2.cvtColor(img,cv2.COLOR_RGB2HSV)
map = cv2.imread('map_color.jpg')

map = cv2.cvtColor(map,cv2.COLOR_RGB2HSV)
# cv2.imwrite('hsv.png',hsv)
map_h = map[5,5,0]
print (map[5][5])

i,j = 0,0
for i in range(600):
    for j in range(800):
        hsv_h = hsv[i,j,0]
        if hsv_h == 101:
            hsv[i,j,2] = 180
        else:
            hsv[i, j,2] = 0

cv2.imshow('hsv_processed',hsv)
# cv2.imwrite('hsv_processed.png',hsv)
rgb = cv2.cvtColor(hsv,cv2.COLOR_HSV2RGB)
cv2.imshow('rgb',rgb)
# cv2.imwrite('rgb.png',rgb)
gray = cv2.cvtColor(rgb,cv2.COLOR_RGB2GRAY)
# cv2.imshow('gray',gray)
# cv2.imwrite('gray.png',gray)
gray = cv2.medianBlur(gray,11)
# cv2.imshow('blur',gray)
# cv2.imwrite('blur.png',gray)
res,gray = cv2.threshold(gray,100,255,0)

kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(70,50))
closing = cv2.morphologyEx(gray,cv2.MORPH_CLOSE,kernel)
# dilate = cv2.dilate(gray,kernel)
# erode = cv2.erode(dilate,kernel)

cv2.imshow("thresh",gray)
# cv2.imwrite('threshold.png',gray)

cv2.imshow("closing",closing)
# cv2.imwrite('closing.png',closing)


kernel = cv2.getStructuringElement(cv2.MORPH_RECT,(30,30))
dilate = cv2.dilate(closing,kernel)
cv2.imshow("dilate",dilate)


k = PyKeyboard()
# while True:
#     k.tap_key(k.down_key)
#     time.sleep(0.1)
    # k.press_key(k.left_key)
    # k.release_key(k.down_key)

cv2.waitKey()
cv2.destroyAllWindows()






'''
 img = cv2.GaussianBlur(img, (7, 7), 0)  # 地圖用高斯再中間值模糊
 # img = cv2.blur(img,(5,5))            
 img = cv2.medianBlur(img,21)
 # img = cv2.Laplacian(img, cv2.CV_64FC3)


 x = cv2.Sobel(img, cv2.CV_16S, 1, 0)
 y = cv2.Sobel(img, cv2.CV_16S, 0, 1)

 absX = cv2.convertScaleAbs(x)    # 转回uint8
 absY = cv2.convertScaleAbs(y)

 img = cv2.addWeighted(absX, 0.5, absY, 0.5, 0)
 
 '''
# img = cv2.Scharr(img, cv2.CV_16S, 1, 0,3)
# img = cv2.convertScaleAbs(img);           絕對值
# ret, img = cv2.threshold(img, 10, 255, 0)

