#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "colorsdispatcher.hpp"
#include "inference.h"
#include "tracker.h"
#include "videocapturewrapper.hpp"
#include "videowriterwrapper.hpp"


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

    VideoCaptureWrapper cap{args.sourceFname};
    
    std::size_t pAt = args.sourceFname.find_last_of('.');
    const std::string outFname = args.sourceFname.substr(0, pAt) + "_dets.avi";
    int ex = static_cast<int>(cap.get(cv::CAP_PROP_FOURCC));
    cv::Size s{static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
               static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))};
    double fps{cap.get(cv::CAP_PROP_FPS)};

    VideoWriterWrapper out{outFname, ex, fps, s};
    Inference inf{args.detectorFname, cv::Size{640, 640}, "", args.runOnGPU};
    Tracker tracker;

    cv::Mat frame;
    int frameIdx {0};
    ColorsDispatcher colors;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        ++frameIdx;

        std::vector<Detection> output = inf.runInference(frame);
        std::vector<cv::Rect> bboxes;
        for (size_t i = 0; i < output.size(); ++i) {
            Detection& detection = output[i];
            
            cv::Rect& box = detection.box;
            bboxes.push_back(box);
        }

        tracker.Run(bboxes);
        const auto tracks = tracker.GetTracks();

        for (const auto& [trackId, track] : tracks) {
            if (track.coast_cycles_ < kMaxCoastCycles &&
                (track.hit_streak_ >= kMinHits || frameIdx < kMinHits)) {
                    const cv::Rect bbox = track.GetStateAsBbox();
                    cv::Scalar color = colors.getColor(trackId);
                    cv::putText(frame, std::to_string(trackId), cv::Point(bbox.tl().x, bbox.tl().y-10),
                                cv::FONT_HERSHEY_DUPLEX, 2, color, 3);
                    cv::rectangle(frame, bbox, color, 3);
                }
        }

        out << frame;
    }
}
