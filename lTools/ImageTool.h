#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "LogTool.h"

enum
{
    V_PROJECT = 1,
    H_PROJECT = 2
};

#ifdef USE_OCV
#include <opencv2/opencv.hpp>

int GetTextProject(cv::Mat src,std::vector<float> &feature, int mode);

int GetTextProject(cv::Mat src, cv::Mat mask, std::vector<float> &pos, int mode);

std::vector<float> createOneHanningVec(int size);

cv::Mat createHanningMats(int size);

cv::Mat drawMatchImage(cv::Mat src1, cv::Point p1, cv::Mat src2, cv::Point p2);

int drawRotateRect(cv::Mat image,cv::RotatedRect rotateRect,cv::Scalar color);

int drawRotateRectLine(cv::Mat image,cv::RotatedRect rotateRect,cv::Scalar color,int lineType=8);

void BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat &dst, float clipHistPercent);

void BrightnessAndContrastAuto(const cv::Mat &src, cv::Mat &dst,float clipHistPercent, cv::Vec2d& lastGray);

int sobelcv(cv::Mat& inoutMat);
#endif