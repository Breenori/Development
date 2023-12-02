# -*- coding: utf-8 -*-
"""
Created on Fri Jun 25 14:50:07 2021

@author: p21702
"""
from AugmentationProcess import * 
import ImageIOUtility
import cv2
import random as rand

inImgID = 1
inPath1 = "...."

#width = 600
#height = 600

targetNumOfImages = 2000

#interpolation strategy and the random transform range
configParameters1 = [cv2.INTER_LANCZOS4, 0.2, 0.2, 90.0]
at1 = AffineTransformationAP(1, 'affineTransformation', configParameters1, width, height)
print('first process allocated')

configParameters2 = [.7, 1.3]
at2 = GammaCorrectionAP(2, 'gamma correction', configParameters2, width, height)
print('second process allocated')

#and so on

#TODO random select images

at1.reInit() #with new random values
at2.reInit() 
      
aImg1 = at1.augmentImage(currImage)
aImg2 = at2.augmentImage(aImg1)
#and so on and finally store the result image after being assembled     
        