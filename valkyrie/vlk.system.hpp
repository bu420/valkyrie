#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define WINDOWS
#else
#error "Unsupported system."
#endif

#ifdef WINDOWS
#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi")
#endif
#include <string>
#include <vector>
#include <cstdint>

#include "vlk.types.hpp"
#include "vlk.gfx.hpp"

namespace vlk {
    void initialize();
    void terminate();

    f64 get_elapsed_time();
    i64 get_ticks_per_sec();

    struct window_params {
        std::string_view title;
        i32 width;
        i32 height;
        bool default_ui = true;
        bool transparent = false;
    };

    class window {
    public:
#ifdef WINDOWS
        HWND hwnd;
        // Raw pointer array because we need a consistent memory address.
        u32* pixels;
        // A handle to the window background bitmap.
        HBITMAP bitmap;
#endif

        window(const window_params& params);

        void poll_events();
        void swap_buffers(const color_buffer& color_buf);

        bool get_should_close() const;
        void set_should_close(bool should_close);

        i32 get_width() const;
        i32 get_height() const;

        bool is_transparent() const;

    private:
        bool should_close;

        i32 width;
        i32 height;

        bool transparent;
    };
}