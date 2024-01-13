# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 14:05:18 2020

@author: P21702
"""

#adapted from https://docs.opencv.org/master/d1/dc5/tutorial_background_subtraction.html

import cv2
import numpy as np

inVideoPath = "data\\vtest.avi"

capture = cv2.VideoCapture(inVideoPath)
if not capture.isOpened:
    #print('Unable to open: ' + args.input)
    exit(0)

frameCount = 0
delayInMS = 100
threshold = 50
weight = 0.01

cumulatedFrame = None
while True:
    ret, frame = capture.read()
    if frame is None:
        break

    frameCopy = frame.copy()

    if frameCount == 0:
        buffer = []
        cumulatedFrame = np.zeros(frameCopy.shape)
        cumulatedFrame = cumulatedFrame + frameCopy
        frameCount = 1
    else:
        cumulatedFrame += frameCopy
        frameCount += 1


avgFrame = cumulatedFrame / frameCount


capture = cv2.VideoCapture(inVideoPath)
if not capture.isOpened:
    #print('Unable to open: ' + args.input)
    exit(0)

frameCount = 0
while True:
    ret, frame = capture.read()
    if frame is None:
        break

    frameCopy = frame.copy()

    cv2.rectangle(frame, (10, 2), (100,20), (255,255,255), -1)
    cv2.putText(frame, str(capture.get(cv2.CAP_PROP_POS_FRAMES)), (15, 15),
               cv2.FONT_HERSHEY_SIMPLEX, 0.5 , (0,0,0))

    cv2.imshow('current frame ', frame)

    delta = cv2.absdiff(frame.astype(np.uint8), avgFrame.astype(np.uint8))
    delta = cv2.cvtColor(delta, cv2.COLOR_BGR2GRAY)
    delta = cv2.morphologyEx(delta, cv2.MORPH_OPEN, np.ones((3, 3), np.uint8), iterations=3)


    delta[delta >= threshold] = 255
    delta[delta < threshold] = 0


    cv2.imshow('delta', delta)


    keyboard = cv2.waitKey(delayInMS)
    if keyboard == 'q' or keyboard == 27:
        exit(-1)