# -*- coding: utf-8 -*-
"""
Created on Sat Jun 19 11:25:37 2021

@author: p21702
"""

import cv2
import os

def loadImage(filePath) :
    inImg = cv2.imread(filePath)
    return inImg


def saveImage(tgtFilePath, image) :
    cv2.imwrite(tgtFilePath, image)
    
    
def getAllFilesFromDirectory(inDirectory) :
   #files = os.listdir(inDirectory)
   #return files
   path = os.path.abspath(inDirectory)
   return [entry.path for entry in os.scandir(path) if entry.is_file()]

def getHSVimage(imageRGB) :
   hsv = cv2.cvtColor(imageRGB, cv2.COLOR_BGR2HSV)
   return hsv


def getRGBimage(imageHSV) :
   rgb = cv2.cvtColor(imageHSV, cv2.COLOR_HSV2BGR)
   return rgb