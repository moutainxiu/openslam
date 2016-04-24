/*************************************************************************
 * �ļ����� initial_position
 *
 * ���ߣ� ���
 * �ʼ��� fengbing123@gmail.com
 * ʱ�䣺 2015/8/7
 *
 * ˵���� �����ʼλ��
 *************************************************************************/
#include <string>
#include <opencv2/opencv.hpp>
#include <openslam/utils/cmd_line.h>
#include <openslam/utils/timer.h>
#include <openslam/slam/pinhole_camera.h>
#include <openslam/slam/initializer.h>
#include <openslam/slam/feature.h>

using namespace openslam::slam;
using namespace openslam::utils;

int main(int argc, char *argv[])
{
	CmdLine cmd;
	std::string first_frame_name;
	std::string second_frame_name;

	cmd.add(make_option('f', first_frame_name, "firstname"));
	cmd.add(make_option('s', second_frame_name, "secondname"));
	try {
		if (argc == 1) throw std::string("Invalid command line parameter.");
		cmd.process(argc, argv);
	}
	catch (const std::string& s) {
		std::cerr << "Feature detector \nUsage: " << argv[0] << "\n"
			<< "[-f|--firstname name]\n"
			<< "[-s|--secondname name]\n"
			<< std::endl;

		std::cerr << s << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat first_img(cv::imread(first_frame_name, 0));
	cv::Mat second_img(cv::imread(second_frame_name, 0));
	assert(first_img.type() == CV_8UC1 && !first_img.empty());
	assert(second_img.type() == CV_8UC1 && !second_img.empty());

	PinholeCamera* cam = new PinholeCamera(752, 480, 315.5, 315.5, 376.0, 240.0);
	ORBextractor *extractor = new ORBextractor(2*1000);

	FramePtr fisrt_frame(new Frame(cam, first_img, 0.0, extractor));
	FramePtr second_frame(new Frame(cam, second_img, 1.0, extractor));
	
	Initializer init;
	init.addFirstFrame(fisrt_frame);
	init.addSecondFrame(second_frame);
	std::cout << second_frame->T_f_w_ << std::endl;

	return 0;
}