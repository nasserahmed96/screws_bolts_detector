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

MultipleImageWindow *miw;
const std::string DATASET_ROOT_DIR = "../Dataset/dataset_white_background/data/";
const std::string NUTS_DIR = DATASET_ROOT_DIR +  "nut/tuerca_%04d.pgm";
const std::string RINGS_DIR = DATASET_ROOT_DIR + "ring/arandela_%04d.pgm";
const std::string SCREWS_DIR = DATASET_ROOT_DIR + "screw/tornillo_%04d.pgm";

cv::Ptr<cv::ml::SVM> svm;

const char* keys = {
	"{help h usage ? | | print this message}"
		"{@image || image to process}"
		"{@lightPattern || Image light pattern to apply to image input}"
		"{lightMethod | 1 | Method to remove background light, 0 difference, 1 div}"
		"{segMethod | 1 | Method to segment: 1 connected Components, 2 connected components with stats, 3 find Contours}"
		"{algo | MOG2 | Background substraction method (KNN, MOG2) }"
};

std::string light_pattern_file;


void connectedComponents(cv::Mat img, bool show_stats=true);

void findContoursBasic(cv::Mat img);
static cv::Scalar randomColor(cv::RNG &rng);
std::vector<std::vector<float>> ExtractFeatures(cv::Mat img, std::vector<int> *left=NULL, std::vector<int> *top=NULL);
bool readFolderAndExtractFeatures(std::string folder, int label, int num_for_test, std::vector<float> &training_data, 
		std::vector<int> &responses_data, std::vector<float> &testing_data, std::vector<int> &testResponesData);
void trainAndTest();



int main(int argc, const char **argv){
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Nasser implementation for object classification");
	if(parser.has("help")){
		parser.printMessage();
		return 0;
	}
	miw = new MultipleImageWindow("MainWindow", 2, 2, cv::WINDOW_AUTOSIZE);
	cv::String img_file  = parser.get<cv::String>(0);
	light_pattern_file = parser.get<cv::String>(1);
	int method_light = parser.get<int>("lightMethod");
	int method_seg = parser.get<int>("segMethod");
	cv::String background_sub_algo = parser.get<cv::String>("algo");
	
	if(!parser.check()){
		parser.printErrors();
		return 0;
	}
	cv::Mat img = cv::imread(img_file, 0);
	
	
	if(img.data == NULL){
		std::cout<<"Error loading image "<<img_file<<std::endl;
		return -1;
	}			
	//connectedComponents(img_thr);
	//findContoursBasic(img_thr);	
	
	trainAndTest();
	return 0;
}

void connectedComponents(cv::Mat img, bool show_stats){
	cv::Mat labels, stats, centroids;
	int num_objects = (show_stats) ? cv::connectedComponentsWithStats(img, labels, stats, centroids): cv::connectedComponents(img, labels);
	if(num_objects < 2){
		std::cout<<"No objects detected"<<std::endl;
		return;
	}
	else{
		std::cout<<"Number of objects detected: "<<num_objects - 1<<std::endl;
	}
	cv::Mat output = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);
	cv::RNG rng(0xFFFFFFFF);
	for(int i=1; i<num_objects;i++){
		cv::Mat mask = labels == i;
		output.setTo(randomColor(rng), mask);
		if(show_stats){
			std::stringstream ss;
			ss << "area: "<<stats.at<int>(i, cv::CC_STAT_AREA);
			putText(output, ss.str(), centroids.at<cv::Point2d>(i), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 255, 255));
		}
	}
	cv::imshow("Result", output);
	cv::waitKey(0);
}

void findContoursBasic(cv::Mat img){
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	cv::Mat output = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);
	if(contours.size() == 0){
		std::cout<<"No objects detected"<<std::endl;
		return;
	}
	else{
		std::cout<<"Number of objects detected: "<<contours.size() <<std::endl;
	}
	cv::RNG rng(0xFFFFFFFF);
	for(int i = 0;i < contours.size(); i++){
		cv::drawContours(output, contours, i, randomColor(rng));
	}
	cv::imshow("Contours", output);
	cv::waitKey(0);
}


cv::Scalar randomColor(cv::RNG &rng){
	int icolor = (unsigned) rng;
	return cv::Scalar(icolor &255, (icolor>>8)&255, (icolor>>16)&255);
}


std::vector<std::vector<float>> ExtractFeatures(cv::Mat img, std::vector<int> *left, std::vector<int> *top){
	std::vector<std::vector<float>> output;
	std::vector<std::vector<cv::Point>> contours;
	cv::Mat input = img.clone();
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(input, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	if(contours.size() == 0){
		return output;
	}
	cv::RNG rng(0xFFFFFFFF);
	for(int i = 0;i < contours.size(); i++){
		cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
		cv::drawContours(mask, contours, i, cv::Scalar(1), cv::FILLED, cv::LINE_8, hierarchy, 1);
		cv::Scalar area_s = cv::sum(mask);
		float area  = area_s[0];	
		if(area>500) {
			cv::RotatedRect r = cv::minAreaRect(contours[i]);
			float width = r.size.width;
			float height = r.size.height;
			float ar = (width<height) ? height / width:width / height;
			std::vector<float> row;
			row.push_back(area);
			row.push_back(ar);
			output.push_back(row);
			if(left != NULL){
				left->push_back((int) r.center.x);
			}
			if(top != NULL){
				top->push_back((int) r.center.y);
			}
			
			miw->addImage("Extract features", mask*255);
			miw->render();
			cv::waitKey(10);
			
		}
	}

		return output;
}


bool readFolderAndExtractFeatures(std::string folder, int label, int num_for_tests, std::vector<float> &trainingData, 
		std::vector<int> &responsesData, std::vector<float> &testingData, std::vector<float> &testingResponsesData){
	cv::VideoCapture images;
	std::cout<<"Start reading "<<folder<<std::endl;
	std::cout<<"Num for tests: "<<num_for_tests<<std::endl;
	if(images.open(folder) == false){
		std::cout<<"Can not open the folder images"<<std::endl;
		return false;
	}
	ImagePreprocessing *image_preprocessor = new ImagePreprocessing(light_pattern_file);
	
	cv::Mat frame;
	int img_index = 0;
	while(images.read(frame)){
		cv::imshow("Original image", frame);
		cv::waitKey(10);
		cv::Mat pre = image_preprocessor->preprocessImage(frame);
		std::vector<std::vector<float>> features = ExtractFeatures(pre);
		for(int i = 0;i < features.size(); i++){
			std::cout<<"Image index: "<<img_index<<std::endl;
			if(img_index >= num_for_tests){
				trainingData.push_back(features[i][0]);
				trainingData.push_back(features[i][1]);
				responsesData.push_back(label);
			}
			else {
				testingData.push_back(features[i][0]);
				testingData.push_back(features[i][1]);
				testingResponsesData.push_back((float) label);
			}
		}
		img_index++;

	}
	return true;
}

void trainAndTest(){
	std::vector<float> trainingData;
	std::vector<int> responsesData;
	std::vector<float> testData;
	std::vector<float> testResponsesData;
	int num_for_tests = 20;
	readFolderAndExtractFeatures(RINGS_DIR, 0, num_for_tests, trainingData, responsesData, testData, testResponsesData);
	readFolderAndExtractFeatures(NUTS_DIR, 1, num_for_tests, trainingData, responsesData, testData, testResponsesData);
	readFolderAndExtractFeatures(SCREWS_DIR, 2, num_for_tests, trainingData, responsesData, testData, testResponsesData);
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
