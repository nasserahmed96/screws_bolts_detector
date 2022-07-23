#include <iostream>
#include <string>
#include <sstream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


const char* keys = {
	"{help h usage ? | | print this message}"
		"{@image || image to process}"
		"{@lightPattern || Image light pattern to apply to image input}"
		"{lightMethod | 1 | Method to remove background light, 0 difference, 1 div}"
		"{segMethod | 1 | Method to segment: 1 connected Components, 2 connected components with stats, 3 find Contours}"
		"{algo | MOG2 | Background substraction method (KNN, MOG2) }"
};

cv::Mat removeLight(cv::Mat img, cv::Mat pattern, int method);
cv::Mat calculateLightPattern(cv::Mat img);
void connectedComponents(cv::Mat img);
void connectedComponentsStats(cv::Mat img);
void findContoursBasic(cv::Mat img);
static cv::Scalar randomColor(cv::RNG &rng);
cv::Mat removeImageNoise(cv::Mat img, std::string algo="blur");
cv::Mat getThresholdedImage(cv::Mat img, int light_method);
cv::Mat getBackgroundSubstractor(cv::Mat img,std::string background_sub_algo="MOG2");
int main(int argc, const char **argv){
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Nasser implementation for object classification");
	if(parser.has("help")){
		parser.printMessage();
		return 0;
	}
	cv::String img_file  = parser.get<cv::String>(0);
	cv::String light_pattern_file = parser.get<cv::String>(1);
	int method_light = parser.get<int>("lightMethod");
	int method_seg = parser.get<int>("segMethod");
	cv::String background_sub_algo = parser.get<cv::String>("algo");
	
	if(!parser.check()){
		parser.printErrors();
		return 0;
	}
	cv::Mat img = cv::imread(img_file, 0);
	cv::Mat light_pattern = cv::imread(light_pattern_file, 0);
	if (light_pattern.data == NULL)
	{
		light_pattern = calculateLightPattern(img);
	}	
	if(img.data == NULL){
		std::cout<<"Error loading image "<<img_file<<std::endl;
		return -1;
	}
	cv::Mat img_no_noise = removeImageNoise(img);
	cv::Mat light_no_noise = removeImageNoise(light_pattern);
	cv::Mat img_no_light = removeLight(img_no_noise, light_no_noise, method_light);
	cv::Mat img_thr = getThresholdedImage(img_no_light, method_light);	
			
	connectedComponentsStats(img_thr);
	findContoursBasic(img_thr);
	cv::imshow("Original image", img);
	//cv::imshow("Image mask", img_mask);
	cv::imshow("Gassuain blur", img_no_noise);
	//cv::imshow("Light pattern", light_pattern);
	cv::imshow("Image no light", img_no_light);
	//cv::imshow("Created pattern", created_pattern);
	cv::imshow("Image threshold", img_thr);
	cv::waitKey(0);
	return 0;
}

cv::Mat getThresholdedImage(cv::Mat img, int light_method){
	switch(light_method){
		case 1:
			cv::threshold(img, img, 40, 255, cv::THRESH_BINARY);
			break;
		case 2:
			cv::threshold(img, img, 140, 255, cv::THRESH_BINARY_INV);
			break;
		default:
			img = img;
	}
	return img;

}
cv::Mat removeLight(cv::Mat img, cv::Mat pattern, int method){
	cv::Mat aux;	
	if(method == 1){
		cv::Mat img32, pattern32;
		img.convertTo(img32, CV_32F);
		pattern.convertTo(pattern32, CV_32F);
		aux = 1 - (img32/pattern32);
		aux = aux*255;
		aux.convertTo(aux, CV_8U);
	}
	else {
		aux = pattern - img;
	}
	return aux;
}

cv::Mat calculateLightPattern(cv::Mat img){
	cv::Mat pattern;
	cv::blur(img, pattern, cv::Size(img.cols/3, img.rows/3));
	return pattern;
}

void connectedComponents(cv::Mat img){
	cv::Mat labels;
	int num_objects = cv::connectedComponents(img, labels);
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
	}
	cv::imshow("Result", output);
	cv::waitKey(0);
}

void connectedComponentsStats(cv::Mat img){
	cv::Mat labels, stats, centroids;
	int num_objects = cv::connectedComponentsWithStats(img, labels, stats, centroids);
	if(num_objects < 2){
		std::cout<<"No objects detected"<<std::endl;
		return;
	}
	else{
		std::cout<<"Number of objects detected: "<<num_objects - 1<<std::endl;
	}
	cv::Mat output = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);
	cv::RNG rng(0xFFFFFFFF);
	for(int i = 1;i<num_objects;i++){
		std::cout<<"Object: "<<i << "With pos: "<<centroids.at<cv::Point2d>(i)<<" with area "<<stats.at<int>(i, cv::CC_STAT_AREA) <<std::endl;
		cv::Mat mask = labels == i;
		output.setTo(randomColor(rng), mask);
		std::stringstream ss;
		ss << "area: "<<stats.at<int>(i, cv::CC_STAT_AREA);
		putText(output,
				ss.str(),
				centroids.at<cv::Point2d>(i),
				cv::FONT_HERSHEY_SIMPLEX, 
				0.4,
				cv::Scalar(255, 255, 255));
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

cv::Mat removeImageNoise(cv::Mat img, std::string algo){
	if (algo == "blur"){
		cv::medianBlur(img, img, 3);
		cv::blur(img, img, cv::Size(3, 3));
	}
	else if (algo == "gaussian"){
		int sigma = 3;
		int ksize = 5;
		cv::GaussianBlur(img, img, cv::Size(ksize, ksize), sigma, sigma);
	}
	return img;
}
cv::Mat getBackgroundSubstractor(cv::Mat img, std::string background_sub_algo){
	cv::Ptr<cv::BackgroundSubtractor> pBackSub;
	if(background_sub_algo == "MOG2"){
		pBackSub = cv::createBackgroundSubtractorMOG2();
	}
	else{
		pBackSub = cv::createBackgroundSubtractorKNN();
	}
	cv::Mat img_mask;	
	pBackSub->apply(img, img_mask);	
	return img_mask;

}
