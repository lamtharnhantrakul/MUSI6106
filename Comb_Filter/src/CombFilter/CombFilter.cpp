
// standard headers
#include <limits>
#include <iostream>
// project headers
#include "MUSI6106Config.h"

#include "ErrorDef.h"
#include "Util.h"
#include "RingBuffer.h"

#include "CombFilterIf.h"
#include "CombFilter.h"

// Oh i added new code that works!

CCombFilterBase::CCombFilterBase( int iMaxDelayInFrames, int iNumChannels ) :
    m_ppCRingBuffer(0),
    m_iNumChannels(iNumChannels)
{

    assert(iMaxDelayInFrames > 0);
    assert(iNumChannels > 0);

    // not sure
    m_aafParamRange[CCombFilterIf::kParamGain][0] = std::numeric_limits<float>::min();
    m_aafParamRange[CCombFilterIf::kParamGain][1] = std::numeric_limits<float>::max();

    // not sure
    m_aafParamRange[CCombFilterIf::kParamDelay][0] = 0.f;
    m_aafParamRange[CCombFilterIf::kParamDelay][1] = iMaxDelayInFrames;

    // initialize parameters to 0
    m_afParam[CCombFilterIf::kParamGain] = 0.f;
    m_afParam[CCombFilterIf::kParamDelay] = 0.f;

    // allocate memory
    m_ppCRingBuffer = new CRingBuffer<float>* [iNumChannels];
    for (int i = 0; i < iNumChannels; ++i) {
        m_ppCRingBuffer[i] = new CRingBuffer<float>(iMaxDelayInFrames);
    }
}

CCombFilterBase::~CCombFilterBase()
{
    for (int i = 0; i < m_iNumChannels; ++i) {
        delete m_ppCRingBuffer[i];
    }
    delete [] m_ppCRingBuffer;
    m_ppCRingBuffer = 0;
}

Error_t CCombFilterBase::resetInstance()
{
    m_afParam[CCombFilterIf::kParamGain] = 0.f;
    m_afParam[CCombFilterIf::kParamDelay] = 0.f;
    for (int i = 0; i < m_iNumChannels; ++i) {
        m_ppCRingBuffer[i]->reset();
    }
    return kNoError;
}

Error_t CCombFilterBase::setParam( CCombFilterIf::FilterParam_t eParam, float fParamValue )
{
    if (!isInParamRange(eParam, fParamValue))
        return kFunctionInvalidArgsError;
    m_afParam[eParam] = fParamValue;

    // If user is setting `kParamDelay` then clear the ring buffer with zeros up new read index
    if (eParam == CCombFilterIf::kParamDelay) {
        for (int i = 0; i < m_iNumChannels; ++i) {
            m_ppCRingBuffer[i]->setWriteIdx(m_ppCRingBuffer[i]->getReadIdx());
            for (int j = 0; j < fParamValue; ++j) {
                m_ppCRingBuffer[i]->putPostInc(0);
            }
        }
    }

    return kNoError;
}

float CCombFilterBase::getParam( CCombFilterIf::FilterParam_t eParam ) const
{
    return m_afParam[eParam];
}

bool CCombFilterBase::isInParamRange( CCombFilterIf::FilterParam_t eParam, float fValue )
{
    if (fValue < m_aafParamRange[eParam][0] || fValue > m_aafParamRange[eParam][1])
    {
        return false;
    }
    else
    {
        return true;
    }
}

Error_t CCombFilterFir::process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames )
{
    for (int j = 0; j < iNumberOfFrames; ++j) {
        for (int i = 0; i < m_iNumChannels; ++i) {
            ppfOutputBuffer[i][j] = ppfInputBuffer[i][j]
                                    + getParam(CCombFilterIf::kParamGain)
                                      * m_ppCRingBuffer[i]->getPostInc();
            m_ppCRingBuffer[i]->putPostInc(ppfInputBuffer[i][j]);
        }
    }
    return kNoError;
}


CCombFilterIir::CCombFilterIir (int iMaxDelayInFrames, int iNumChannels) : CCombFilterBase(iMaxDelayInFrames, iNumChannels)
{
    // not sure
    m_aafParamRange[CCombFilterIf::kParamGain][0] = -1.0f;
    m_aafParamRange[CCombFilterIf::kParamGain][1] = 1.0f;
}

Error_t CCombFilterIir::process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames )
{
    for (int j = 0; j < iNumberOfFrames; ++j) {
        for (int i = 0; i < m_iNumChannels; ++i) {
            ppfOutputBuffer[i][j] = ppfInputBuffer[i][j]
                                    + getParam(CCombFilterIf::kParamGain)
                                    * m_ppCRingBuffer[i]->getPostInc();
            m_ppCRingBuffer[i]->putPostInc(ppfOutputBuffer[i][j]);
        }
    }
    return kNoError;
}
