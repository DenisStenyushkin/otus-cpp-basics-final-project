#pragma once

#include <stdexcept>
#include <string>

#include "opencv2/videoio.hpp"


class VideoWriterWrapper {
public:
    VideoWriterWrapper(const std::string& fname, int ex, double fps, cv::Size s) 
        : m_wrt{fname, ex, fps, s, true} {
        if (!m_wrt.isOpened()) {
            throw std::runtime_error("Unable to open out stream " + fname);
        }
    }

    cv::VideoWriter& operator<<(const cv::Mat& mat) {
        return m_wrt << mat;
    }

    ~VideoWriterWrapper() {
        m_wrt.release();
    }
private:
    cv::VideoWriter m_wrt;
};
