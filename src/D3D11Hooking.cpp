#include <d3d11.h>
#include <iostream>
#include "D3D11Hooking.hpp"

bool GetD3D11SwapchainDeviceContext(IDXGISwapChain** pSwapchain, ID3D11Device** pDevice,
    ID3D11DeviceContext** pContextTable)
{
    WNDCLASSEX wc{ 0 };
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = DefWindowProc;
    wc.lpszClassName = TEXT("vc");

    if (!RegisterClassEx(&wc))
    {
        std::cout << "Failed to register class\n";
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };

    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.OutputWindow = GetForegroundWindow();
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel;
    bool success = false;

    for (D3D_DRIVER_TYPE driverType : DRIVER_TYPE_LIST)
    {
        std::cout << driverType;
        HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 0, NULL, 0,
            D3D11_SDK_VERSION, &swapChainDesc, pSwapchain, pDevice, &featureLevel, nullptr);

        if (!FAILED(hr))
        {
            success = true;
            break;
        }
    }

    DWORD dwOld;
    VirtualProtect(GetD3D11SwapchainDeviceContext, 2, PAGE_EXECUTE_READWRITE, &dwOld);

    DestroyWindow(swapChainDesc.OutputWindow);
    UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

    if (!success)
    {
        std::cout << "Failed to create DeviceAndSwapChain for all driver types." << "\n";
        return false;
    }

    return true;
}

D3D_PRESENT_FUNCTION GetD3D11PresentFunction()
{
    IDXGISwapChain* swapChain;
    ID3D11Device* device;
    ID3D11DeviceContext* ctx;

    if (GetD3D11SwapchainDeviceContext(&swapChain, &device, &ctx))
    {
        void** vmt = *(void***)swapChain;

        SAFE_RELEASE(swapChain);
        SAFE_RELEASE(device);
        SAFE_RELEASE(ctx);

        DWORD dwOld;
        VirtualProtect(GetD3D11PresentFunction, 2, PAGE_EXECUTE_READWRITE, &dwOld);

        return (D3D_PRESENT_FUNCTION)vmt[8];
    }

    return NULL;
}