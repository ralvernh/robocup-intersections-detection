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

# the must:   https://medium.com/@kylepob61392/airplane-image-classification-using-a-keras-cnn-22be506fdb53


#très (trop) avancé:

"""
 https://github.com/bandiatindra/Object-Detection-Project/blob/master/Object%20Detection%20on%20Google%20Open%20AI%20Images.ipynb

 https://towardsdatascience.com/object-detection-using-google-ai-open-images-4c908cad4a54
"""
#__________________________________________________________________________________________

LABELS = ['Croix', 'T', 'Angles']

IMAGE_ANGLES_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\Angles"
IMAGE_CROIX_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\Croix"
IMAGE_T_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\Ts"
IMAGE_RIEN_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\IMAGES\rien"

file_paths_angles = glob.glob(path.join(IMAGE_ANGLES_PATH, '*.png'))
file_paths_croix = glob.glob(path.join(IMAGE_CROIX_PATH, '*.png'))
file_paths_T = glob.glob(path.join(IMAGE_T_PATH, '*.png'))
file_paths_rien = glob.glob(path.join(IMAGE_RIEN_PATH, '*.png'))

# regrouper les chemins
file_paths=[]
file_paths.append(file_paths_angles)
file_paths.append(file_paths_croix)
file_paths.append(file_paths_T)
file_paths.append(file_paths_rien)

# Load the images
images_angles = [misc.imread(path) for path in file_paths_angles]
images_angles = np.asarray(images_angles)
#-----------------
images_croix = [misc.imread(path) for path in file_paths_croix]
images_croix = np.asarray(images_croix)
#-----------------
images_T = [misc.imread(path) for path in file_paths_T]
images_T = np.asarray(images_T)
#-----------------
images_rien = [misc.imread(path) for path in file_paths_rien]
images_rien = np.asarray(images_rien)
#-----------------

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
#-----------------

# Scale
images_angles = images_angles / 255
#-----------------
images_croix = images_croix / 255
#-----------------
images_T = images_T / 255
#-----------------
images_rien = images_rien / 255
#-----------------

n_images_angles = images_angles.shape[0]
n_images_croix = images_croix.shape[0]
n_images_T = images_T.shape[0]
n_images_rien = images_rien.shape[0]

#regrouper toutes les images
images=[]
images.append([images_angles])
images.append([images_croix])
images.append([images_T])
images.append([images_rien])

#regrouper les tailles des images
tailles_immmages=[]
tailles_immmages.append([n_images_angles])
tailles_immmages.append([n_images_croix])
tailles_immmages.append([n_images_T])
tailles_immmages.append([n_images_rien])

# Read the labels from the filenames
n_images = images.shape[0]
labels = np.zeros(len(tailles_immmages)-1)

#----------------------------------------------------------------------------
for(j in range(len(tailles_immmages)-1)):
    for i in range(tailles_immmages[j]):
        filename = path.basename(file_paths[j][i])[0]
        if(filename[0]="r"):   # rgb: que_dalle -> 3
            labels[j][i] = 3
        else:
            labels[j][i] = int(filename[0])
        # 0: "croix", 1: "T", 2: "angle", rgb -> 3: que_dalle
#----------------------------------------------------------------------------

    
 # Split into test and training sets
TRAIN_TEST_SPLIT = 0.9


compteur=0
x_train = []
y_train = []
x_test = []
y_test = []

for(j in range(len(tailles_immmages)-1)):
    i = tailles_immmages[j]
    # Split at the given index
    split_index = int(TRAIN_TEST_SPLIT * i)
    shuffled_indices = np.random.permutation(i)
        
    # 0%-90% -> train   90%-100% -> test
    train_indices = shuffled_indices[0:split_index]
    test_indices = shuffled_indices[split_index:]
    
    # Split the images and the labels
    #(NB: "list.extend(list2)" adds the elements in "list2" to the end of the "list". donc != .append() )
    x_train.extend( images[j][train_indices, :, :] )
    y_train.extend( labels[j][train_indices] )
    x_test.extend( images[j][test_indices, :, :] )
    y_test.extend( labels[j][test_indices] )



