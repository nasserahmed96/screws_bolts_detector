#include <TrainingAndTesting.hpp>


TrainingAndTesting::TrainingAndTesting(){


}


void TrainingAndTesting::trainAndTest(std::string light_pattern_file){
	cv::Ptr<cv::ml::SVM> svm;
	std::vector<float> trainingData;
	std::vector<int> responsesData;
	std::vector<float> testData;
	std::vector<float> testResponsesData;
	int num_for_tests = 20;
	ImageExtractFeatures *features_extractor = new ImageExtractFeatures();
	features_extractor->readFolderAndExtractFeatures(TrainingAndTesting::RINGS_DIR, 0, num_for_tests, trainingData, responsesData, testData, testResponsesData, light_pattern_file);
	features_extractor->readFolderAndExtractFeatures(TrainingAndTesting::NUTS_DIR, 1, num_for_tests, trainingData, responsesData, testData, testResponsesData, light_pattern_file);
	features_extractor->readFolderAndExtractFeatures(TrainingAndTesting::SCREWS_DIR, 2, num_for_tests, trainingData, responsesData, testData, testResponsesData, light_pattern_file);
	std::cout<<"Num of traingin examples: "<<responsesData.size()<<std::endl;
	std::cout<<"Num of testing examples: "<<testResponsesData.size()<<std::endl;
	cv::Mat trainingDataMat(trainingData.size()/2, 2, CV_32FC1, &trainingData[0]);
	cv::Mat responses(responsesData.size(), 1, CV_32SC1, &responsesData[0]);
	cv::Mat testDataMat(testData.size() / 2, 2, CV_32FC1, &testData[0]);
	cv::Mat testResponses(testResponsesData.size(), 1, CV_32FC1, &testResponsesData[0]);
	svm = cv::ml::SVM::create();
	svm->setType(cv::ml::SVM::C_SVC);
	svm->setKernel(cv::ml::SVM::CHI2);
	svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
}
