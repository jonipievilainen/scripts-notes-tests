"""
@file hough_lines.py
@brief This program demonstrates line finding with the Hough transform
"""
import sys
import math
import cv2 as cv
import numpy as np
from functools import reduce

def pointter( window, point ):
  cv.circle(window, point, radius=2, color=(0, 255, 0), thickness=-1)

def liner( window, point, point2 ):
  cv.line(window, point,point2, (255, 0, 0), 2)

def convex_hull_graham(points):
    '''
    Returns points on convex hull in CCW order according to Graham's scan algorithm. 
    By Tom Switzer <thomas.switzer@gmail.com>.
    '''
    TURN_LEFT, TURN_RIGHT, TURN_NONE = (1, -1, 0)

    def cmp(a, b):
        # return (a > b) - (a < b)
        return np.subtract((a > b), (a < b), dtype=np.float32)

    def turn(p, q, r):
        return cmp((q[0] - p[0])*(r[1] - p[1]) - (r[0] - p[0])*(q[1] - p[1]), 0)

    def _keep_left(hull, r):
        while len(hull) > 1 and turn(hull[-2], hull[-1], r) != TURN_LEFT:
            hull.pop()
        if not len(hull) or hull[-1] != r:
            hull.append(r)
        return hull

    points = sorted(points)
    l = reduce(_keep_left, points, [])
    u = reduce(_keep_left, reversed(points), [])
    return l.extend(u[i] for i in range(1, len(u) - 1)) or l

def closest_node(node, nodes):
    nodes = np.asarray(nodes)
    deltas = nodes - node
    dist_2 = np.einsum('ij,ij->i', deltas, deltas)
    return np.argmin(dist_2)

def main(argv):
    
    default_file = 'line.png'
    default_file = 'kivi.png'
    filename = argv[0] if len(argv) > 0 else default_file
    # Loads an image
    src = cv.imread(cv.samples.findFile(filename), cv.IMREAD_GRAYSCALE)
    # Check if image is loaded fine
    if src is None:
        print ('Error opening image!')
        print ('Usage: hough_lines.py [image_name -- default ' + default_file + '] \n')
        return -1
    
    
    dst = cv.Canny(src, 50, 200, None, 3)
    
    # Copy edges to the images that will display the results in BGR
    cdst = cv.cvtColor(dst, cv.COLOR_GRAY2BGR)
    cdstP = np.copy(cdst)
    
    lines = cv.HoughLines(dst, 1, np.pi / 180, 150, None, 0, 0)
    
    # if lines is not None:
    #     for i in range(0, len(lines)):
    #         rho = lines[i][0][0]
    #         theta = lines[i][0][1]
    #         a = math.cos(theta)
    #         b = math.sin(theta)
    #         x0 = a * rho
    #         y0 = b * rho
    #         pt1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a)))
    #         pt2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a)))
    #         cv.line(cdst, pt1, pt2, (0,0,255), 3, cv.LINE_AA)
    
    
    linesP = cv.HoughLinesP(dst, 1, np.pi / 180, 1, None, 111, 111)

    my_list = []
    # my_list = [[329, 296], [453, 420], [328, 303], [447, 422], [332, 298], [451, 391]]
    
    if linesP is not None:
        for i in range(0, len(linesP)):
            l = linesP[i][0]
            # cv.line(cdstP, (l[0], l[1]), (l[2], l[3]), (0,0,255), 3, cv.LINE_AA)
            # pointter( cdst, (l[0], l[1]))
            # pointter( cdstP, (l[2], l[3]))
            # liner( cdstP, (l[0], l[1]), (l[2], l[3]))
            my_list.append([l[0], l[1]])
            my_list.append([l[2], l[3]])
    

    cover_points = convex_hull_graham(my_list)
    temp = cover_points

    # print(cover_points)

    if cover_points is not None:
        size = len(cover_points)
        print(size)
        last_point = (1,1)
        for i in range(0, len(cover_points)):
            l = cover_points[i]
            # i += 1
            # ll = cover_points[i]
            # pointter( cdst, (l[0], l[1]))
            # pointter( cdstP, (l[2], l[3]))
            print(l)
            # print(ll)
            # liner( cdstP, tuple(l), tuple(ll))
            cv.circle(cdstP, tuple(l), 2, (255, 255, 0), -1)


            closest = closest_node(tuple(l) , temp)
            ll = temp[closest]
            print(ll)
            # cv.circle(cdstP, tuple(ll), 4, (0, 255, 255), -1)
            print("------")
            liner( cdstP, last_point, tuple(ll))
            # del temp[i]
            last_point = tuple(ll)

            if i > size:
                break


    

    cv.imshow("Source", src)
    # cv.imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst)
    cv.imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP)
    
    cv.waitKey()
    return 0
    
if __name__ == "__main__":
    main(sys.argv[1:])