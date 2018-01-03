/**
 * @function calcHist_Demo.cpp
 * @brief Demo code to use the function calcHist
 * @author
 */

#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.inl.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc.hpp>
#include <cstdlib>

#include "hatch.hpp"

void hatch(const cv::Mat& input, cv::Mat& output) {

	cv::Mat temp;

	cv::cvtColor(input, temp, CV_RGB2HLS);

	for (int y = 0; y < temp.rows; ++y) {
		for (int x = 0; x < temp.cols; ++x) {
			cv::Vec3b p = temp.at<cv::Vec3b>(cv::Point(x, y));

			cv::Vec3b r;

			if ((p.val[1] < 0.15 * 255) && (div(x - y - 10, 10).rem == 0)) {

				r = cv::Vec3b::all(0);

			} else if ((p.val[1] < 0.25 * 255)
					&& (div(x + y - 10, 10).rem == 0)) {

				r = cv::Vec3b::all(0);

			} else if ((p.val[1] < 0.5 * 255)
					&& (div(x - y - 5, 10).rem == 0)) {

				r = cv::Vec3b::all(0);

			} else if ((p.val[1] < 0.65 * 255)
					&& (div(x + y - 5, 10).rem == 0)) {

				r = cv::Vec3b::all(0);

			} else if ((p.val[1] < 0.75 * 255) && (div(x - y, 10).rem == 0)) {

				r = cv::Vec3b::all(0);

			} else if ((p.val[1] < 0.85 * 255) && (div(x + y, 10).rem == 0)) {

				r = cv::Vec3b::all(0);

			} else {

				r = cv::Vec3b::all(0xFF);
			}

			output.at<cv::Vec3b>(cv::Point(x, y)) = r;
		}
	}
}
