#include "../../../include/TimberWolf/Core/Gradient.hpp"

tw::Color tw::Gradient::getColor (float position) const {

    if (std::isnan(position)) {
        return m_colorNaN;
    }

    if (position == -INFINITY) {
        return m_colorNegativeInfinity;
    }

    if (position == INFINITY) {
        return m_colorPositiveInfinity;
    }

    if (m_points.find(position) != m_points.end()) {
        return m_points.at(position);
    }

    auto lowerEntry = m_points.lower_bound(position);
    auto upperEntry = m_points.upper_bound(position);

    if (lowerEntry == m_points.end() && upperEntry == m_points.end()) {
        return Color();
    }

    if (lowerEntry == m_points.end() || upperEntry == m_points.end()) {
        return (lowerEntry == m_points.end() ? upperEntry : lowerEntry)->second;
    }

    float relativeValue = (position - lowerEntry->first) / (upperEntry->first - lowerEntry->first);

    return lowerEntry->second.makeInterpolate(upperEntry->second, relativeValue);

}

tw::Gradient& tw::Gradient::addPoint (float position, const Color& color) {

    if (std::isnan(position)) {
        m_colorNaN = color;
    } else if (position == INFINITY) {
        m_colorPositiveInfinity = color;
    } else if (position == -INFINITY) {
        m_colorNegativeInfinity = color;
    } else {
        m_points.insert_or_assign(
            std::move(position),
            std::move(color)
        );
    }

    return *this;

}
