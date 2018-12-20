import keras
import cv2
import glob
import matplotlib.pyplot as plt
import os.path as path
import numpy as np
from keras.datasets import mnist
from keras.layers import Convolution2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.models import Sequential
from keras.optimizers import SGD
from keras.preprocessing import image
from keras.preprocessing.image import ImageDataGenerator
from IPython.display import display
from PIL import Image
from scipy import misc

IMAGE_ANGLES_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\Angles"
IMAGE_CROIX_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\Croix"
IMAGE_T_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\Ts"
IMAGE_RIEN_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\rien"
##############################################################################################################
IMAGE_ANGLES_dest_PATH = "C:\\Users\\Romain\\Desktop\\Outils_d_imagerie_pour_la_robotique\\PROJET_OUTILS_DIMAGERIE_ROB\\IMAGES\\Angles_dest"
IMAGE_CROIX_dest_PATH = "C:\\Users\\Romain\\Desktop\\Outils_d_imagerie_pour_la_robotique\\PROJET_OUTILS_DIMAGERIE_ROB\\IMAGES\\Croix_dest"
IMAGE_T_dest_PATH = "C:\\Users\\Romain\\Desktop\\Outils_d_imagerie_pour_la_robotique\\PROJET_OUTILS_DIMAGERIE_ROB\\IMAGES\\Ts_dest"
IMAGE_RIEN_dest_PATH = "C:\\Users\\Romain\\Desktop\\Outils_d_imagerie_pour_la_robotique\\PROJET_OUTILS_DIMAGERIE_ROB\\IMAGES\\rien_dest"

"""
file_paths_angles = glob.glob(path.join(IMAGE_ANGLES_PATH, '*.png'))
file_paths_croix = glob.glob(path.join(IMAGE_CROIX_PATH, '*.png'))
file_paths_T = glob.glob(path.join(IMAGE_T_PATH, '*.png'))
file_paths_rien = glob.glob(path.join(IMAGE_RIEN_PATH, '*.png'))
"""

# https://stackoverflow.com/questions/26392336/importing-images-from-a-directory-python

images_angles = []
for filename in glob.glob("{xxx}/*.png".format(xxx=IMAGE_ANGLES_PATH)): 
    im=Image.open(filename)
    im = np.asarray(im)
    images_angles.append(im)
#----------------------------------------------------------------------------
images_croix = []
for filename in glob.glob("{xxx}/*.png".format(xxx=IMAGE_CROIX_PATH)): 
    im=Image.open(filename)
    im = np.asarray(im)
    images_croix.append(im)
#----------------------------------------------------------------------------
images_T = []
for filename in glob.glob("{xxx}/*.png".format(xxx=IMAGE_T_PATH)): 
    im=Image.open(filename)
    im = np.asarray(im)
    images_T.append(im)
#----------------------------------------------------------------------------
images_rien = []
for filename in glob.glob("{xxx}/*.png".format(xxx=IMAGE_RIEN_PATH)): 
    im=Image.open(filename)
    im = np.asarray(im)
    images_rien.append(im)
#----------------------------------------------------------------------------


"""
# Load the images
images_angles = [misc.imread(path) for path in file_paths_angles]
#images_angles = np.asarray(images_angles)
#-----------------
images_croix = [misc.imread(path) for path in file_paths_croix]
#images_croix = np.asarray(images_croix)
#-----------------
images_T = [misc.imread(path) for path in file_paths_T]
#images_T = np.asarray(images_T)
#-----------------
images_rien = [misc.imread(path) for path in file_paths_rien]
#images_rien = np.asarray(images_rien)
#-----------------
"""


# Get image size
image_size_angles = np.asarray([images_angles.shape[1], images_angles.shape[2], images_angles.shape[3]])
print(image_size_angles)
#-----------------
image_size_croix = np.asarray([images_croix.shape[1], images_croix.shape[2], images_croix.shape[3]])
print(image_size_croix)
#-----------------
image_size_T = np.asarray([images_T.shape[1], images_T.shape[2], images_T.shape[3]])
print(image_size_T)
#-----------------
image_size_rien = np.asarray([images_rien.shape[1], images_rien.shape[2], images_rien.shape[3]])
print(image_size_rien)




indice_img=1

dest_cpy_path=IMAGE_CROIX_dest_PATH
filename_croix=r"{0}\0croix{1}.png".format(dest_cpy_path,indice_img)

dest_cpy_path=IMAGE_T_dest_PATH
filename_T=r"{0}\1t{1}.png".format(dest_cpy_path,indice_img)

dest_cpy_path=IMAGE_ANGLES_dest_PATH
filename_ang=r"{0}\2ang{1}.png".format(dest_cpy_path,indice_img)

dest_cpy_path=IMAGE_RIEN_dest_PATH
filename_rien=r"{0}\3rien{1}.png".format(dest_cpy_path,indice_img)

indice_img=1
dest_cpy_path=IMAGE_ANGLES_dest_PATH
image1=images_angles[0]
#---------------------------------------
for i in range (0,18):
    image1=images_angles[i]
    cv2.imwrite(filename_ang, image1)
    indice_img+=1
    filename_ang="2ang{}.png".format(indice_img)

indice_img=1
dest_cpy_path=IMAGE_CROIX_dest_PATH
image2=images_croix[0]
#---------------------------------------
for i in range (0,74):
    image2=images_croix[i]
    cv2.imwrite(filename_croix, image2)
    indice_img+=1
    filename_croix="0croix{}.png".format(indice_img)
    
indice_img=1   
dest_cpy_path=IMAGE_T_dest_PATH
image3=images_T[0]
#---------------------------------------
for i in range (0,10):
    image3=images_T[i]
    cv2.imwrite(filename_T, image3)
    indice_img+=1
    filename_T="1t{}.png".format(indice_img)

indice_img=1
dest_cpy_path=IMAGE_RIEN_dest_PATH
image4=images_rien[0]
#---------------------------------------
for i in range (0,408):
    image4=images_rien[i]
    cv2.imwrite(filename_rien, image4)
    indice_img+=1
    filename_rien="3rien{}.png".format(indice_img)
    

