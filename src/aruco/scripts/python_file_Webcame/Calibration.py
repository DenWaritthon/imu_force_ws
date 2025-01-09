import cv2
import numpy as np
import os
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

def get_calibration_parameters(img_dir):
    # Define the aruco dictionary, charuco board and detector
    aruco_dict = cv2.aruco.getPredefinedDictionary(ARUCO_DICT)
    board = cv2.aruco.CharucoBoard((SQUARES_VERTICALLY, SQUARES_HORIZONTALLY), SQUARE_LENGTH, MARKER_LENGTH, aruco_dict)
    detector = cv2.aruco.ArucoDetector(aruco_dict)

    all_charuco_corners = []
    all_charuco_ids = []
    imgSize = None

    # Iterate through the images in the directory
    for filename in os.listdir(img_dir):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            image = cv2.imread(os.path.join(img_dir, filename))
            if imgSize is None:
                imgSize = image.shape[:2][::-1]  # Get the image size

            marker_corners, marker_ids, rejectedCandidates = detector.detectMarkers(image)
        
            if len(marker_ids) > 0:  # If at least one marker is detected
                # cv2.aruco.drawDetectedMarkers(image_copy, marker_corners, marker_ids)
                ret, charucoCorners, charucoIds = cv2.aruco.interpolateCornersCharuco(marker_corners, marker_ids, image, board)

                if charucoIds is not None and len(charucoCorners) > 3:
                    all_charuco_corners.append(charucoCorners)
                    all_charuco_ids.append(charucoIds)
    
    # Calibrate camera with extracted information
    result, mtx, dist, rvecs, tvecs = cv2.aruco.calibrateCameraCharuco(all_charuco_corners, all_charuco_ids, board, imgSize, None, None)
    return mtx, dist

SENSOR = 'logitech_c920'
OUTPUT_JSON = 'calibration.json'

mtx, dist = get_calibration_parameters(img_dir='image')
data = {"sensor": SENSOR, "mtx": mtx.tolist(), "dist": dist.tolist()}

with open(OUTPUT_JSON, 'w') as json_file:
    json.dump(data, json_file, indent=4)