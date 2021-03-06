
#This part is used for compile faster_rcnn_demo.cpp
cmake_minimum_required (VERSION 2.8)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -g -msse2 -march=native -std=c++11 -fopenmp")
set(LIBPATH "/storage2/public/tunicorn/gs5/dface2/3rdparty")
# include(CheckCXXCompilerFlag)  
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)  
# if(COMPILER_SUPPORTS_CXX11)  
#         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  
#         message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has -std=c++11.") 
# elseif(COMPILER_SUPPORTS_CXX0X)  
#         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
# else()  
#      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
# endif() 
#SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH}
project (main_camera)

#DUSE_CUDNN
add_definitions( -DUSE_OPENCV)


set(RFCN_DIR /home/liushuai/tiannuocaffe/py-rfcn-gpu//)
#set(RFCN_DIR /storage/liushuai/RFCN/py-R-FCN-multiGPU/)


#BLAS := atlas
#USE_CUDNN := 1
#CUDA_ARCH := -gencode arch=compute_30,code=sm_30 \
#        -gencode arch=compute_35,code=sm_35 \
#        -gencode arch=compute_50,code=sm_50 \
#        -gencode arch=compute_50,code=compute_50
#PYTHON_INCLUDE := /usr/include/python2.7 \
#       /usr/lib/python2.7/dist-packages/numpy/core/include \
#  /home/liushuai/storage/mycaffe/include/python2.7 \
#  /home/liushuai/storage/mycaffe/lib64/python2.7/site-packages/numpy/core/include/
#PYTHON_LIB := /usr/lib
#WITH_PYTHON_LAYER := 1

#BUILD_DIR := build
#DISTRIBUTE_DIR := distribute

# ---[ Dependencies
# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
# include(cmake/Dependencies.cmake)

set(BLAS_DIR ${LIBPATH}/OpenBLAS)
include_directories(${BLAS_DIR}/include)
link_directories(${BLAS_DIR}/lib)

set(OpenCV_DIR "${LIBPATH}/opencv/share/OpenCV")
find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(Boost COMPONENTS system filesystem regex REQUIRED)

# include_directories ( "${RFCN_DIR}/caffe/include"
#     "${RFCN_DIR}/caffe/.build_release/src/"
#     "${RFCN_DIR}/caffe/python"
#     "${RFCN_DIR}/lib" 
#     "${RFCN_DIR}/lib/nms" 
#     "${PROJECT_SOURCE_DIR}/lib"
#     /usr/include
#     /usr/local/include 
#     /usr/local/cuda-7.5/include
#     /usr/include
#     /usr/local/cuda
#     /usr/lib
#     /usr/include/python2.7
#     /usr/lib/python2.7/dist-packages/numpy/core/include 
#     /usr/local/cuda/include 
#     /usr/local/opencv_3_1_0/include
#     /storage2/liushuai/work_code/tbb-2018_U2/include/tbb)
include_directories ( "${RFCN_DIR}/caffe/include"
    "${RFCN_DIR}/caffe/.build_release/src/"
    "${RFCN_DIR}/caffe/python"
    "${RFCN_DIR}/lib" 
    "${RFCN_DIR}/lib/nms" 
    "${PROJECT_SOURCE_DIR}/lib"
    /usr/include
    /usr/local/include 
    /usr/local/cuda-7.5/include
    /usr/include
    /usr/local/cuda
    /usr/lib
    /usr/include/python2.7
    /usr/lib/python2.7/dist-packages/numpy/core/include 
    /usr/local/cuda/include 
    "${LIBPATH}/tbb2018_20171205oss/include/tbb")

set(nms_DIR ${RFCN_DIR}/lib/nms)
set(caffe_DIR ${RFCN_DIR}/caffe/.build_release/lib)
set(python_DIR ${RFCN_DIR}/caffe/python)
set(DETECT_DIR ${PROJECT_SOURCE_DIR}/lib)

message(${RFCN_DIR})
message(${nms_DIR})
message(${caffe_DIR})
message(${python_DIR})
message(${DETECT_DIR})

#SUBDIRS(hello sample)
#ADD_SUBDIRECTORY(lib)

SET (SRC_LIST CameraStreamer.hpp )
add_executable(main main.cpp CameraStreamer.cpp)

# link_directories( ${DETECT_DIR}
#     ${caffe_DIR}
#     ${python_DIR}
#     /usr/lib
#     /usr/local/lib
#     /usr/local/cuda-7.5/lib64
#     /storage2/liushuai/work_code/tbb-2018_U2/build/linux_intel64_gcc_cc4.8.5_libc2.17_kernel3.10.0_release )
set(TBB_DIR "${LIBPATH}/tbb2018_20171205oss/cmake")
find_package(TBB REQUIRED)

link_directories( ${DETECT_DIR}
    ${caffe_DIR}
    ${python_DIR}
    /usr/lib
    /usr/local/lib
    /usr/local/cuda-7.5/lib64
    /storage2/liushuai/work_code/tbb-2018_U2/build/linux_intel64_gcc_cc4.8.5_libc2.17_kernel3.10.0_release )
    
#target_link_libraries(main ${Caffe_LINKER_LIBS})

#FIND_LIBRARY(rfcn_LIBRARY NAMES libcaffe_detect.so PATHS ${DETECT_DIR})
#IF (rfcn_LIBRARY)
#    message(${rfcn_LIBRARY})
#    target_link_libraries(main ${rfcn_LIBRARY})
#ENDIF(rfcn_LIBRARY)


#FIND_LIBRARY(nms_LIBRARY NAMES gpu_nms.so PATHS ${nms_DIR})
#IF (nms_LIBRARY)
 #   message(${nms_LIBRARY})
 #   target_link_libraries(main ${nms_LIBRARY})
#ENDIF(nms_LIBRARY)

#FIND_LIBRARY(caffe_LIBRARY NAMES libcaffe.so PATHS ${caffe_DIR})
#IF (caffe_LIBRARY)
#   message(${caffe_LIBRARY})
#    target_link_libraries(main ${caffe_LIBRARY})
#ENDIF(caffe_LIBRARY)



#set(opencv_DIR /usr/local/lib)
#FIND_LIBRARY(opencv_LIBRARY NAMES libopencv_videoio.so libopencv_video.so libopencv_objdetect.so libopencv_highgui.so libopencv_core.so libopencv_imgcodecs.so libopencv_imgproc.so PATHS ${opencv_DIR})
#IF (opencv_LIBRARY)
#    message(${opencv_LIBRARY})
#    target_link_libraries(main opencv_LIBRARY)
#ENDIF(opencv_LIBRARY)

# find_package( OpenCV REQUIRED )
# if(OpenCV_FOUND)
#    message("Found OpenCV")
#    message("Includes: " ${OpenCV_INCLUDE_DIRS})
# endif(OpenCV_FOUND)
# include_directories(${OpenCV_INCLUDE_DIRS})

#    opencv_videoio
#    opencv_video
#   opencv_objdetect
 #   opencv_highgui 
 #   opencv_core
 #   opencv_imgcodecs
  #  opencv_imgproc
 # target_link_libraries(main 
 #    ${OpenCV_LIBS}
 #    pthread
 #    tbbmalloc_proxy
 #    tbbmalloc
 #    tbb
 #    ) 
target_link_libraries(main 
    pthread
    ${OpenCV_LIBS} ${TBB_IMPORTED_TARGETS}
    )

#target_link_libraries(main "${PROJECT_SOURCE_DIR}/lib/libgpu_nms.so" 
 #   caffe_detect
 #   ${OpenCV_LIBS}
 #   libglog.so
 #   libboost_system.so
 #   libboost_python.so
 #   libglog.so
 #   libpython2.7.so
 #   )
   
 #   libopencv_imgcodecs.so

#target_link_libraries(main libfaster_rcnn.so
#    "${PROJECT_SOURCE_DIR}/../../py-R-FCN-master/caffe/.build_release/lib/libcaffe.so"
#    "${PROJECT_SOURCE_DIR}/../../py-R-FCN-master/lib/nms/gpu_nms.so "
#   /share/apps/local/lib/libopencv_highgui.so 
#    /share/apps/local/lib/libopencv_core.so 
#    /share/apps/local/lib/libopencv_imgproc.so 
#    /share/apps/local/lib/libopencv_imgcodecs.so
#    /share/apps/local/lib/libglog.so
#    /share/apps/local/lib/libboost_system.so
#    /share/apps/local/lib/libboost_python.so
#    /share/apps/local/lib/libglog.so
#    /opt/rh/python27/root/usr/lib64/libpython2.7.so
#    )

