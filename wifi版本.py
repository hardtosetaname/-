import socket
import struct
import cv2 as cv

ip = "192.168.2.175"
port = 2666
xml = "E:/install_opencv/opencv-4.2.0/data/haarcascades/haarcascade_frontalface_alt_tree.xml"
com_transfer = "start /b C:/users/RYAN/Project5.exe "

def main():
    tcp_server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_server_socket.bind((ip, port))
    tcp_server_socket.listen(1)
    print("等待连接\r\n")
    new_client_socket, client_addr = tcp_server_socket.accept()
    print(f'当前链接：{client_addr}')
    capture = cv.VideoCapture(0)
    a = int(90)
    b = int(90)
    while(True):
        ret, frame = capture.read()
        frame = cv.flip(frame, 1)
        gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        face_detector = cv.CascadeClassifier(xml)
        faces = face_detector.detectMultiScale(gray, 1.1, 2)
        for x, y, w, h in faces:
            cv.circle(frame, (int(x + w / 2), int(y + h / 2)), h, (255, 255, 255), -1)
            a = int(a - (320 - (x + w / 2)) / 50)
            b = int(b + (240 - (y + h / 2)) / 50)
            if a > 180:
                a = 180
            elif a < 0:
                a = 0
            if b > 180:
                b = 180
            elif b < 0:
                b = 0
        # ff1 = int.to_bytes(a, length=1, byteorder='big', signed=False)
        # ff2 = int.to_bytes(b, length=1, byteorder='big', signed=False)
        ss = struct.pack("BB", a, b)
        new_client_socket.send(ss)
        cv.imshow("video", frame)
        c = cv.waitKey(50)
        if c == 27:
            break
    new_client_socket.close()
    tcp_server_socket.close()



if __name__ == "__main__":
    main()
