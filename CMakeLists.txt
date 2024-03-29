################################################################################
# File generated by HDevelop Version 18.11
#
# Do not modify!
################################################################################

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(lTools CXX)
set(CMAKE_CXX_FLAGS "-fPIC")

# ===================================================================================================
# ===================================================================================================
# Source and header files
# ===================================================================================================
# ===================================================================================================

# ==================================================
#                  Source files
# ==================================================

FILE (GLOB LTOOLS_SRC "./lTools/*.cpp"  "./lTools/*.c" )
set(SOURCE ${LTOOLS_SRC})

# ==================================================
#                  Header files
# ==================================================
FILE (GLOB LTOOLS_H "./lTools/*.hpp"  "./lTools/*.h" )
set(HEADER ${LTOOLS_H})


#set(SOURCE_INC ${CMAKE_CURRENT_SOURCE_DIR}/include )
#set (INC_DIRS ${INC_DIRS} ${SOURCE_INC})

# ===================================================================================================
# ===================================================================================================
# Dependencies
# ===================================================================================================
# ===================================================================================================


# ==================================================
#  OpenCV
# ==================================================
option (USE_OCV "USE_OCV " OFF)
IF(USE_OCV)
add_definitions("-DUSE_OCV")
message("-DUSE_OCV")


set(OPENCV_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../autofanyiji_linux/camera-calibration-and-registration/public/halcon/thirdparty/opencv-4.2.0/install)
set(OPENCV_INC ${OPENCV_PATH}/include/opencv4/opencv2
                                    ${OPENCV_PATH}/include/opencv4)
message(${OPENCV_INC})
set(OPENCV_LIB ${OPENCV_PATH}/lib/libopencv_highgui.so
                                    ${OPENCV_PATH}/lib/libopencv_core.so
                                    ${OPENCV_PATH}/lib/libopencv_calib3d.so
                                    ${OPENCV_PATH}/lib/libopencv_imgproc.so
                                    ${OPENCV_PATH}/lib/libopencv_imgcodecs.so              
                                    ${OPENCV_PATH}/lib/libopencv_calib3d.so        
                                    ${OPENCV_PATH}/lib/libopencv_features2d.so   
                                    ${OPENCV_PATH}/lib/libopencv_video.so   
                                    ${OPENCV_PATH}/lib/libopencv_videoio.so   
                                    ${OPENCV_PATH}/lib/libopencv_videostab.so    
                                    )
set (INC_DIRS ${INC_DIRS} ${OPENCV_INC})
set (LIBS ${LIBS} ${OPENCV_LIB})



endif(USE_OCV)









# ===================================================================================================
# ===================================================================================================
# Output
# ===================================================================================================
# ===================================================================================================


if(${UNIX})
    set (LIBS ${LIBS} pthread)
endif()
add_library(${PROJECT_NAME} SHARED ${SOURCE} ${HEADER})

set (INC_DIRS ${INC_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

add_executable(testRun test.cpp )
target_include_directories(testRun PUBLIC ${INC_DIRS})
target_link_libraries(testRun PUBLIC ${LIBS})
target_link_libraries(testRun PUBLIC ${PROJECT_NAME})
set_property(TARGET testRun PROPERTY CXX_STANDARD 11)





