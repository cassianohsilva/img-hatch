/*
 * main.cpp
 *
 *  Created on: 2 de jan de 2018
 *      Author: cassiano
 */

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.inl.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/videoio.hpp>
#include <cstdio>
#include <iostream>
#include <string>

#include "args.hxx"
#include "hatch.hpp"

int main(int argc, char **argv) {

	std::string in;
	std::string out;

	{
		args::ArgumentParser parser("A simple program that hatch a video from a file or a camera.");

		args::HelpFlag help(parser, "help", "Display this help menu", { 'h',
				"help" });

		args::ValueFlag<std::string> input(parser, "input",
				"Input filename to be hatched (if empty, the default camera will be used)", { 'i', "input" });

		args::Positional<std::string> output(parser, "output",
				"Output filename", args::Options::Required);

		try {
			parser.ParseCLI(argc, argv);

			if (input) {
				in = args::get(input);
			}

			if (output) {
				out = args::get(output);
			}

		} catch (const args::Completion& e) {
			std::cout << e.what();

			return 0;
		} catch (const args::RequiredError& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << parser;

			return 0;
		} catch (const args::Help&) {
			std::cout << parser;

			return 0;
		} catch (const args::ParseError& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << parser;

			return 1;
		}
	}

	cv::VideoCapture capture;
	cv::VideoWriter writer;

	if (in.empty()) {

		cv::namedWindow("Capture", 1);

//		capture = new cv::VideoCapture();
	} else {
		capture.open(in);
	}

	if (!capture.isOpened()) {

		if (in.empty()) {
			std::printf("Cannot load default video capture.\n");
		} else {
			std::printf("Cannot load input file.\n");
		}

		return 1;
	}

	int frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);
	int frameRate = capture.get(CV_CAP_PROP_FPS);

	if (!frameRate) {
		frameRate = 24;
	}

	writer.open(out, CV_FOURCC('X', '2', '6', '4'), frameRate,
			cv::Size(frameWidth, frameHeight));

	cv::Mat frame;
	cv::Mat aux = cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3);

	int progressCount = 0;
	int progress = -1;

	while (capture.read(frame)) {

		hatch(frame, aux);

		if (frameCount) {
			if (progress < (progressCount * 100) / frameCount) {

				progress = (progressCount * 100) / frameCount;

				std::printf("\rProgress:\t%d %%",
						(progressCount * 100) / frameCount);

				std::fflush(stdout);
			}

			++progressCount;

			imshow("Capture", aux);
		}

		writer.write(aux);
	}

	if (frameCount) {
		std::printf("\rProgress:\t100 %%\n");
	}

	capture.release();
	writer.release();
}
