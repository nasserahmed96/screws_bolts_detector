#ifndef IMGAESEGMENTATION
#define IMAGESEGMENTATION

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class ImageSegmentation{
	void connectedComponents(cv::Mat img, bool show_stats=true);
	void findAndDrawingContours(cv::Mat img);
	cv::Scalar randomColor(cv::RNG &rng);
};

#endif
