#include "ImagePreprocessing.hpp"

ImagePreprocessing::ImagePreprocessing(std::string &light_pattern_file_path) {
	this->light_pattern = cv::imread(light_pattern_file_path, 0);
}


cv::Mat ImagePreprocessing::getThresholdedImage(cv::Mat img, int light_method){
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
cv::Mat ImagePreprocessing::removeLight(cv::Mat img, int method){
	cv::Mat aux;	
	if(method == 1){
		cv::Mat img32, pattern32;
		img.convertTo(img32, CV_32F);	
		this->light_pattern.convertTo(pattern32, CV_32F);	
		aux = 1 - (img32/pattern32);	
		aux = aux*255;
		aux.convertTo(aux, CV_8U);
	}
	else {
		aux = this->light_pattern - img;
	}
		return aux;
}

cv::Mat ImagePreprocessing::calculateLightPattern(cv::Mat img){
	cv::Mat pattern;
	cv::blur(img, pattern, cv::Size(img.cols/3, img.rows/3));
	return pattern;
}

cv::Mat ImagePreprocessing::removeImageNoise(cv::Mat img, std::string algo){
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
cv::Mat ImagePreprocessing::getBackgroundSubstractor(cv::Mat img, std::string background_sub_algo){
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

cv::Mat ImagePreprocessing::preprocessImage(cv::Mat input){
	cv::Mat result;
	cv::Mat img_noise, img_box_smooth;
	img_noise = this->removeImageNoise(input);
	cv::Mat img_no_light;
	img_noise.copyTo(img_no_light);
	img_no_light = removeLight(img_noise, 1);	
	result = this->getThresholdedImage(img_no_light, 1);
	return result;
}
