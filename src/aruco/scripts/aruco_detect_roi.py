import cv2
import numpy as np
import json
import pygame

ARUCO_DICT = cv2.aruco.DICT_6X6_250  # Dictionary ID
SQUARES_VERTICALLY = 7               # Number of squares vertically
SQUARES_HORIZONTALLY = 5             # Number of squares horizontally
SQUARE_LENGTH_MM = 40                # Square side length (in mm)
MARKER_LENGTH_MM = 20                # ArUco marker side length (in mm)
MARGIN_MM = 10                       # Margins size (in mm)

# Convert mm to pixels (assuming 300 DPI)
DPI = 300
MM_TO_PX = DPI / 25.4
SQUARE_LENGTH = int(SQUARE_LENGTH_MM * MM_TO_PX)
MARKER_LENGTH = int(MARKER_LENGTH_MM * MM_TO_PX)
MARGIN_PX = int(MARGIN_MM * MM_TO_PX)

json_file_path = 'src/aruco/config/calibration.json'

with open(json_file_path, 'r') as file:  # Read the JSON file
    json_data = json.load(file)

mtx = np.array(json_data['mtx'])
dist = np.array(json_data['dist'])

cap = cv2.VideoCapture(2)  # Open the webcam with ID 1

if not cap.isOpened():
    print("Error: Could not open webcam.")
    exit()