#_______________________________________CNN_NETWORK______________________________________________________________________________________________________________________________________________________________________________________________________________________________

# Initialising the CNN
model = Sequential()
# Step 1 - Convolution
model.add(Convolution2D(32, 3, 3, input_shape = (64, 64, 3), activation = 'relu'))
# Step 2 - Pooling
model.add(MaxPooling2D(pool_size = (2, 2)))
# Adding a second convolutional layer
model.add(Convolution2D(32, 3, 3, activation = 'relu'))
model.add(MaxPooling2D(pool_size = (2, 2)))
# Step 3 - Flattening
model.add(Flatten())
# Step 4 - Full connection
model.add(Dense(units=128,activation="relu",input_shape=(784,)))
model.add(Dense(units=128,activation="relu"))
model.add(Dense(units=128,activation="relu"))
model.add(Dense(units=4,activation="softmax"))
# Compiling the CNN
model.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

# time to work and so to ...TRAIN!!!!
model.fit(train_x,train_y,batch_size=32,epochs=20,verbose=1)



# ou:
"""
# Training hyperparamters
EPOCHS = 150
BATCH_SIZE = 200

#------------------------------------------------------------------------
# Early stopping callback
PATIENCE = 10
early_stopping = EarlyStopping(monitor='loss', min_delta=0, patience=PATIENCE, verbose=0, mode='auto')
# TensorBoard callback
LOG_DIRECTORY_ROOT = ''
now = datetime.utcnow().strftime("%Y%m%d%H%M%S")
log_dir = "{}/run-{}/".format(LOG_DIRECTORY_ROOT, now)
tensorboard = TensorBoard(log_dir=log_dir, write_graph=True, write_images=True)
# Place the callbacks in a list
callbacks = [early_stopping, tensorboard]
#------------------------------------------------------------------------

# Train the model !!!!!!
model.fit(x_train, y_train, epochs=EPOCHS, batch_size=BATCH_SIZE, callbacks=callbacks, verbose=0)
"""


#_________________________________________MODEL_EVALUATION_______________________________________________________________________________________________________________________________________________________________________________________________________________________



# Make a prediction on the test set -> 0: "no"  1: "yes"
test_predictions = model.predict(x_test)
test_predictions = np.round(test_predictions)

#récupérer les classes de la base de test (0 ou 1 ou 2 ou 3)
img = y_test[130]
test_img = img.reshape((1,784))

img_class = model.predict_classes(test_img)
prediction = img_class[0]
print("Class: ",prediction)

label_indices_cross = (y_test == 0)
label_indices_T = (y_test == 1)
label_indices_angle = (y_test == 2)

# Report the accuracy
accuracy = accuracy_score(y_test, test_predictions)
print("Accuracy: " + str(accuracy))


"""
TEMPLATES_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates"

"""



