#pragma once

#include <stdexcept>
#include <string>

#include "opencv2/videoio.hpp"


class VideoCaptureWrapper {
public:
    VideoCaptureWrapper(const std::string& fname) : m_cap{fname} {
        if (!m_cap.isOpened()) {
            throw std::runtime_error("Unable to open video source " + fname);
        }
    }

    double get(int propId) const {
        return m_cap.get(propId);
    }

    cv::VideoCapture& operator>>(cv::Mat& mat) {
        return m_cap >> mat;
    }

    ~VideoCaptureWrapper() {
        m_cap.release();
    }
private:
    cv::VideoCapture m_cap;
};
