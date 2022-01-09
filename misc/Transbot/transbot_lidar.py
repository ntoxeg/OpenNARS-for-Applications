import numpy as np
from common import *
from time import sleep
from sensor_msgs.msg import LaserScan

ResponseDist = 0.55
LaserAngle = 30  # 10~180
Right_warning = 0
Left_warning = 0
front_warning = 0

def registerScan(self, scan_data):
    global Left_warning, Right_warning, front_warning
    # 记录激光扫描并发布最近物体的位置（或指向某点）
    # Record the laser scan and publish the position of the nearest object (or point to a point)
    ranges = np.array(scan_data.ranges)
    # 按距离排序以检查从较近的点到较远的点是否是真实的东西
    # Sort by distance to check whether things are real from closer points to more distant points
    sortedIndices = np.argsort(ranges)
    Right_warning = 0
    Left_warning = 0
    front_warning = 0
    #print "scan_data:", len(sortedIndices)
    # if we already have a last scan to compare to:
    for i in sortedIndices:
        if len(np.array(scan_data.ranges)) == 720:
            # 通过清除不需要的扇区的数据来保留有效的数据
            # Keep valid data by purging data from unneeded sectors
            if 20 < i < LaserAngle * 2:
                if ranges[i] < ResponseDist: Left_warning += 1
            elif (720 - LaserAngle * 2) < i < 700:
                if ranges[i] < ResponseDist: Right_warning += 1
            elif (700 <= i ) or ( i <= 20):
                if ranges[i] <= ResponseDist: front_warning += 1
        elif len(np.array(scan_data.ranges)) == 360:
            # 通过清除不需要的扇区的数据来保留有效的数据
            # Keep valid data by purging data from unneeded sectors
            if 10 < i < LaserAngle:
                if ranges[i] < ResponseDist: Left_warning += 1
            elif (350 - LaserAngle) < i < 350:
                if ranges[i] < ResponseDist: Right_warning += 1
            elif (350 <= i <= 360) or (0<= i <=10):
                # print ("i: {},dist: {}", format(i, ranges[i]))
                if ranges[i] < ResponseDist: front_warning += 1
    # print (Left_warning,front_warning,Right_warning)

sub_laser = rospy.Subscriber('/scan', LaserScan, registerScan)

def getCollision():
    if self.front_warning > 10:
        return "front"
    if self.Left_warning > 10:
        return "left"
    if self.Right_warning > 10:
        return "right"
    return "free"

