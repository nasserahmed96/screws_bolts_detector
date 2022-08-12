#ifndef IMAGEPREPROCESSING
#define IMAGEPREPROCESSING

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>



class ImagePreprocessing{
	public:
		explicit ImagePreprocessing(std::string &light_pattern_file_path);
		cv::Mat removeImageNoise(cv::Mat img, std::string algo="blur");
		cv::Mat getThresholdedImage(cv::Mat img, int light_method);
		cv::Mat getBackgroundSubstractor(cv::Mat img,std::string background_sub_algo="MOG2");
		cv::Mat removeLight(cv::Mat img, int method);
		cv::Mat calculateLightPattern(cv::Mat img);
		cv::Mat preprocessImage(cv::Mat input);
	private:
		cv::Mat light_pattern;
};

#endif
