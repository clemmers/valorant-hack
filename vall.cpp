
// g++ val.cpp -o jittrippin.exe -lgdi32



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
    Sleep(5000);
    // gets the screen width and height
    const int screenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
    const int vertOffset = screenWidth / 192;
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
    
    // sets the offset value
    const int offset = screenWidth / 150;


    // sets the color values and disparity
    const int red = 172; // 172 enemy 106 reaction time test
    const int green = 62; // 62 enemy 219 reaction time test
    const int blue = 170; // 170 enemy 75 reaction time test


    // how far the checked color can be to set color
    const int colorDisparity = 80;

    // flag variable to keep track of whether the 'g' key has been pressed
    bool gKeyPressed = false;

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
        int r1, g1, b1, r2, g2, b2, r3, g3, b3;
        if (GetAsyncKeyState('G') & 0x8000) // check if the 'g' key is being held down
        {
            std::cout << "g pressed" << std::endl;
            gKeyPressed = !gKeyPressed;
            Sleep(200); // sets the flag variable to true

            // checks pixel to the left of center pixel
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth, screenHeight, SRCCOPY) == 0)
            {
                std::cout << "Failed to copy pixels from the screen" << std::endl;
                return -1;
            }

            // gets the color of the center pixel
            int* pPixels = (int*)pBuffer;
            int centerPixel = pPixels[0];

            // extracts the red, green, and blue values from the pixel
            r3 = GetRValue(centerPixel);
            g3 = GetGValue(centerPixel);
            b3 = GetBValue(centerPixel);

            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth - offset, screenHeight + vertOffset, SRCCOPY) == 0)
                {
                    std::cout << "Failed to copy pixels from the screen" << std::endl;
                    return -1;
                }

            int leftPixel = pPixels[0];
            r1 = GetRValue(leftPixel);
            g1 = GetGValue(leftPixel);
            b1 = GetBValue(leftPixel);

            // checks pixel to the right of center pixel
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth + offset, screenHeight + vertOffset, SRCCOPY) == 0)
                {
                    std::cout << "Failed to copy pixels from the screen" << std::endl;
                    return -1;
                }

            int rightPixel = pPixels[0];
            r2 = GetRValue(rightPixel);
            g2 = GetGValue(rightPixel);
            b2 = GetBValue(rightPixel);
            
        }
        if(gKeyPressed)
        {
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth, screenHeight, SRCCOPY) == 0)
            {
                std::cout << "Failed to copy pixels from the screen" << std::endl;
                return -1;
            }

            // gets the color of the center pixel
            int* pPixels = (int*)pBuffer;
            int centerPixel = pPixels[0];

            // extracts the red, green, and blue values from the pixel
            int rr3 = GetRValue(centerPixel);
            int gg3 = GetGValue(centerPixel);
            int bb3 = GetBValue(centerPixel);

            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth - offset, screenHeight + vertOffset, SRCCOPY) == 0)
                {
                    std::cout << "Failed to copy pixels from the screen" << std::endl;
                    return -1;
                }

            int leftPixel = pPixels[0];
            int rr1 = GetRValue(leftPixel);
            int gg1 = GetGValue(leftPixel);
            int bb1 = GetBValue(leftPixel);

            // checks pixel to the right of center pixel
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth + offset, screenHeight + vertOffset, SRCCOPY) == 0)
                {
                    std::cout << "Failed to copy pixels from the screen" << std::endl;
                    return -1;
                }

            int rightPixel = pPixels[0];
            int rr2 = GetRValue(rightPixel);
            int gg2 = GetGValue(rightPixel);
            int bb2 = GetBValue(rightPixel);
            // lmao
            if(rr1 != r1 || gg1 != g1 || bb1 != b1 || rr2 != r2 || gg2 != g2 || bb2 != b2 || rr3 != r3 || gg3 != g3 || bb3 != b3)
            {
                std::cout << "enemy spotted!!" << std::endl;
                // simulates a left mouse click
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                gKeyPressed = !gKeyPressed;
                Sleep(50);
            }

        }
        else if (GetAsyncKeyState('C') & 0x8000) // checks if the 'h' key is being held down
        {
            
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



            // calculates the euclidean distance between the current pixel color and the target color
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
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth - offset, screenHeight + vertOffset, SRCCOPY) == 0)
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
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth + offset, screenHeight + vertOffset, SRCCOPY) == 0)
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
            if (BitBlt(hdcBuffer, 0, 0, 1, 1, hdcScreen, screenWidth + vertOffset, screenHeight + offset, SRCCOPY) == 0)
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
        }
        // cleans up the resources
        SelectObject(hdcBuffer, hOldBitmap);
        DeleteDC(hdcBuffer);
        ReleaseDC(NULL, hdcScreen);
        DeleteObject(hBitmap);
    }
    return 0;
}
