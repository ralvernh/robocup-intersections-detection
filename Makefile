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
IMAGE= 145-rgb.png
IMAGE_CHOSE = chose.png
IMAGE_2= croix2-rgb.png

#	072-rgb.png
#	145-rgb.png
BIN=\
	lines-detector_v3 \
	find_picture_motif_homography \
	find_picture_motif_homography_v2 \
	template_matching_opencv \
	template_matching_opencv_v2 \
	template_matching_opencv_v3 \
	template_matching_opencv_v4 \
	harris_detector

#	harris_detector_v2 \
#	harris_detector \
#	lines-detector \
#	lines-detector_v2 \
#	bannnannne \


.PHONY: all clean cleanall
all: $(BIN)

.PHONY: test
test:   lines-detector_v3  find_picture_motif_homography template_matching_opencv template_matching_opencv_v2 harris_detector template_matching_opencv_v3 template_matching_opencv_v4

	./lines-detector_v3 $(DATA)/$(IMAGE)
	./find_picture_motif_homography $(DATA)/$(IMAGE) $(DATA_2)/$(IMAGE_2)
	./template_matching_opencv $(DATA_2)/$(IMAGE) $(DATA_2)/$(IMAGE_2)
	./template_matching_opencv_v2 $(DATA)/$(IMAGE)
	./template_matching_opencv_v3 $(DATA)/$(IMAGE)
	./template_matching_opencv_v4 $(DATA)/$(IMAGE)
	./harris_detector $(DATA)/$(IMAGE_CHOSE)

#	./lines-detector $(DATA)/$(IMAGE)
#	./harris_detector_v2 $(DATA)/$(IMAGE)
#	./lines-detector_v2 $(DATA)/$(IMAGE)
#	./bannnannne $(DATA)/$(IMAGE)
#	./find_picture_motif_homography_v2 $(DATA)/$(IMAGE) $(DATA_2)/$(IMAGE_2)
#view-2.png

clean:
	$(RM) *~ *.png
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