dictionary = cv2.aruco.getPredefinedDictionary(ARUCO_DICT)
board = cv2.aruco.CharucoBoard((SQUARES_VERTICALLY, SQUARES_HORIZONTALLY), SQUARE_LENGTH, MARKER_LENGTH, dictionary)
params = cv2.aruco.DetectorParameters()
detector = cv2.aruco.ArucoDetector(dictionary, params)

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((1280, 480))  # Adjusted to show both frames side by side
pygame.display.set_caption("Webcam Feed")

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    ret, frame = cap.read()
    if not ret:
        print("Error: Could not read frame.")
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    h, w = gray.shape[:2]
    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w, h), 1, (w, h))
    gray = cv2.undistort(gray, mtx, dist, None, newcameramtx)

    marker_corners, marker_ids, rejectedCandidates = detector.detectMarkers(gray)

    if marker_ids is not None and len(marker_ids) > 0:  # If at least one marker is detected
        ids = marker_ids.flatten()
        if all(x in ids for x in [0, 1, 2, 3]):  # Check if all required markers are detected
            corners_dict = {id: marker_corners[np.where(ids == id)[0][0]].reshape((4, 2)) for id in [0, 1, 2, 3]}
            topLeft = tuple(map(int, corners_dict[0][0]))
            topRight = tuple(map(int, corners_dict[1][1]))
            bottomLeft = tuple(map(int, corners_dict[2][3]))
            bottomRight = tuple(map(int, corners_dict[3][2]))

            # Draw the bounding box of the ArUco detection
            cv2.line(frame, topLeft, topRight, (0, 255, 0), 2)
            cv2.line(frame, topRight, bottomRight, (0, 255, 0), 2)
            cv2.line(frame, bottomRight, bottomLeft, (0, 255, 0), 2)
            cv2.line(frame, bottomLeft, topLeft, (0, 255, 0), 2)

            # Label the corners
            cv2.putText(frame, 'TL', topLeft, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
            cv2.putText(frame, 'TR', topRight, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
            cv2.putText(frame, 'LL', bottomLeft, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
            cv2.putText(frame, 'LR', bottomRight, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)

            # Compute and draw the center (x, y)-coordinates of the ArUco marker
            cX = int((topLeft[0] + bottomRight[0]) / 2.0)
            cY = int((topLeft[1] + bottomRight[1]) / 2.0)
            cv2.circle(frame, (cX, cY), 4, (0, 0, 255), -1)

            # Calculate and display the size of the ArUco marker in cm
            marker_width_px = np.linalg.norm(np.array(topRight) - np.array(topLeft))
            marker_height_px = np.linalg.norm(np.array(topLeft) - np.array(bottomLeft))
            marker_width_cm = marker_width_px / MM_TO_PX / 10
            marker_height_cm = marker_height_px / MM_TO_PX / 10
            cv2.putText(frame, f'Size: {marker_width_cm:.2f}x{marker_height_cm:.2f} cm', (topLeft[0], topLeft[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

            # Create ROI around the detected marker
            roi = frame[topLeft[1]:bottomRight[1], topLeft[0]:bottomRight[0]]

            # Display the size of the ROI on the main frame
            roi_width_px = bottomRight[0] - topLeft[0]
            roi_height_px = bottomRight[1] - topLeft[1]
            roi_width_cm = roi_width_px / MM_TO_PX / 10
            roi_height_cm = roi_height_px / MM_TO_PX / 10
            cv2.putText(frame, f'ROI Size: {roi_width_px}px x {roi_height_px}px', (topLeft[0], topLeft[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)
            cv2.putText(frame, f'ROI Size: {roi_width_cm:.2f}x{roi_height_cm:.2f} cm', (topLeft[0], topLeft[1] - 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)

            # Convert ROI to HSV color space
            hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)

            # Define the range for black color in HSV
            lower_black = np.array([0, 0, 0])
            upper_black = np.array([180, 255, 30])

            # Create a mask for black color
            mask = cv2.inRange(hsv, lower_black, upper_black)

            # Find contours in the mask
            contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

            if contours:
                # Find the largest contour
                largest_contour = max(contours, key=cv2.contourArea)
                x, y, w, h = cv2.boundingRect(largest_contour)

                # Draw the bounding box around the largest black object
                cv2.rectangle(roi, (x, y), (x + w, y + h), (255, 0, 0), 2)  # Blue bounding box

                # Calculate and display the size and position of the black object
                object_width_cm = w / MM_TO_PX / 10
                object_height_cm = h / MM_TO_PX / 10
                cv2.putText(roi, f'Size: {object_width_cm:.2f}x{object_height_cm:.2f} cm', (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)
                cv2.putText(roi, f'Pos: (x: {x}, y: {y})', (x, y + h + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)  # Red for x, Green for y

                # Calculate the center of the black object
                object_center_x = x + w // 2
                object_center_y = y + h // 2

                # Draw the center of the black object
                cv2.circle(roi, (object_center_x, object_center_y), 4, (255, 0, 0), -1)

                # Draw X and Y axis lines
                cv2.line(roi, (object_center_x, 0), (object_center_x, roi.shape[0]), (0, 255, 0), 2)  # Y axis (Green)
                cv2.line(roi, (0, object_center_y), (roi.shape[1], object_center_y), (0, 0, 255), 2)  # X axis (Red)

                # Draw the start point (0, 0)
                cv2.putText(roi, '0,0', (0, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)  # White text for start point

    # Flip the frame horizontally
    frame = cv2.flip(frame, 1)

    # Convert the frame to RGB format
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    frame_rgb = np.rot90(frame_rgb)
    frame_rgb = pygame.surfarray.make_surface(frame_rgb)

    # Convert the ROI to RGB format, flip it horizontally, and resize it to fit the pygame window
    if 'roi' in locals():
        roi = cv2.flip(roi, 1)  # Flip the ROI horizontally
        roi_rgb = cv2.cvtColor(roi.astype(np.uint8), cv2.COLOR_BGR2RGB)
        roi_rgb = cv2.resize(roi_rgb, (640, 480))
        roi_rgb = np.rot90(roi_rgb)
        roi_rgb = pygame.surfarray.make_surface(roi_rgb)
        screen.blit(roi_rgb, (640, 0))

    # Display the frame in pygame window
    screen.blit(frame_rgb, (0, 0))
    pygame.display.update()

cap.release()
pygame.quit()
cv2.destroyAllWindows()