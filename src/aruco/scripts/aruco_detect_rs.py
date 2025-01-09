#!/usr/bin/python3

import cv2
import numpy as np
import json
import pygame
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import Point
from std_msgs.msg import Int16MultiArray
from cv_bridge import CvBridge
import pyrealsense2 as rs

class ArucoDetectNode(Node):
    def __init__(self):
        super().__init__('aruco_detect_node')
        self.image_pub = self.create_publisher(Image, '/aruco_images', 10)
        self.object_pose_pub = self.create_publisher(Point, '/object_pose', 10)
        self.size_roi_pub = self.create_publisher(Int16MultiArray, '/size_roi', 10)
        self.bridge = CvBridge()

        # RealSense pipeline setup
        self.pipeline = rs.pipeline()
        config = rs.config()
        config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
        config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
        
        self.pipeline.start(config)

        # Load calibration data
        json_file_path = 'src/aruco/config/calibration_real-sense.json'
        with open(json_file_path, 'r') as file:
            json_data = json.load(file)
        self.mtx = np.array(json_data['mtx'])
        self.dist = np.array(json_data['dist'])

        self.dictionary = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_6X6_250)
        self.board = cv2.aruco.CharucoBoard((7, 5), 40, 20, self.dictionary)
        self.params = cv2.aruco.DetectorParameters()
        self.detector = cv2.aruco.ArucoDetector(self.dictionary, self.params)

        self.real_axis_x = 28.1
        self.real_axis_y = 18.4

        pygame.init()
        self.screen = pygame.display.set_mode((1280, 480))
        pygame.display.set_caption("RealSense Feed")

        self.get_logger().info('Node Aruco Detect Start!!!')

        self.timer = self.create_timer(0.1, self.timer_callback)

    def timer_callback(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.stop_pipeline()
                rclpy.shutdown()
                return

        frames = self.pipeline.wait_for_frames()
        color_frame = frames.get_color_frame()
        depth_frame = frames.get_depth_frame()

        if not color_frame or not depth_frame:
            self.get_logger().error("Error: Could not retrieve frames.")
            return

        color_image = np.asanyarray(color_frame.get_data())
        gray = cv2.cvtColor(color_image, cv2.COLOR_BGR2GRAY)
        h, w = gray.shape[:2]
        newcameramtx, roi = cv2.getOptimalNewCameraMatrix(self.mtx, self.dist, (w, h), 1, (w, h))
        gray = cv2.undistort(gray, self.mtx, self.dist, None, newcameramtx)

        marker_corners, marker_ids, _ = self.detector.detectMarkers(gray)

        if marker_ids is not None and len(marker_ids) > 0:
            ids = marker_ids.flatten()
            if all(x in ids for x in [0, 1, 2, 3]):
                corners_dict = {id: marker_corners[np.where(ids == id)[0][0]].reshape((4, 2)) for id in [0, 1, 2, 3]}
                topLeft = tuple(map(int, corners_dict[0][0]))
                topRight = tuple(map(int, corners_dict[1][1]))
                bottomLeft = tuple(map(int, corners_dict[2][3]))
                bottomRight = tuple(map(int, corners_dict[3][2]))

                # Flip coordinates for ROI if the image is flipped horizontally
                topLeft = (w - topLeft[0], topLeft[1])
                topRight = (w - topRight[0], topRight[1])
                bottomLeft = (w - bottomLeft[0], bottomLeft[1])
                bottomRight = (w - bottomRight[0], bottomRight[1])

                # Draw ROI area
                cv2.line(color_image, topLeft, topRight, (0, 255, 0), 2)
                cv2.line(color_image, topRight, bottomRight, (0, 255, 0), 2)
                cv2.line(color_image, bottomRight, bottomLeft, (0, 255, 0), 2)
                cv2.line(color_image, bottomLeft, topLeft, (0, 255, 0), 2)

                # Calculate and draw the center point of the ROI
                cX = int((topLeft[0] + bottomRight[0]) / 2.0)
                cY = int((topLeft[1] + bottomRight[1]) / 2.0)
                cv2.circle(color_image, (cX, cY), 4, (0, 0, 255), -1)

                # Calculate ROI dimensions
                roi_width_px = abs(bottomRight[0] - topLeft[0])
                roi_height_px = abs(bottomRight[1] - topLeft[1])

                cv2.putText(color_image, f'ROI Size: {roi_width_px}px x {roi_height_px}px',
                            (topLeft[0], topLeft[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)

        # Flip the final image for display
        flipped_color_image = cv2.flip(color_image, 1)

        frame_rgb = cv2.cvtColor(flipped_color_image, cv2.COLOR_BGR2RGB)
        frame_rgb = np.rot90(frame_rgb)
        frame_surface = pygame.surfarray.make_surface(frame_rgb)
        self.screen.blit(frame_surface, (0, 0))
        pygame.display.update()

        image_msg = self.bridge.cv2_to_imgmsg(flipped_color_image, encoding="bgr8")
        self.image_pub.publish(image_msg)


    def stop_pipeline(self):
        self.pipeline.stop()
        pygame.quit()
        cv2.destroyAllWindows()


def main(args=None):
    rclpy.init(args=args)
    node = ArucoDetectNode()
    rclpy.spin(node)
    node.stop_pipeline()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
