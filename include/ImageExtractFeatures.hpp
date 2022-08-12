#ifndef IMAGEEXTRACTFEATURES
#define IMAGEEXTRACTFEATURES

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <MultipleImageWindow.h>
#include <ImagePreprocessing.hpp>


class ImageExtractFeatures{
	public:
		ImageExtractFeatures();
		std::vector<std::vector<float>> extractFeatures(cv::Mat img, std::vector<int> *left=NULL, std::vector<int> *top=NULL);
		bool readFolderAndExtractFeatures(std::string folder, int label, int num_for_tests, std::vector<float> &trainingData, 
				std::vector<int> &responsesData, std::vector<float> &testingData, std::vector<float> &testingResponsesData, std::string light_pattern_file);

	private:
		MultipleImageWindow *miw;
};

#endif
