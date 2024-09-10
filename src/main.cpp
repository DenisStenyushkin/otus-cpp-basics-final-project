#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include "inference.h"


struct Arguments {
    bool isCorrect;
    std::string sourceFname;
    std::string detectorFname;
    bool runOnGPU;
};

Arguments parseArguments(int argc, char* argv[]) {
    const std::string arg_keys = 
        "{help h usage ? || print this message}"
        "{@sourceFname   || path to source video file}"
        "{@detectorFname || path to detector weights file}"
        "{gpu            || use gpu}";
    cv::CommandLineParser cl_parser(argc, argv, arg_keys);

    bool isCorrect{ true };
    std::string sourceFname{ cl_parser.get<std::string>("@sourceFname") };
    std::string detectorFname{ cl_parser.get<std::string>("@detectorFname") };
    bool runOnGPU{ cl_parser.has("gpu") };

    if (cl_parser.has("help") || sourceFname.empty() || detectorFname.empty()) {
        cl_parser.printMessage();
        isCorrect = false;
    }

    Arguments args {
        isCorrect, sourceFname, detectorFname, runOnGPU
    };

    return args;
}


int main(int argc, char* argv[]) {
    Arguments args = parseArguments(argc, argv);
    if (!args.isCorrect) {
        return 0;
    }

    cv::VideoCapture cap{args.sourceFname};
    if (!cap.isOpened()) {
        std::cerr << "Unable to open video source.\n";
        return -1;
    }
    
    std::size_t pAt = args.sourceFname.find_last_of('.');
    const std::string outFname = args.sourceFname.substr(0, pAt) + "_dets.avi";
    int ex = static_cast<int>(cap.get(cv::CAP_PROP_FOURCC));
    cv::Size s{static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
               static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))};
    double fps{cap.get(cv::CAP_PROP_FPS)};
    cv::VideoWriter out{outFname, ex, fps, s, true};
    if (!out.isOpened()) {
        std::cerr << "Could not open out stream.\n";
        return -1;
    }

    Inference inf{args.detectorFname, cv::Size{640, 640}, "", args.runOnGPU};

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        std::vector<Detection> output = inf.runInference(frame);
        for (size_t i = 0; i < output.size(); ++i) {
            Detection& detection = output[i];
            
            cv::Rect& box = detection.box;
            cv::Scalar& color = detection.color;
            cv::rectangle(frame, box, color, 2);

            cv::Size textSize = cv::getTextSize(detection.className, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
            cv::Rect textBox{box.x, box.y - 40, textSize.width + 10, textSize.height + 20};
            cv::rectangle(frame, textBox, color, cv::FILLED);
            cv::putText(frame, detection.className, cv::Point{box.x + 5, box.y - 10},
                        cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar{0, 0, 0}, 2, 0);
        }

        out << frame;
    }
    
    cap.release();
    out.release();
}
