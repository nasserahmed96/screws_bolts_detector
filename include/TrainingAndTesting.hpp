#ifndef TRAININGANDTESTING
#define TRAININGANDTESTING


#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <MultipleImageWindow.h>
#include <ImageExtractFeatures.hpp>
#include <ImagePreprocessing.hpp>


class TrainingAndTesting{
	public:
		TrainingAndTesting();
		cv::Ptr<cv::ml::SVM> trainAndTest(std::string light_pattern_file);
		void predict(cv::Mat img, std::string light_pattern_file, cv::Ptr<cv::ml::SVM> svm);
		inline static const std::string DATASET_ROOT_DIR = "../Dataset/dataset_white_background/data/";
		inline static const std::string NUTS_DIR = DATASET_ROOT_DIR +  "nut/tuerca_%04d.pgm";
		inline static const std::string RINGS_DIR = DATASET_ROOT_DIR + "ring/arandela_%04d.pgm";
		inline static const std::string SCREWS_DIR = DATASET_ROOT_DIR + "screw/tornillo_%04d.pgm";		
	private:
		MultipleImageWindow *miw;
};
#endif
