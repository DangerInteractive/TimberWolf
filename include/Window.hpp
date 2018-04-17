#ifndef H_CLASS_WINDOW
#define H_CLASS_WINDOW

#include <string>
#include <functional>
#include <memory>
#include <exception>
#include <stdexcept>
#include <iomanip>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Color.hpp"
#include "Log.hpp"

namespace tw {
class Window {

public:

    typedef std::function <void (GLFWwindow*, int, int, int, int)> KeyCallback;
    typedef std::function <void (GLFWwindow*, double, double)> CursorCallback;
    typedef std::function <void (GLFWwindow*, int)> CursorInOutCallback;
    typedef std::function <void (GLFWwindow*, int, int, int)> MouseButtonCallback;
    typedef std::function <void (GLFWwindow*, double, double)> ScrollCallback;
    typedef std::function <void (GLFWwindow*, int, const char**)> DropCallback;

    Window () = delete; // static only
    ~Window () = delete;

    Window (Window&&) = delete;
    Window& operator = (Window&&) = delete;

    Window (const Window&) = delete;
    Window& operator = (const Window&) = delete;

    static void init ();
    static void deinit ();

    static GLFWwindow* getContext ();
    static void makeContextCurrent ();

    static bool isOpen ();
    static void open ();
    static void close ();
    static void destroy ();

    static void clear ();
    static void clear (const Color&);
    static void clear (float, float, float, float);

    static int getWidth ();
    static int getHeight ();
    static void setWidth (const int);
    static void setHeight (const int);
    static void setSize (const int, const int);

    static std::string getTitle ();
    static void setTitle (const std::string&);

    static int getGlVersionMajor ();
    static int getGlVersionMinor ();
    static std::string getGlVersion ();
    static void setGlVersionMajor (const int);
    static void setGlVersionMinor (const int);
    static void setGlVersion (const int, const int);

    static void setKeyCallback ();

private:

    static void pushWindowSize ();
    static void pushWindowTitle ();

    struct GLFWwindowDeleter{
        void operator () (GLFWwindow* ptr) { glfwDestroyWindow(ptr); }
    };
    static std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_context;

    static int m_width;
    static int m_height;
    static std::mutex mutex_size;

    static std::string m_title;
    static std::mutex mutex_title;

    static int m_glVersionMajor;
    static int m_glVersionMinor;
    static std::mutex mutex_glVersion;

    static Color m_lastClearColor;
    static const Color m_defaultClearColor;

};
}

#endif
