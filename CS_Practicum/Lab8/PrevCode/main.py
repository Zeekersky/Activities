import cv2
import os
import tkinter as tk
from tkinter import messagebox
from PIL import Image, ImageTk
import requests

# capturing from webcam & save it

captureCount = 1
video_source = 0
vid = cv2.VideoCapture(video_source)


def capture():
    global captureCount
    ret, frame = vid.read()
    if ret:
        folder_path = 'FacesORnot\\'
        img_name = f"image{captureCount}.jpg"
        cv2.imwrite(folder_path+img_name, frame)
        captureCount += 1
    else:
        messagebox.showerror("Error", "Failed to capture selfie!")


def update():
    ret, frame = vid.read()
    if ret:
        photo = ImageTk.PhotoImage(image=Image.fromarray(
            cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)))
        canvas.create_image(0, 0, image=photo, anchor=tk.NW)
        canvas.photo = photo
    window.after(10, update)


window = tk.Tk()
window.title("Webcam Selfie Capture")

canvas = tk.Canvas(window, width=vid.get(3), height=vid.get(4))
canvas.pack()

btn_capture = tk.Button(window, text="Capture Image",
                        width=20, command=capture)
btn_capture.pack(padx=10, pady=10)

btn_exit = tk.Button(window, text="Exit", width=20, command=window.quit)
btn_exit.pack(padx=10, pady=10)

update()
window.mainloop()

vid.release()


# Database Collection and data upload

# Detection the face

def detect_face(img):
    face_cascade = cv2.CascadeClassifier(
        cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(
        gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    if len(faces) > 0:
        x, y, w, h = faces[0]

        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        center = (x + (w/2), y + (h/2))

        cv2.imshow('Detected Faces', img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

        return center, w, h, True
    else:
        print("No face detected in the given image.")
        return None, None, None, False


def upload_files():
    # Handling files upload from a folder
    folder_path = 'FacesORnot\\'

    for filename in os.listdir(folder_path):
        if filename.endswith('.jpg') or filename.endswith('.png'):
            file_path = os.path.join(folder_path, filename)

            # Detect face in the uploaded image
            img1 = cv2.imread(file_path)
            img = img1.resize((640,480))
            faceCenter, width, height, faceExist = detect_face(img)

            # Insert data into the database if face is detected
            if faceExist:
                url = 'http://172.16.40.16/upload_images.php'
                item = {
                    "x": faceCenter[0], "y": faceCenter[1], "h": height, "w": width}
                file = {'myFile': open(file_path, 'rb')}
                r = requests.post(url, data=item, files=file)
                if r.status_code != 200:
                    print('sendErr: '+r.url)
                else:
                    print(r.text)

    return 'Files uploaded and face data inserted into the database successfully'
