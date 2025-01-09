import pyrealsense2 as rs
import cv2
import numpy as np

# Configure RealSense pipeline
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
pipeline.start(config)

# Load ArUco dictionary
dictionary = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
detector = cv2.aruco.ArucoDetector(dictionary)

try:
    while True:
        # Get frames from the RealSense camera
        frames = pipeline.wait_for_frames()
        color_frame = frames.get_color_frame()
        depth_frame = frames.get_depth_frame()

        if not color_frame or not depth_frame:
            continue

        # Convert frames to numpy arrays
        color_image = np.asanyarray(color_frame.get_data())
        depth_image = np.asanyarray(depth_frame.get_data())

        # Detect ArUco markers
        gray = cv2.cvtColor(color_image, cv2.COLOR_BGR2GRAY)
        corners, ids, _ = detector.detectMarkers(gray)

        if ids is not None:
            for corner, marker_id in zip(corners, ids):
                pts = corner[0].astype(int)
                topLeft, topRight, bottomRight, bottomLeft = pts
                cv2.polylines(color_image, [pts], isClosed=True, color=(0, 255, 0), thickness=2)

                # Get the center of the marker
                center_x = int((topLeft[0] + bottomRight[0]) / 2)
                center_y = int((topLeft[1] + bottomRight[1]) / 2)

                # Get depth at the center
                depth = depth_frame.get_distance(center_x, center_y)
                cv2.circle(color_image, (center_x, center_y), 5, (0, 0, 255), -1)
                cv2.putText(color_image, f"ID: {marker_id[0]}", (topLeft[0], topLeft[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
                cv2.putText(color_image, f"Distance: {depth:.2f} m", (center_x, center_y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

        # Display the color image
        cv2.imshow('RealSense ArUco Detection', color_image)

        # Break on 'q' key press
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    # Stop the pipeline
    pipeline.stop()
    cv2.destroyAllWindows()
