#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <windows.h>
#include <cmath>
#include <thread>
#include <vector>
#include <random>

#include "engine.hpp"

const size_t num_threads = std::thread::hardware_concurrency() > 4 ? std::thread::hardware_concurrency() - 2 : 4;
std::vector<std::thread> threads(num_threads);

// Add global variables for grid dimensions
size_t GRID_X = num_threads*128; //1280 ... 1920;
size_t GRID_Y = num_threads*72; //720 ... 1080;
size_t GRID_Z = 1;
size_t BOX_N  = 2;

POINT mousePos;

int main()
{
    auto GRID = std::unique_ptr<Engine::Grid>(new Engine::Grid(GRID_X, GRID_Y, GRID_Z));
    size_t total_x = GRID->get_size_x();
    size_t total_y = GRID->get_size_y();
    size_t total_work = total_x * total_y;
    size_t chunk = total_work / num_threads;
    size_t area = chunk / 2;
    std::cout << "Main " << __cplusplus << std::endl;

    // Create window only once
    static HWND hwnd = nullptr;
    static HDC hdc = nullptr;
    static BITMAPINFO bmi = {};
    static std::vector<uint32_t> pixels(GRID_X * GRID_Y);

    if (!hwnd) {
        WNDCLASSW wc = {
            /* style         */ 0,
            /* lpfnWndProc   */ DefWindowProcW,
            /* cbClsExtra    */ 0,
            /* cbWndExtra    */ 0,
            /* hInstance     */ GetModuleHandleW(nullptr),
            /* hIcon         */ nullptr,
            /* hCursor       */ nullptr,
            /* hbrBackground */ nullptr,
            /* lpszMenuName  */ nullptr,
            /* lpszClassName */ L"GridWindowClass"
        };
        RegisterClassW(&wc);

        hwnd = CreateWindowExW(
            0, wc.lpszClassName, L"GridAndBoxes",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, (int)GRID_X, (int)GRID_Y,
            nullptr, nullptr, wc.hInstance, nullptr
        );
        hdc = GetDC(hwnd);

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = (LONG)GRID_X;
        bmi.bmiHeader.biHeight = -(LONG)GRID_Y; // top-down
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
    }

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    for(size_t i=0; i < GRID->get_size_x(); i++)
    {
        for(size_t j=0; j < GRID->get_size_y(); j++)
        {
            for(size_t k=0; k < GRID->get_size_z(); k++)
            {
                for(size_t l=0; l < BOX_N; l++)
                {
                    auto b1 = GRID->at(i,j,k);
                    b1->insert();
                    auto o1 = GRID->at(i,j,k,0);
                    // Create a simple water pattern: sine wave based on position
                    double freq = 0.1;
                    double amp = 127.5;
                    double offset = 127.5;
                    o1->val = static_cast<uint8_t>(
                        amp * (std::sin(freq * i + freq * j + freq * k + l * 10) +
                               std::cos(freq * i - freq * j + freq * k - l * 10)) * 0.5 + offset
                    );
                }
            }
        }
    }

    std::cout << "All objects after: "
              << Engine::Object::GetAllObjects().size()
              << " | Memory size: "
              << (Engine::Object::GetAllObjects().size() * sizeof(Engine::Object)) / 1024 / 1024
              << " MB"
              << std::endl;

    // End timing and print duration
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Create time: " << duration << " us" << std::endl << std::endl;

    // Lambda for thread work
    auto worker = [&](size_t thread_id)
    {
        GetCursorPos(&mousePos);
        ScreenToClient(hwnd, &mousePos);
        size_t start = thread_id * chunk;
        size_t end = (thread_id == num_threads - 1) ? total_work : (start + chunk);

        static thread_local size_t seed = 0;
        static thread_local std::mt19937 rng(std::random_device{}());
        static thread_local std::uniform_int_distribution<size_t> dist(0, 1);

        for (size_t idx = start; idx < end; ++idx)
        {
            int mouse_x = mousePos.x;
            int mouse_y = mousePos.y;

            size_t i = idx / total_y;
            size_t j = idx % total_y;

            seed = dist(rng);

            // Avoid out-of-bounds for swap
            if (i + 1 < total_x && j + 1 < total_y)
            {
                // Check if within 20 pixels of mouse position
                int dx = static_cast<int>(i) - mouse_x;
                int dy = static_cast<int>(j) - mouse_y;
                size_t ni = i + seed; // i or i+1
                size_t nj = j + seed; // j or j+1
                if ((dx * dx + dy * dy) < static_cast<int>(area))
                {
                    ni = i + seed; // i or i+1
                    nj = j - seed; // j or j+1
                }
                if (ni < total_x && nj < total_y)
                {
                    Engine::Grid::swap(GRID->at(i, j, 0), GRID->at(ni, nj, 0));
                }
            }

            // Map val to color (simple grayscale)
            if (i < GRID_X && j < GRID_Y)
            {
            uint8_t c = GRID->at(i, j, 0, 0)->val;
            pixels[j * GRID_X + i] = (0xFF << 24) | (c << 16) | (c << 8) | c;
            }
        }
    };

    while (true)
    {
        auto start = std::chrono::high_resolution_clock::now();
        // Launch threads
        for (size_t t = 0; t < num_threads; ++t)
        {
            threads[t] = std::thread(worker, t);
        }
        // Join threads
        for (auto& th : threads)
        {
            th.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Loop time: " << duration << " us " << std::endl;

        // Get current window client size
        RECT rect;
        GetClientRect(hwnd, &rect);
        int win_width = rect.right - rect.left;
        int win_height = rect.bottom - rect.top;

        // Draw to window, stretching pixels to fit window size
        StretchDIBits(
            hdc, 0, 0, win_width+40, win_height+40,
            0, 0, (int)GRID_X, (int)GRID_Y,
            pixels.data(), &bmi, DIB_RGB_COLORS, SRCCOPY
        );

        // Handle window messages
        MSG msg;
        while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    return 0;
}
