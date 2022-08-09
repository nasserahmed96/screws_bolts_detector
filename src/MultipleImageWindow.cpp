/**
 * Mutliple Image Window
 *
 * This class create a window with multiple images showed on it
 * in a grid with optional titles each one
 *
 * @author: David Millan Escriva
 * @email: david.millan@damiles.com
 *
 */


#include <MultipleImageWindow.h>

MultipleImageWindow::MultipleImageWindow(std::string window_title, int cols, int rows, int flags){
	this->window_title = window_title;
	this->cols = cols;
	this->rows = rows;
	cv::namedWindow(window_title, flags);
	cv::moveWindow(window_title, 0, 0);
	// ToDo: detect resolution of desktop and show fullresolution canvas
	this->canvas_width = 1200;
	this->canvas_height = 700;
	this->canvas = cv::Mat(this->canvas_height, this->canvas_width, CV_8UC3);
	cv::imshow(this->window_title, this->canvas);
}

int MultipleImageWindow::addImage(std::string title, cv::Mat img, bool render){
	int index = -1;
	for(int i=0; i < this->titles.size();i++){
		std::string t = this->titles[i];
		if(t.compare(title) == 0){
			index=i;
			break;
		}
	}
	if(index == -1){
		this->titles.push_back(title);
		this->images.push_back(img);
	}
	else{
		this->images[index] = img;
	}
	if(render){
		this->render();
	}
	return this->images.size()-1;
}

void MultipleImageWindow::removeImage(int pos){
	this->titles.erase(this->titles.begin() + pos);
	this->images.erase(this->images.begin() + pos);
}

void MultipleImageWindow::render(){
	this->canvas.setTo(cv::Scalar(20, 20, 20));
	std::cout<<"Images size: "<<this->images.size()<<std::endl;
	int cell_width = (this->canvas_width/this->cols);
	int cell_height = (this->canvas_height/this->rows);
	int max_images = (this->images.size()>cols*rows)?cols*rows:this->images.size();
	int i=0;
	std::vector<std::string>::iterator titles_it = this->titles.begin();
	for(std::vector<cv::Mat>::iterator it=this->images.begin(); it !=this->images.end(); ++it){
		std::string title = *titles_it;
		int cell_x = (cell_width) * ((i) % this->cols);
		int cell_y = (cell_height) * floor((i) / (float)this->cols);
		
		
		cv::Rect mask(cell_x, cell_y, cell_width, cell_height);
		cv::Mat cell(this->canvas, mask);
		cv::Mat resized;
		double cell_aspect = (double)cell_width/(double)cell_height;
		cv::Mat img = *it;
		double img_aspect = (double)img.cols/(double)img.rows;
		double f = (cell_aspect<img_aspect)?(double)cell_width/(double)img.cols: (double)cell_height/(double)img.rows;
		cv::resize(img, resized, cv::Size(0, 0), f, f);
		if(resized.channels() == 1){
			cv::cvtColor(resized, resized, cv::COLOR_GRAY2BGR);
		}
		cv::Mat sub_cell(this->canvas, cv::Rect(cell_x + ((cell_width - resized.cols)/2), cell_y + ((cell_height - resized.rows) / 2), resized.cols, resized.rows));
		resized.copyTo(sub_cell);
		cv::putText(cell, title.c_str(), cv::Point(20, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(200, 0, 0), 1, cv::LINE_AA);
		cv::rectangle(canvas, cv::Rect(cell_x, cell_y, cell_width, cell_height), cv::Scalar(200, 200, 200), 1);
		i++;
		++titles_it;
		if(i == max_images){
			break;
		}

	}
	imshow(this->window_title, this->canvas);
}
