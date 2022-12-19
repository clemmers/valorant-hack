
// g++ vall.cpp -o vall.exe -lgdi32



// restarting this project in c++ at 3 in the morning because i just woke up from
// a dream in which a girl told me she would only love me if i learned c++
// so sorry in advance if my c++ is unconventionally written
#include <iomanip>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cmath>



int main(int argc, char** argv)
{
    // loads the gdi32 library
    HINSTANCE _hGDI = LoadLibrary("gdi32.dll");

    
    // checks if the library was loaded successfully
    if (_hGDI == NULL)
    {
        std::cout << "Failed to load gdi32 library" << std::endl;
        return -1;
    }

    std::cout << "Running..." << std::endl;

    // gets the screen width and height
    const int screenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
    
    // sets the offset value
    const int offset = screenWidth / 50;


    // sets the color values and disparity
    const int red = 172; // 172 enemy 106 reaction time test
    const int green = 62; // 62 enemy 219 reaction time test
    const int blue = 170; // 170 enemy 75 reaction time test


    // how far the checked color can be to set color
    const int colorDisparity = 80;

    while(true)
    {

        // defines a BITMAPINFO structure to describe the memory buffer
        BITMAPINFO bmi;
        memset(&bmi, 0, sizeof(bmi));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = 1; // width of the memory buffer
        bmi.bmiHeader.biHeight = 1; // height of the memory buffer
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32; // each pixel is a 32-bit value
        bmi.bmiHeader.biCompression = BI_RGB;

        // creates a memory buffer to store the pixels
        void* pBuffer;
        HDC hdcScreen = GetDC(NULL);
        HBITMAP hBitmap = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &pBuffer, NULL, 0);

        // creates a device context for the memory buffer
        HDC hdcBuffer = CreateCompatibleDC(hdcScreen);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcBuffer, hBitmap);

        
        // uses BitBlt to copy the pixels from the screen into the memory buffer
        if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth, screenHeight, SRCCOPY) == 0)
        {
            std::cout << "Failed to copy pixels from the screen" << std::endl;
            return -1;
        }

        // gets the color of the center pixel
        int* pPixels = (int*)pBuffer;
        int centerPixel = pPixels[0];

        // extracts the red, green, and blue values from the pixel
        int r = GetRValue(centerPixel);
        int g = GetGValue(centerPixel);
        int b = GetBValue(centerPixel);



        // calculates the euclidean distance between the current pixel color and (255, 255, 255)
        double distance = sqrt(pow(r - red, 2) + pow(g - green, 2) + pow(b - blue, 2));

        // checks if the distance is less than or equal to the threshold
        
        if (distance <= colorDisparity)
        {
            std::cout << "enemy spotted!!" << std::endl;
            // simulates a left mouse click
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(50);
        }


        // std::cout << "Center pixel color: (" << r << ", " << g << ", " << b << ")" << std::endl;

        // checks pixel to the left of center pixel
        if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth - offset, screenHeight + screenWidth / 192, SRCCOPY) == 0)
            {
                std::cout << "Failed to copy pixels from the screen" << std::endl;
                return -1;
            }

        int leftPixel = pPixels[0];
        r = GetRValue(leftPixel);
        g = GetGValue(leftPixel);
        b = GetBValue(leftPixel);

        distance = sqrt(pow(r - red, 2) + pow(g - green, 2) + pow(b - blue, 2));
        if (distance <= colorDisparity)
        {
            std::cout << "enemy spotted!! left" << std::endl;
            // simulates a left mouse click
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(50);
        }

        
        // checks pixel to the right of center pixel
        if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth + offset, screenHeight + screenWidth / 192, SRCCOPY) == 0)
            {
                std::cout << "Failed to copy pixels from the screen" << std::endl;
                return -1;
            }


        int rightPixel = pPixels[0];
        r = GetRValue(rightPixel);
        g = GetGValue(rightPixel);
        b = GetBValue(rightPixel);
        distance = sqrt(pow(r - red, 2) + pow(g - green, 2) + pow(b - blue, 2));
        if (distance <= colorDisparity)
        {
            std::cout << "enemy spotted!! right" << std::endl;
            // simulates a left mouse click
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(50);
        }

        // checks pixel below center pixel
        if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth + screenWidth / 192, screenHeight + offset, SRCCOPY) == 0)
            {
                std::cout << "Failed to copy pixels from the screen" << std::endl;
                return -1;
            }
        
        int bottomPixel = pPixels[0];
        r = GetRValue(bottomPixel);
        g = GetGValue(bottomPixel);
        b = GetBValue(bottomPixel);
        distance = sqrt(pow(r - red, 2) + pow(g - green, 2) + pow(b - blue, 2));
        if (distance <= colorDisparity)
        {
            std::cout << "enemy spotted!! down" << std::endl;
            // simulates a left mouse click
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(50);
        }
        
            // cleans up the resources
            SelectObject(hdcBuffer, hOldBitmap);
            DeleteDC(hdcBuffer);
            ReleaseDC(NULL, hdcScreen);
            DeleteObject(hBitmap);

    }

    return 0;
}
