import pyrealsense2 as rs
import cv2
import os
import numpy as np

# Create 'image' directory if it doesn't exist
if not os.path.exists('image'):
    os.makedirs('image')

# Initialize RealSense pipeline
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

# Start streaming
pipeline.start(config)
print("Press 'c' to capture images for calibration. Press 'ESC' to quit.")

img_counter = 0

try:
    while True:
        # Wait for frames
        frames = pipeline.wait_for_frames()
        color_frame = frames.get_color_frame()
        if not color_frame:
            continue

        # Convert RealSense frame to OpenCV format
        frame = np.asanyarray(color_frame.get_data())

        # Display the frame
        cv2.imshow("Calibration Capture", frame)

        k = cv2.waitKey(1)
        if k % 256 == 27:
            # ESC pressed
            print("Escape hit, closing...")
            break
        elif k % 256 == 99:
            # 'c' pressed
            img_name = f"image/calib_img_{img_counter}.png"
            cv2.imwrite(img_name, frame)
            print(f"{img_name} written!")
            img_counter += 1
finally:
    # Stop streaming
    pipeline.stop()
    cv2.destroyAllWindows()
