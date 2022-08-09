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

#ifndef MIW_H
#define MIW_H

#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class MultipleImageWindow{
	public:
		MultipleImageWindow(std::string window_title, int cols, int rows, int flags);
		int addImage(std::string title, cv::Mat img, bool render=false);
		void removeImage(int pos);
		void render();
	private:
		int cols;
		int rows;
		int canvas_width;
		int canvas_height;
		std::string window_title;
		std::vector<std::string> titles;
		std::vector<cv::Mat> images;
		cv::Mat canvas;
};

#endif

