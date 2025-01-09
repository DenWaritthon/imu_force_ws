import cv2
import numpy as np
from PIL import Image

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

IMG_SIZE = tuple(int(i * SQUARE_LENGTH + 2 * MARGIN_PX) for i in (SQUARES_VERTICALLY, SQUARES_HORIZONTALLY))
OUTPUT_NAME_PNG = 'ChArUco_Marker_A4.png'
OUTPUT_NAME_PDF = 'ChArUco_Marker_A4.pdf'

def create_and_save_new_board():
    dictionary = cv2.aruco.getPredefinedDictionary(ARUCO_DICT)
    board = cv2.aruco.CharucoBoard((SQUARES_VERTICALLY, SQUARES_HORIZONTALLY), SQUARE_LENGTH, MARKER_LENGTH, dictionary)
    img = board.generateImage(IMG_SIZE, marginSize=MARGIN_PX)
    cv2.imwrite(OUTPUT_NAME_PNG, img)

    # Convert PNG to PDF
    image = Image.open(OUTPUT_NAME_PNG)
    pdf_path = OUTPUT_NAME_PDF
    image.save(pdf_path, "PDF", resolution=DPI)

create_and_save_new_board()