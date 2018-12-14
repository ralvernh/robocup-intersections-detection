CPPFLAGS= -I. -I/opt/opencv/include
CXXFLAGS= -Wall -Wextra -Werror
LDFLAGS = -Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui\
	-lopencv_features2d\
	-lopencv_calib3d\
	-lopencv_objdetect\
	-lopencv_flann\
	-lopencv_imgcodecs	
	#-lopencv_nonfree

#modify DATA or VIEWER path command if not applicable
VIEWER= pvisu
DATA='../data/log1/'
IMAGE=$(DATA)/143-rgb.png

BIN=\
	harris\
	lines-detector_v3\


.PHONY: all clean cleanall
all: $(BIN)

.PHONY: test
test: 
	./harris $(IMAGE)
	#./lines-detector_v3 $(DATA)/$(IMAGE)

#view-2.png

clean:
	$(RM) *~ *.png
cleanall: clean
	$(RM) $(BIN) *.o
