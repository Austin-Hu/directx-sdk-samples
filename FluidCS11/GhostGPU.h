#pragma once

#include <dxgi.h>
#include <d3d11.h>

class GhostGPU
{
public:
    GhostGPU() {}
    ~GhostGPU() {}
    void Init()
    {
        HRESULT hr=S_OK;
        IDXGIFactory* pFactory = NULL;
        CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);

        IDXGIAdapter* pAdapter;
        hr = pFactory->EnumAdapters(0, &pAdapter);
        DXGI_ADAPTER_DESC       adapterDesc;

        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE,
        };
        UINT numDriverTypes = ARRAYSIZE(driverTypes);

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };
        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

        D3D_FEATURE_LEVEL       out_featureLevel = D3D_FEATURE_LEVEL_11_0;

        const UINT createDeviceFlags = 0; //D3D11_CREATE_DEVICE_DEBUG

        if (hr != DXGI_ERROR_NOT_FOUND)
        {
            pAdapter->GetDesc(&adapterDesc);

            hr = D3D11CreateDevice(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
                D3D11_SDK_VERSION, &m_pd3dDevice, &out_featureLevel, &m_pd3dImmediateContext);
        }
    }

    void ReleaseAll()
    {
        SAFE_RELEASE(m_pParticlesSRV);
        SAFE_RELEASE(m_pParticlesUAV);
        SAFE_RELEASE(m_pParticles);

        SAFE_RELEASE(m_pParticlesCPU);

        SAFE_RELEASE(m_pParticleDensitySRV);
        SAFE_RELEASE(m_pParticleDensityUAV);
        SAFE_RELEASE(m_pParticleDensity);

        SAFE_RELEASE(m_pParticleForcesSRV);
        SAFE_RELEASE(m_pParticleForcesUAV);
        SAFE_RELEASE(m_pParticleForces);

        SAFE_RELEASE(m_pSortedParticlesSRV);
        SAFE_RELEASE(m_pSortedParticlesUAV);
        SAFE_RELEASE(m_pSortedParticles);

        SAFE_RELEASE(m_pForce_SimpleCS);
        SAFE_RELEASE(m_pDensity_SimpleCS);
        SAFE_RELEASE(m_pIntegrateCS);

        SAFE_RELEASE(m_pcbSimulationConstants);
    }

    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pd3dImmediateContext = nullptr;

    ID3D11Buffer* m_pcbSimulationConstants = nullptr;

    ID3D11ComputeShader* m_pForce_SimpleCS = nullptr;
    ID3D11ComputeShader* m_pDensity_SimpleCS = nullptr;
    ID3D11ComputeShader* m_pIntegrateCS = nullptr;

    ID3D11Buffer* m_pParticles = nullptr;
    ID3D11Buffer* m_pParticlesCPU = nullptr;
    ID3D11ShaderResourceView* m_pParticlesSRV = nullptr;
    ID3D11UnorderedAccessView* m_pParticlesUAV = nullptr;

    ID3D11Buffer* m_pSortedParticles = nullptr;
    ID3D11ShaderResourceView* m_pSortedParticlesSRV = nullptr;
    ID3D11UnorderedAccessView* m_pSortedParticlesUAV = nullptr;

    ID3D11Buffer* m_pParticleDensity = nullptr;
    ID3D11ShaderResourceView* m_pParticleDensitySRV = nullptr;
    ID3D11UnorderedAccessView* m_pParticleDensityUAV = nullptr;

    ID3D11Buffer* m_pParticleForces = nullptr;
    ID3D11ShaderResourceView* m_pParticleForcesSRV = nullptr;
    ID3D11UnorderedAccessView* m_pParticleForcesUAV = nullptr;
};