#include <random>
#include <vector>

#include "opencv2/core.hpp"


class ColorsDispatcher {
public:
    explicit ColorsDispatcher(size_t capacity = 5) : m_colors{}, m_rd{},
                                                  m_rg{m_rd()}, m_distr{0, 255} {
        m_colors.reserve(capacity);
    }

    cv::Scalar getColor(size_t colorIdx) {
        if (colorIdx > m_colors.capacity()) {
            colorIdx %= m_colors.capacity();
        }

        if (colorIdx > m_colors.size()) {
            m_colors.push_back(cv::Scalar(m_distr(m_rg),
                                          m_distr(m_rg),
                                          m_distr(m_rg)));
        }

        return m_colors[colorIdx];
    }
private:
    std::vector<cv::Scalar> m_colors;
    std::random_device m_rd;
    std::mt19937 m_rg;
    std::uniform_int_distribution<int> m_distr;
};
