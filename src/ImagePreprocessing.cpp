#include "ImagePreprocessing.hpp"

ImagePreprocessing::ImagePreprocessing(std::string &light_pattern_file_path, cv::Mat img): m_img{img} {
	if (light_pattern_file_path == ""){
		this->m_light_pattern = this->calculateLightPattern();
	}
	else{
		this->m_light_pattern = cv::imread(light_pattern_file_path, 0);
	}
}


cv::Mat ImagePreprocessing::getThresholdedImage(cv::Mat img_no_light, int light_method){
	switch(light_method){
		case 1:
			cv::threshold(img_no_light, img_no_light, 40, 255, cv::THRESH_BINARY);
			break;
		case 2:
			cv::threshold(img_no_light, img_no_light, 140, 255, cv::THRESH_BINARY_INV);
			break;
		default:
			img_no_light = img_no_light;
	}
	return img_no_light;

}
cv::Mat ImagePreprocessing::removeLight(cv::Mat img_noise, int method){
	cv::Mat aux;	
	if(method == 1){
		cv::Mat img32, pattern32;
		img_noise.convertTo(img32, CV_32F);	
		this->m_light_pattern.convertTo(pattern32, CV_32F);	
		aux = 1 - (img32/pattern32);	
		aux = aux*255;
		aux.convertTo(aux, CV_8U);
	}
	else {
		aux = this->m_light_pattern - img_noise;
	}
		return aux;
}

cv::Mat ImagePreprocessing::calculateLightPattern(){
	cv::Mat pattern;
	cv::blur(m_img, pattern, cv::Size(m_img.cols/3, m_img.rows/3));
	return pattern;
}

cv::Mat ImagePreprocessing::removeImageNoise(std::string algo){
	if (algo == "blur"){
		cv::medianBlur(m_img, m_img, 3);
		cv::blur(m_img, m_img, cv::Size(3, 3));
	}
	else if (algo == "gaussian"){
		int sigma = 3;
		int ksize = 5;
		cv::GaussianBlur(m_img, m_img, cv::Size(ksize, ksize), sigma, sigma);
	}
	return m_img;
}
cv::Mat ImagePreprocessing::getBackgroundSubstractor(std::string background_sub_algo){
	cv::Ptr<cv::BackgroundSubtractor> pBackSub;
	if(background_sub_algo == "MOG2"){
		pBackSub = cv::createBackgroundSubtractorMOG2();
	}
	else{
		pBackSub = cv::createBackgroundSubtractorKNN();
	}
	cv::Mat img_mask;	
	pBackSub->apply(m_img, img_mask);	
	return img_mask;

}

cv::Mat ImagePreprocessing::preprocessImage(){
	cv::Mat result;
	cv::Mat img_noise, img_box_smooth;
	img_noise = this->removeImageNoise("gaussian");
	cv::Mat img_no_light;
	img_noise.copyTo(img_no_light);
	img_no_light = removeLight(img_noise, 1);	
	result = this->getThresholdedImage(img_no_light, 1);
	return result;
}