def visualise_image_I(i, x_test, y_test, test_predictions, image, label_indices_cross, label_indices_T, label_indices_angle, LABELS):

    TEMPLATE_CROSS_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates\img13.jpg"

    TEMPLATE_T_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates\img11.jpg"

    TEMPLATE_ANGLE_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates\img2.jpg"
    
    if (test_predictions[i] == 1):  # image reconnue
        if (y_test[i] == label_indices_cross[0]):  # rang 0 pour "label_indices_cross" : au pif
            template = image.load_img(TEMPLATE_CROSS_PATH, target_size = (64, 64))
            template_name = LABELS[0]
        else if(y_test[i]== label_indices_T[0] ):  # rang 0 pour "label_indices_T" : au pif
            template = image.load_img(TEMPLATE_T_PATH, target_size = (64, 64))
            template_name = LABELS[1]
        else if(y_test[i]== label_indices_angle[0] ):  # rang 0 pour "label_indices_angle" : au pif
            template = image.load_img(TEMPLATE_ANGLE_PATH, target_size = (64, 64))
            template_name = LABELS[2]

        w, h = template.shape[::-1]
        
        method = eval('cv2.TM_CCOEFF')
        res = cv2.matchTemplate(x_test[i],template,method)
        min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)

        top_left = max_loc
        bottom_right = (top_left[0] + w, top_left[1] + h)
        
        pos_centx=int((bottom_right[0]+top_left[0])/2)
        pos_centy=int((bottom_right[1]+top_left[1])/2)

        cv2.rectangle(frame,top_left, bottom_right, (0,255,0), 2)
        resIM=res-np.amin(res)
        VarMod=1000*(np.var(resIM)/1.02295316e+20)
        
        #print(np.mean(resIM*VarMod))
        resIM=VarMod*resIM
        if(np.mean(resIM)>15):
            evaligne = template_name

        else:
            evaligne = "???"

    
        cv2.putText(x_test[i] ,evaligne, bottom_right, cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        
        if(template_name = LABELS[0]):
            cv2.putText(x_test[i] ,"X", (pos_centx, pos_centy), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        if(template_name = LABELS[1]):
            cv2.putText(x_test[i] ,"T", (pos_centx, pos_centy), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        if(template_name = LABELS[1]):
            cv2.putText(x_test[i] ,"L", (pos_centx, pos_centy), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        # ou: cv2.line(x_test[i],(x1,y1), (x2,y2),(255,0,0),2)
    

    #figure.add_subplot(maximum_square, maximum_square, count)
    plt.imshow(x_data[i, :, :, :])
    plt.axis('off')
    plt.title("whouaw" , fontsize=10)
    plt.show()


visualise_image_I(i, x_test, y_test, test_predictions, image, label_indices_cross, label_indices_T, label_indices_angle, LABELS)


"""

TEMPLATE_CROSS_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates\img13.jpg"

TEMPLATE_T_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates\img11.jpg"

TEMPLATE_ANGLE_PATH = r"C:\Users\Romain\Desktop\Outils_d_imagerie_pour_la_robotique\PROJET_OUTILS_DIMAGERIE_ROB\super_templates\img2.jpg"



for i in y_test : #ou séléction de la i-ème frame  à visionner (sans doute mieux)
    if (test_predictions == 1):  # image reconnue
        if (i == label_indices_cross):
            template = image.load_img(TEMPLATE_CROSS_PATH, target_size = (64, 64))
            template_name = LABELS[0]
        else if(i== label_indices_T ):
            template = image.load_img(TEMPLATE_T_PATH, target_size = (64, 64))
            template_name = LABELS[1]
        else if(i== label_indices_angle ):
            template = image.load_img(TEMPLATE_ANGLE_PATH, target_size = (64, 64))
            template_name = LABELS[2]

        w, h = template.shape[::-1]
    
        method = eval('cv2.TM_CCOEFF')
        res = cv2.matchTemplate(x_test[i],template,method)
        min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)

        top_left = max_loc
        bottom_right = (top_left[0] + w, top_left[1] + h)
        
        pos_centx=int((bottom_right[0]+top_left[0])/2)
        pos_centy=int((bottom_right[1]+top_left[1])/2)

        cv2.rectangle(frame,top_left, bottom_right, (0,255,0), 2)
        resIM=res-np.amin(res)
        VarMod=1000*(np.var(resIM)/1.02295316e+20)
        #print(np.mean(resIM*VarMod))
        resIM=VarMod*resIM
        if(np.mean(resIM)>15):
            evaligne = template_name

        else:
            evaligne=' ??? '

    
        cv2.putText(x_test[i] ,evaligne, bottom_right, cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        
        if(template_name = LABELS[0]):
            cv2.putText(x_test[i] ,"X", (pos_centx, pos_centy), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        if(template_name = LABELS[1]):
            cv2.putText(x_test[i] ,"T", (pos_centx, pos_centy), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        if(template_name = LABELS[1]):
            cv2.putText(x_test[i] ,"L", (pos_centx, pos_centy), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)
        # ou: cv2.line(x_test[i],(x1,y1), (x2,y2),(255,0,0),2)
    
image_visualisee= 15 #au pif

figure.add_subplot(maximum_square, maximum_square, count)
plt.imshow(x_data[image_visualisee, :, :, :])
plt.axis('off')
plt.title("whouaw" , fontsize=10)
plt.show()

"""





#---------------------------------------------------------------------------------

def visualize_incorrect_labels(x_data, y_real, y_predicted):
    # INPUTS
    # x_data      - images
    # y_data      - ground truth labels
    # y_predicted - predicted label
    count = 0
    figure = plt.figure()
    incorrect_label_indices = (y_real != y_predicted)
    y_real = y_real[incorrect_label_indices]
    y_predicted = y_predicted[incorrect_label_indices]
    x_data = x_data[incorrect_label_indices, :, :, :]

    maximum_square = np.ceil(np.sqrt(x_data.shape[0]))

    for i in range(x_data.shape[0]):
        count += 1
        figure.add_subplot(maximum_square, maximum_square, count)
        plt.imshow(x_data[i, :, :, :])
        plt.axis('off')
        plt.title("Predicted: " + str(int(y_predicted[i])) + ", Real: " + str(int(y_real[i])), fontsize=10)

    plt.show()

#visualize_incorrect_labels(x_test, y_test, np.asarray(test_predictions).ravel())


#---------------------------------------------------------------------------------













#   peut-être utiliser LIGNES SUIVANTES:


"""


#______________________________________DEF_FUNCTIONS__________________________________________________________________________________________________________________________________

class BoundBox:
    def __init__(self, xmin, ymin, xmax, ymax, c = None, classes = None):
        self.xmin = xmin
        self.ymin = ymin
        self.xmax = xmax
        self.ymax = ymax
        
        self.c     = c
        self.classes = classes

        self.label = -1
        self.score = -1

    def get_label(self):
        if self.label == -1:
            self.label = np.argmax(self.classes)
        
        return self.label
    
    def get_score(self):
        if self.score == -1:
            self.score = self.classes[self.get_label()]
            
        return self.score


def draw_boxes(image, boxes, labels):
    image_h, image_w, _ = image.shape

    for box in boxes:
        xmin = int(box.xmin*image_w)
        ymin = int(box.ymin*image_h)
        xmax = int(box.xmax*image_w)
        ymax = int(box.ymax*image_h)

        cv2.rectangle(image, (xmin,ymin), (xmax,ymax), (0,0,255), 8)
        cv2.putText(image, 
                    labels[box.get_label()] + ' ' + str(round(box.get_score(),2)), 
                    (xmin  , ymin ), 
                    cv2.FONT_HERSHEY_TRIPLEX, 
                    1e-3 * image_h*1, 
                    (255,255,255), 7)
        
    return image


#_____________________________________________________________________________________________________________________________________________________________________________________

 


image = cv2.imread('../../../../validation/group_pic.jpg')

dummy_array = np.zeros((1,1,1,1,TRUE_BOX_BUFFER,4))

input_image = cv2.resize(image, (608, 608))
input_image = input_image / 255.
input_image = input_image[:,:,::-1]
input_image = np.expand_dims(input_image, 0)
    
netout = model.predict([input_image, dummy_array])
boxes = decode_netout(netout[0], 
                  obj_threshold=0.4,
                  nms_threshold=0.3,
                  anchors=ANCHORS, 
                  nb_class=CLASS)
    
image = draw_boxes(image, boxes, labels=LABELS)
plt.imshow(image[:,:,::-1]); plt.show()
"""          











