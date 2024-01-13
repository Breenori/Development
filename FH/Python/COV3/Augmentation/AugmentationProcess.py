# -*- coding: utf-8 -*-
"""
Created on Sat Jun 19 10:35:16 2021

@author: p21702
"""

import numpy as np
import cv2
import ImageIOUtility
import random as rand

#base class
#augmentationParameters: the random values to be applied
#configParameters: the possible range
class AugmentationProcessBase:
  def __init__(self, ID, name, augmentationParameters, configParameters):
    self.ID = ID
    self.name = name
    self.augmentationParameters = augmentationParameters
    self.configParameters = configParameters
    
  def __init__(self, ID, name, configParameters, width, height):
    self.ID = ID
    self.name = name   
    self.configParameters =  configParameters
    self.augmentationParameters = self.getRandomAugmentationParameters(width, height) 
    self.width = width
    self.height = height

  def reInit(self) :
    self.augmentationParameters = self.getRandomAugmentationParameters(self.width, self.height) 

  def augmentImage(self, inImage):
      return None

  def print(self):
    print(self.name + " [" + self.ID + "], params = " + self.parameters)
    
  #generate the level of variation
  #if image and reference mask and so on need to get transformed, then this 
  #random setup is generated once and then utilized  
  def getRandomAugmentationParameters(self, width, height) :
      return None
  

#child classes

#Rotate, Translate
class AffineTransformationAP(AugmentationProcessBase):    
    
    def getRandomAugmentationParameters(self, width, height) :      
       #Tx = rand.random() * ???
       #Ty = rand.random() * ????
       #Rot = rand.random() * ???
       return [Tx, Ty, Rot]
    
    def augmentImage(self, inImage):
      
       #imageFinal = cv2.warpAffine(imageFinal,M,(width, height),flags=interpMode)      
       return imageFinal
       
#perform gamma correction   
class GammaCorrectionAP(AugmentationProcessBase):   

    def getRandomAugmentationParameters(self, width, height) :
        gamma = rand.random() * ???        
        return [gamma] #gamma
    
    def augmentImage(self, inImage):  
        #TODO
        return rgbImg
 
#perform sharpening / unsharpening   
class ConvolutionAP(AugmentationProcessBase):   

    def getRandomAugmentationParameters(self, width, height) :
       print('TODO')
	   return [params]
    
    def augmentImage(self, inImage):  
       print('TODO')
       return resultImg
       


#perform sharpening / unsharpening   
class NoiseAP(AugmentationProcessBase):   

    def getRandomAugmentationParameters(self, width, height) :
       print('TODO')
	   return [params]
    
    def augmentImage(self, inImage):  
       print('TODO')
       return resultImg

