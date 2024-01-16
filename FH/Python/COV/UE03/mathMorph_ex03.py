import cv2 as cv
import numpy as np
import argparse

#from https://docs.opencv.org/master/d3/dbe/tutorial_opening_closing_hats.html

morph_size = 0
max_operator = 4
max_elem = 2
max_kernel_size = 21
title_trackbar_operator_type = 'Operator:\n 0: Opening - 1: Closing  - 2: Erode \n 3: Dilate'
title_trackbar_element_type = 'Element:\n 0: Rect - 1: Cross - 2: Ellipse'
title_trackbar_kernel_size = 'Kernel size:\n 2n + 1'
title_window = 'Morphology Transformations Demo'
morph_op_dic = {0: cv.MORPH_OPEN, 1: cv.MORPH_CLOSE, 2: cv.MORPH_ERODE, 3: cv.MORPH_DILATE}

#inFilePath = "D:/LEHRE/_COV_ComputerVision_DSE/Exercises/openCV_material/color_monkey.jpg"
inFilePath = "D:/LEHRE/_COV_ComputerVision_DSE/Exercises/openCV_material/gray_monkey.png"


def morphology_operations(val):
    morph_operator = cv.getTrackbarPos(title_trackbar_operator_type, title_window)
    morph_size = cv.getTrackbarPos(title_trackbar_kernel_size, title_window)
    morph_elem = 0
    val_type = cv.getTrackbarPos(title_trackbar_element_type, title_window)
    if val_type == 0:
        morph_elem = cv.MORPH_RECT
    elif val_type == 1:
        morph_elem = cv.MORPH_CROSS
    elif val_type == 2:
        morph_elem = cv.MORPH_ELLIPSE

    element = cv.getStructuringElement(morph_elem, (2*morph_size + 1, 2*morph_size+1), (morph_size, morph_size))
    operation = morph_op_dic[morph_operator]
    dst = cv.morphologyEx(src, operation, element)
    cv.imshow(title_window, dst)


src = cv.imread(inFilePath)
Tmin = 140
Tmax = 200
doSegment = True #False

if doSegment : 
   srcBin = src.copy()
   subImgRange = (src > Tmin) & (src < Tmax)
   srcBin[:] = 0
   srcBin[subImgRange] = 255
   src = srcBin

if src is None:
    print('Could not open or find the image: ', inFilePath)
    exit(0)

cv.namedWindow(title_window)
cv.createTrackbar(title_trackbar_operator_type, title_window , 0, max_operator, morphology_operations)
cv.createTrackbar(title_trackbar_element_type, title_window , 0, max_elem, morphology_operations)
cv.createTrackbar(title_trackbar_kernel_size, title_window , 0, max_kernel_size, morphology_operations)

morphology_operations(0)
cv.waitKey()