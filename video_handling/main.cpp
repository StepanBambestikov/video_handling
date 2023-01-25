#include "color_distance_counter.h"
#include "edge_provider_4connected.h"
#include "graph_based_parameter_segmentation.h"
#include "graph_based_frame_segmenter.h"
#include "input_video.h"
#include "output_video.h"
#include "pixel_border_highlighter.h"
#include "pixel_painter.h"
#include "video_handler.h"

#include <chrono>

#include "thread_video_handler.h"

template <typename Clock = std::chrono::high_resolution_clock>
class stopwatch
{
    const typename Clock::time_point start_point;
public:
    stopwatch() :
        start_point(Clock::now())
    {}

    template <typename Rep = typename Clock::duration::rep, typename Units = typename Clock::duration>
    Rep elapsed_time() const
    {
        std::atomic_thread_fence(std::memory_order_relaxed);
        auto counted_time = std::chrono::duration_cast<Units>(Clock::now() - start_point).count();
        std::atomic_thread_fence(std::memory_order_relaxed);
        return static_cast<Rep>(counted_time);
    }
};

using precise_stopwatch = stopwatch<>;
using system_stopwatch = stopwatch<std::chrono::system_clock>;
using monotonic_stopwatch = stopwatch<std::chrono::steady_clock>;



//video handling
int main(){

	graph_based_parameter_segmentation TEST_MERGE_CONSTANT = { 10000 };
	size_t MIN_SEGMENT_SIZE = { 1000 };

	/*input_video input{ "input.mp4" };
	output_video output{"output.mp4", input.get_width(), input.get_height()};*/

	auto edge_provider_ptr = std::make_shared<edge_provider_4connected<color_distance_counter>>();
	auto segmenter_ptr = std::make_shared<graph_based_frame_segmenter>(edge_provider_ptr);
	auto pixel_handler_ptr = std::make_shared<pixel_border_highlighter>();
	auto painter_ptr = std::make_shared<segment_frame_handler<pixel_border_highlighter>>(segmenter_ptr, pixel_handler_ptr, TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE);


	video_handler handler{ painter_ptr };
    //thread_video_handler handler{1, painter_ptr};

	//std::cout << "input.mp4 processing started" << std::endl;
 //   precise_stopwatch stopwatch;
	//handler.process(input, output);
 //   auto actual_wait_time = stopwatch.elapsed_time<unsigned int, std::chrono::microseconds>() / 1000;
 //   std::cout << "elapsed time: " << actual_wait_time << std::endl;
	//std::cout << "input.mp4 processing finished" << std::endl;
	for (size_t i = 1; i < 2; ++i)
	{
        input_video input{ "input.mp4" };
        output_video output{{ "output.avi"}, input.get_width(), input.get_height() };

        thread_video_handler handler{ 2, painter_ptr };
        //video_handler handler{ painter_ptr };
        precise_stopwatch stopwatch;
        handler.process(input, output);
        auto actual_wait_time = stopwatch.elapsed_time<unsigned int, std::chrono::microseconds>() / 1000;
        std::cout << "thread " << i << " elapsed time: " << actual_wait_time << std::endl;
	}
    return 0;
}

//image handling
//int main() {
//
//	graph_based_parameter_segmentation TEST_MERGE_CONSTANT = { 10000 };
//	size_t MIN_SEGMENT_SIZE = { 1000 };
//
//	/*auto file_name = cv::samples::findFile("input_image.jpg");*/
//	Image input_image{ "input_image.jpg" };
//	if (input_image.empty())
//	{
//		std::cout << "cannot open input_image.jpg" << std::endl;
//		return 1;
//	}
//
//	auto edge_provider_ptr = std::make_shared<edge_provider_4connected<color_distance_counter>>();
//	auto segmenter_ptr = std::make_shared<graph_based_frame_segmenter>(edge_provider_ptr);
//	auto pixel_handler_ptr = std::make_shared<pixel_painter>(15);
//	auto painter = segment_frame_handler(segmenter_ptr, 
//		pixel_handler_ptr, TEST_MERGE_CONSTANT, MIN_SEGMENT_SIZE);
//
//	std::cout << "input_image.jpg processing started" << std::endl;
//	auto output_image = painter.process_image(input_image);
//	output_image.save("output_image.jpg");
//	std::cout << "input_image.jpg processing finished" << std::endl;
//
//	return 0;
//}



