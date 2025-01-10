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

class ArucoDetectNode(Node):
    def __init__(self):
        super().__init__('aruco_detect_node')
        self.image_pub = self.create_publisher(Image, '/aruco_images', 10)
        self.object_pose_pub = self.create_publisher(Point, '/object_pose', 10)
        self.size_roi_pub = self.create_publisher(Int16MultiArray, '/size_roi', 10)
        self.bridge = CvBridge()

        self.cap = cv2.VideoCapture(2)
        if not self.cap.isOpened():
            self.get_logger().error("Error: Could not open webcam.")
            rclpy.shutdown()
            return

        self.timer = self.create_timer(0.1, self.timer_callback)

        json_file_path = 'src/aruco/config/calibration_webcam.json'
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
        pygame.display.set_caption("Webcam Feed")

        #logger
        self.get_logger().info(f'Node Aruco Detect Start!!!')

    def timer_callback(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                rclpy.shutdown()
                return

        ret, frame = self.cap.read()
        if not ret:
            self.get_logger().error("Error: Could not read frame.")
            return

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
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

                cv2.line(frame, topLeft, topRight, (0, 255, 0), 2)
                cv2.line(frame, topRight, bottomRight, (0, 255, 0), 2)
                cv2.line(frame, bottomRight, bottomLeft, (0, 255, 0), 2)
                cv2.line(frame, bottomLeft, topLeft, (0, 255, 0), 2)

                cv2.putText(frame, 'TL', topLeft, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
                cv2.putText(frame, 'TR', topRight, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
                cv2.putText(frame, 'LL', bottomLeft, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)
                cv2.putText(frame, 'LR', bottomRight, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 2)

                cX = int((topLeft[0] + bottomRight[0]) / 2.0)
                cY = int((topLeft[1] + bottomRight[1]) / 2.0)
                cv2.circle(frame, (cX, cY), 4, (0, 0, 255), -1)

                marker_width_px = np.linalg.norm(np.array(topRight) - np.array(topLeft))
                marker_height_px = np.linalg.norm(np.array(topLeft) - np.array(bottomLeft))
                marker_width_cm = marker_width_px / (300 / 25.4) / 10
                marker_height_cm = marker_height_px / (300 / 25.4) / 10

                roi = frame[topLeft[1]:bottomRight[1], topLeft[0]:bottomRight[0]]

                roi_width_px = bottomRight[0] - topLeft[0]
                roi_height_px = bottomRight[1] - topLeft[1]
                roi_width_cm = roi_width_px / (300 / 25.4) / 10
                roi_height_cm = roi_height_px / (300 / 25.4) / 10
                cv2.putText(frame, f'ROI Size: {roi_width_px}px x {roi_height_px}px', (topLeft[0], topLeft[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)

                hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
                lower_black = np.array([0, 0, 0])
                upper_black = np.array([180, 255, 30])
                mask = cv2.inRange(hsv, lower_black, upper_black)
                contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

                if contours:
                    largest_contour = max(contours, key=cv2.contourArea)
                    x, y, w, h = cv2.boundingRect(largest_contour)
                    cv2.rectangle(roi, (x, y), (x + w, y + h), (255, 0, 0), 2)

                    object_width_cm = w / (300 / 25.4) / 10
                    object_height_cm = h / (300 / 25.4) / 10

                    object_center_x = x + w // 2
                    object_center_y = y + h // 2
                    cv2.circle(roi, (object_center_x, object_center_y), 4, (255, 0, 0), -1)
                    cv2.line(roi, (object_center_x, 0), (object_center_x, roi.shape[0]), (0, 255, 0), 2)
                    cv2.line(roi, (0, object_center_y), (roi.shape[1], object_center_y), (0, 0, 255), 2)
                    # cv2.putText(roi, '0,0', (0, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                    cv2.putText(roi, f'Pos: (x: {object_center_x - roi_width_px // 2}, y: {object_center_y - roi_height_px // 2})', (x, y + h + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)


                    gain_axis_x = self.real_axis_x / roi_width_px 
                    gain_axis_y = self.real_axis_y / roi_height_px 

                    object_pose = Point()
                    object_pose.x = float(f"{((object_center_x - roi_width_px // 2) * gain_axis_x * -1):.2f}")
                    object_pose.y = float(f"{((object_center_y - roi_height_px // 2) * gain_axis_y):.2f}")
                    object_pose.z = 0.0
                    self.object_pose_pub.publish(object_pose)

                    size_roi = Int16MultiArray()
                    size_roi.data = [int(roi_width_px), int(roi_height_px)]
                    self.size_roi_pub.publish(size_roi)

        frame = cv2.flip(frame, 1)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame_rgb = np.rot90(frame_rgb)
        frame_rgb = pygame.surfarray.make_surface(frame_rgb)

        if 'roi' in locals():
            roi = cv2.flip(roi, 1)
            roi_rgb = cv2.cvtColor(roi.astype(np.uint8), cv2.COLOR_BGR2RGB)
            roi_rgb = cv2.resize(roi_rgb, (640, 480))
            roi_rgb = np.rot90(roi_rgb)
            roi_rgb = pygame.surfarray.make_surface(roi_rgb)
            self.screen.blit(roi_rgb, (640, 0))

        self.screen.blit(frame_rgb, (0, 0))
        pygame.display.update()

        image_msg = self.bridge.cv2_to_imgmsg(frame, encoding="bgr8")
        self.image_pub.publish(image_msg)

def main(args=None):
    rclpy.init(args=args)
    node = ArucoDetectNode()
    rclpy.spin(node)
    node.cap.release()
    pygame.quit()
    cv2.destroyAllWindows()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
