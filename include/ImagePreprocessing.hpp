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
		explicit ImagePreprocessing(std::string &light_pattern_file_path, cv::Mat img);
		cv::Mat removeImageNoise(std::string algo="blur");
		cv::Mat getThresholdedImage(cv::Mat img_no_light, int light_method);
		cv::Mat getBackgroundSubstractor(std::string background_sub_algo="MOG2");
		cv::Mat removeLight(cv::Mat img_noise, int method);
		cv::Mat calculateLightPattern();
		cv::Mat preprocessImage();
	private:
		cv::Mat m_light_pattern;
		cv::Mat m_img;
		std::string m_remove_noise_algorithm;
		double m_threshold_value;
		double m_threshold_max_value;
		int m_threshold_method;
		int m_light_method;
};

#endif
