#include "../include/Log.hpp"

/**
 * @class tw::Log
 *
 * Static class providing a global means of notifying all log observers
 * (polymorphic tw::LogObserver objects), and also storing and managing those
 * log observers.
 */

/**
 * @fn tw::Log::log
 *
 * Send a notificiation to all log observers containing a message log level
 * (verbose, notice, warning, error), a std::string context, which is a short
 * string representing the source or subsystem relating to the message, and any
 * data that can be converted into text. The message argument is variadic and
 * will accept any data type.
 *
 * @tparam T           variadic type of message arguments (automatically deduced)
 * @param  messageType message log level
 * @param  context     message context
 * @param  message     variadic message
 */

/**
 * @fn tw::Log::verbose
 *
 * Send a verbose log message to all log observers, taking in a std::string
 * context and a variadic message of any types that can be converted to text.
 *
 * @tparam T       variadic type of message arguments (automatically deduced)
 * @param  context message context
 * @param  message variadic message
 */

/**
 * @fn tw::Log::notice
 *
 * Send a notice log message to all log observers, taking in a std::string
 * context and a variadic message of any types that can be converted to text.
 *
 * @tparam T       variadic type of message arguments (automatically deduced)
 * @param  context message context
 * @param  message variadic message
 */

/**
 * @fn tw::Log::warning
 *
 * Send a warning log message to all log observers, taking in a std::string
 * context and a variadic message of any types that can be converted to text.
 *
 * @tparam T       variadic type of message arguments (automatically deduced)
 * @param  context message context
 * @param  message variadic message
 */

/**
 * @fn tw::Log::error
 *
 * Send an error log message to all log observers, taking in a std::string
 * context and a variadic message of any types that can be converted to text.
 *
 * @tparam T       variadic type of message arguments (automatically deduced)
 * @param  context message context
 * @param  message variadic message
 */

/**
 * Make unhandled exceptions send a message to the game engine logging subsystem
 * before aborting.
 */
void tw::Log::bindUnhandledException () {

    std::set_terminate([](){
        tw::Log::error("system", "Unhandled exception.");
        std::abort();
    });

}

/**
 * @fn tw::Log::makeObserver
 *
 * Factory method that constructs a log observer of a given type and parameters,
 * registers it, and then returns a pointer to it.
 *
 * @tparam T    type of log observer to construct (must extend tw::LogObserver)
 * @tparam Targ variadic types of the arguments passed to T constructor (automatically deduced)
 * @param  args variadic arugments forwarded to T constructor
 */

/**
 * Register a std::unique_ptr to a tw::LogObserver (polymorphic) object to
 * receive log messages.
 *
 * @param observer unique pointer to log observer
 */
void tw::Log::registerObserver (std::unique_ptr<LogObserver>&& observer) {

    m_observers.push_back(std::move(observer));

}

/**
 * Register a pointer to a tw::LogObserver (polymorphic) object to receive log
 * messages. Note that despite being passed as a regular pointer, it will be
 * stored as a unique pointer and will therefore be deleted if removed.
 *
 * @param observer pointer to log observer
 */
void tw::Log::registerObserver (LogObserver* observer) {

    m_observers.emplace_back(observer);

}

/**
 * @fn tw::Log::concatMessage
 *
 * Combine a variadic set of arguments that can be converted into text into a
 * single std::string.
 *
 * @tparam T       variadic types of arguments
 * @param  message variadic arguments
 * @return concatenation of all arguments
 */

std::mutex tw::Log::m_mutex; ///< Mutex to be locked during message sending to prevent out of order sends.
std::vector<std::unique_ptr<tw::LogObserver>> tw::Log::m_observers {}; ///< Collection of attached log observers.
