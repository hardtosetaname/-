import os
import cv2 as cv

xml = "E:/install_opencv/opencv-4.2.0/data/haarcascades/haarcascade_frontalface_alt_tree.xml"
com_transfer = "start /b C:/users/RYAN/Project5.exe "


def main():
    capture = cv.VideoCapture(0)
    a = int(90)
    b = int(90)
    while (True):
        ret, frame = capture.read()
        frame = cv.flip(frame, 1)
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        face_detector = cv.CascadeClassifier(xml)
        faces = face_detector.detectMultiScale(gray, 1.1, 2)
        for x, y, w, h in faces:
            cv.circle(frame, (int(x+w/2), int(y+h/2)), h, (255, 255, 255), -1)
            a = int(a - (320 - (x + w / 2)) / 50)
            b = int(b + (240 - (y + h / 2)) / 50)
            if a > 180:
                a = 180
            elif a < 0:
                a = 0
            if b > 135:
                b = 135
            elif b < 45:
                b = 45
            os.system(com_transfer+str(a*1000+b))
        cv.imshow("video", frame)
        c = cv.waitKey(50)
        if c == 27:
            break

if __name__ == "__main__":
    main()
