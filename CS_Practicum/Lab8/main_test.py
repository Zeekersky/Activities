import cv2
import os
import tkinter as tk
from tkinter import messagebox
from tkinter import filedialog
from PIL import Image, ImageTk
import requests


captureCount = 2
folder_path = 'FacesORnot\\'
while os.path.isfile(os.path.join(folder_path, f"image{captureCount}.jpg")):
    captureCount += 1

video_source = 0
vid = cv2.VideoCapture(video_source)


def detectFace(img):
    face_cascade = cv2.CascadeClassifier(
        cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(
        gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    if len(faces) > 0:
        x, y, w, h = faces[0]

        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        TopCorner = (x, y)
        print(x,y,h,w)
        cv2.imshow('Detected Faces', img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

        return TopCorner, w, h, True
    else:
        messagebox.showerror("Error","No face detected in the given image.")
        return None, None, None, False

def uploadFace(faceTopCorner, w, h, face_exist, folder_path, img_name):
    if face_exist:
        url = 'http://192.168.20.234/upload_images.php'
        data = {
            "x": faceTopCorner[0],
            "y": faceTopCorner[1],
            "h": h,
            "w": w
        }
        files = {'myFile': (img_name, open(folder_path + img_name, 'rb'))}

        r = requests.post(url, data=data, files=files)
        if r.status_code == 200:
            messagebox.showinfo("Success", "Image uploaded successfully!")
        else:
            messagebox.showerror("Error","Failed to upload image.")

def capture():
    global captureCount
    ret, frame = vid.read()
    if ret:
        folder_path = 'FacesORnot\\'
        img_name = f"image{captureCount}.jpg"
        captureCount += 1
        cv2.imwrite(folder_path + img_name, frame)
        faceTopCorner, width, height, face_exist = detectFace(frame)
        uploadFace(faceTopCorner, width, height, face_exist, folder_path, img_name)

    else:
        messagebox.showerror("Error", "Failed to capture selfie!")


def FileUpload():
    file_path = filedialog.askopenfilename()
    if file_path:
        img_name = os.path.basename(file_path)
        img = cv2.imread(file_path)

        faceTopCorner, width, height, face_exist = detectFace(img)
        uploadFace(faceTopCorner, width, height, face_exist, folder_path, img_name)

def update():
    ret, frame = vid.read()
    if ret:
        photo = ImageTk.PhotoImage(image=Image.fromarray(
            cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)))
        canvas.create_image(0, 0, image=photo, anchor=tk.NW)
        canvas.photo = photo
    window.after(10, update)


window = tk.Tk()
window.title("Upload Image")

canvas = tk.Canvas(window, width=vid.get(3), height=vid.get(4))
canvas.pack()

btn_capture = tk.Button(window, text="Capture Image",
                        width=20, command=capture)
btn_capture.pack(padx=10, pady=10)

btn_capture = tk.Button(window, text="Browse Image",
                        width=20, command=FileUpload)
btn_capture.pack(padx=10, pady=10)

btn_exit = tk.Button(window, text="Exit", width=20, command=window.quit)
btn_exit.pack(padx=10, pady=10)

update()
window.mainloop()

vid.release()
