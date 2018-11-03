#include "../../../include/TimberWolf/Core/Observer.hpp"

std::unique_lock<std::mutex> tw::Observer::getLock () {

    return std::unique_lock<std::mutex>(m_mutex);

}

bool tw::Observer::isAlive () const noexcept {

    return m_isAlive;

}

void tw::Observer::kill () {

    auto lock = getLock();

    m_isAlive = false;

}
