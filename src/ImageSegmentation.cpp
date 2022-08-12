#include<ImageSegmentation.hpp>



void ImageSegmentation::connectedComponents(cv::Mat img, bool show_stats){
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


void ImageSegmentation::findAndDrawingContours(cv::Mat img){

	/*The main goal of this function is to find contours in `img` and show them, it's not used in the pipline as we will use the OpenCV built in function
	 * for simplicity
	 *
	 *
	 */
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


cv::Scalar ImageSegmentation::randomColor(cv::RNG &rng){
	int icolor = (unsigned) rng;
	return cv::Scalar(icolor &255, (icolor>>8)&255, (icolor>>16)&255);
}
