// OpenCV.h
#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

#ifdef _MSC_VER // Visual Studio compiler

# if CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION == 11
// OpenCV version 2.4.11
#  if defined(_DEBUG) // debug versions: '***d.lib'

#  pragma comment(lib, "zlibd.lib")
#  pragma comment(lib, "libjpegd.lib")
#  pragma comment(lib, "libtiffd.lib")
#  pragma comment(lib, "libpngd.lib")
#  pragma comment(lib, "libjasperd.lib")
#  pragma comment(lib, "IlmImfd.lib")

#  pragma comment(lib, "opencv_core2411d.lib")
#  pragma comment(lib, "opencv_highgui2411d.lib")
#  pragma comment(lib, "opencv_imgproc2411d.lib")
#  pragma comment(lib, "opencv_video2411d.lib")
#  pragma comment(lib, "opencv_ml2411d.lib")

#  pragma comment(lib, "opencv_calib3d2411d.lib")
#  pragma comment(lib, "opencv_objdetect2411d.lib")
#  pragma comment(lib, "opencv_features2d2411d.lib")
#  pragma comment(lib, "opencv_contrib2411d.lib")
#  pragma comment(lib, "opencv_ts2411d.lib")
#  pragma comment(lib, "opencv_legacy2411d.lib")
#  pragma comment(lib, "opencv_flann2411d.lib")
#  pragma comment(lib, "opencv_gpu2411d.lib")

#  pragma comment(lib, "opencv_nonfree2411d.lib")
#  pragma comment(lib, "opencv_ocl2411d.lib")
#  pragma comment(lib, "opencv_photo2411d.lib")
#  pragma comment(lib, "opencv_stitching2411d.lib")
#  pragma comment(lib, "opencv_superres2411d.lib")
#  pragma comment(lib, "opencv_videostab2411d.lib")

# else  // release versions: '***.lib'

#  pragma comment(lib, "zlib.lib")
#  pragma comment(lib, "libjpeg.lib")
#  pragma comment(lib, "libtiff.lib")
#  pragma comment(lib, "libpng.lib")
#  pragma comment(lib, "libjasper.lib")
#  pragma comment(lib, "IlmImf.lib")

#  pragma comment(lib, "opencv_core2411.lib")
#  pragma comment(lib, "opencv_highgui2411.lib")
#  pragma comment(lib, "opencv_imgproc2411.lib")
#  pragma comment(lib, "opencv_video2411.lib")
#  pragma comment(lib, "opencv_ml2411.lib")

#  pragma comment(lib, "opencv_calib3d2411.lib")
#  pragma comment(lib, "opencv_objdetect2411.lib")
#  pragma comment(lib, "opencv_features2d2411.lib")
#  pragma comment(lib, "opencv_contrib2411.lib")
#  pragma comment(lib, "opencv_ts2411.lib")
#  pragma comment(lib, "opencv_legacy2411.lib")
#  pragma comment(lib, "opencv_flann2411.lib")
#  pragma comment(lib, "opencv_gpu2411.lib")

#  pragma comment(lib, "opencv_nonfree2411.lib")
#  pragma comment(lib, "opencv_ocl2411.lib")
#  pragma comment(lib, "opencv_photo2411.lib")
#  pragma comment(lib, "opencv_stitching2411.lib")
#  pragma comment(lib, "opencv_superres2411.lib")
#  pragma comment(lib, "opencv_videostab2411.lib")

# endif // defined(_DEBUG)

# endif // CV_MAJOR_VERSION == 2 && CV_MINOR_VERSION == 4 && CV_SUBMINOR_VERSION == 11

#pragma comment(lib, "Vfw32.lib") // 'Video for Windows', used by OpenCV for video capture

#endif // _MSC_VER