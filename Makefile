CPPFLAGS= -I. -I/opt/opencv/include
CXXFLAGS= -Wall -Wextra -Werror
LDFLAGS = -Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui\
	-lopencv_features2d\
	-lopencv_nonfree\
	-lopencv_calib3d\
	-lopencv_objdetect\
	-lopencv_flann
#	-lopencv_imgcodecs

#modify DATA or VIEWER path command if not applicable
VIEWER= pvisu
DATA= ../data
DATA_2= ../data_2
IMAGE= 072-rgb.png
IMAGE_2= croix1-rgb.png

BIN=\
	harris_detector \
	lines-detector \
	harris_detector_v2 \
	lines-detector_v2 \
	lines-detector_v3 \
	bannnannne \
	find_picture_motif_homography


.PHONY: all clean cleanall
all: $(BIN)

.PHONY: test
test: harris_detector lines-detector harris_detector_v2 lines-detector_v2 lines-detector_v3 bannnannne find_picture_motif_homography
	./harris_detector $(DATA)/$(IMAGE)
	./lines-detector $(DATA)/$(IMAGE)
	./harris_detector_v2 $(DATA)/$(IMAGE)
	./lines-detector_v2 $(DATA)/$(IMAGE)
	./lines-detector_v3 $(DATA)/$(IMAGE)
	./bannnannne $(DATA)/$(IMAGE)
	./find_picture_motif_homography $(DATA)/$(IMAGE) $(DATA_2)/$(IMAGE_2)

#view-2.png

clean:
	$(RM) *~ *.png
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
