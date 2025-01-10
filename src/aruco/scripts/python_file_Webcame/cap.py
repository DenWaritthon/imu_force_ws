import cv2
import os

# Create 'image' directory if it doesn't exist
if not os.path.exists('image'):
    os.makedirs('image')

# Initialize the camera
cap = cv2.VideoCapture(2)

if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

img_counter = 0

while True:
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break

    cv2.imshow("Calibration Capture", frame)

    k = cv2.waitKey(1)
    if k % 256 == 27:
        # ESC pressed
        print("Escape hit, closing...")
        break
    elif k % 256 == 99:
        # 'c' pressed
        img_name = f"calibration_images/calib_img_{img_counter}.png"
        cv2.imwrite(img_name, frame)
        print(f"{img_name} written!")
        img_counter += 1

cap.release()
cv2.destroyAllWindows()