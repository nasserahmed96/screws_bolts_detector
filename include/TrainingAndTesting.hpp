#ifndef TRAININGANDTESTING
#define TRAININGANDTESTING


#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>

#include <ImageExtractFeatures.hpp>


class TrainingAndTesting{
	public:
		TrainingAndTesting();
		void trainAndTest(std::string light_pattern_file);
		
		inline static const std::string DATASET_ROOT_DIR = "../Dataset/dataset_white_background/data/";
		inline static const std::string NUTS_DIR = DATASET_ROOT_DIR +  "nut/tuerca_%04d.pgm";
		inline static const std::string RINGS_DIR = DATASET_ROOT_DIR + "ring/arandela_%04d.pgm";
		inline static const std::string SCREWS_DIR = DATASET_ROOT_DIR + "screw/tornillo_%04d.pgm";		
};
#endif
