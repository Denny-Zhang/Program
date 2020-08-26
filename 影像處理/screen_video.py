import cv2
import numpy as np
import time
from PIL import ImageGrab

def screen_record():
    last_time = time.time()
    while(True):

        printscreen = np.array(ImageGrab.grab(bbox=(50, 130, 851, 730)))
        print('loop took {} seconds'.format(time.time()-last_time))
        last_time = time.time()


        img = cv2.cvtColor(printscreen,cv2.COLOR_BGR2RGB)
        img = cv2.cvtColor(img, cv2.COLOR_RGB2HSV)

        gray = cv2.inRange(img, np.array([101, 136, 120]), np.array([101, 136, 120]))

        cv2.imshow('window',gray)
        if cv2.waitKey(5) & 0xFF == ord('q'):   #waitKey = 鍵值，AND 8位元(只取8bits)，避免BUG
            cv2.destroyAllWindows()
            break
screen_record()








