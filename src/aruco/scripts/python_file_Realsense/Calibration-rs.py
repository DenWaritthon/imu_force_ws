import cv2
# import numpy as np  # Removed as it is not used
import glob
import json

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

# Create the Charuco board
aruco_dict = cv2.aruco.getPredefinedDictionary(ARUCO_DICT)
charuco_board = cv2.aruco.CharucoBoard(
   (SQUARES_VERTICALLY, SQUARES_HORIZONTALLY), SQUARE_LENGTH, MARKER_LENGTH, aruco_dict
)

# Arrays to store object points and image points
all_corners = []
all_ids = []

# Load calibration images
images = glob.glob('calibration_images/*.png')  # Adjust your path

for fname in images:
    img = cv2.imread(fname)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detect ArUco markers
    corners, ids, _ = cv2.aruco.detectMarkers(gray, aruco_dict)

    if ids is not None:
        # Refine corner detection with Charuco board
        _, charuco_corners, charuco_ids = cv2.aruco.interpolateCornersCharuco(corners, ids, gray, charuco_board)

        if charuco_corners is not None and charuco_ids is not None:
            all_corners.append(charuco_corners)
            all_ids.append(charuco_ids)

        # Draw markers for visualization
        img = cv2.aruco.drawDetectedMarkers(img, corners, ids)
        cv2.imshow('Charuco Detection', img)
        cv2.waitKey(500)

cv2.destroyAllWindows()

# Camera calibration
ret, mtx, dist, rvecs, tvecs = cv2.aruco.calibrateCameraCharuco(
    charucoCorners=all_corners,
    charucoIds=all_ids,
    board=charuco_board,
    imageSize=gray.shape[::-1],
    cameraMatrix=None,
    distCoeffs=None
)

# Print the calibration results
print("Camera Matrix:")
print(mtx)
print("\nDistortion Coefficients:")
print(dist)

# Save the results to a JSON file
calibration_data = {
    "mtx": mtx.tolist(),
    "dist": dist.tolist()
}

with open('calibration.json', 'w') as f:
    json.dump(calibration_data, f)

print("\nCalibration data saved to 'calibration.json'")
