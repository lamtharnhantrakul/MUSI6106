
// standard headers
#include <limits>

// project headers
#include "MUSI6106Config.h"

#include "ErrorDef.h"
#include "Util.h"
#include "RingBuffer.h"

#include "CombFilterIf.h"
#include "CombFilter.h"


CCombFilterBase::CCombFilterBase( int iMaxDelayInFrames, int iNumChannels ) :
    m_ppCRingBuffer(0),
    m_iNumChannels(iNumChannels)
{

    assert(iMaxDelayInFrames > 0);
    assert(iNumChannels > 0);

    // There is a ring buffer per channel of audio
     for (int c = 0; c < iNumChannels; c++) {
         m_ppCRingBuffer[c] = new CRingBuffer<float>(iMaxDelayInFrames);
     }

    // Initialize both of the L ring buffer and the R ring buffer to have contents of 0
    for (int c = 0; c < iNumChannels; c++) {
        for (int j = 0; j < iMaxDelayInFrames; j++) {
            m_ppCRingBuffer[c]->putPostInc(0);
        }
    }

    // Set WriteIdx to end of ring buffer, set ReadIdx to start of buffer
    for (int i = 0; i < iNumChannels; i++) {
        m_ppCRingBuffer[i]->setWriteIdx(iMaxDelayInFrames);
        m_ppCRingBuffer[i]->setReadIdx(0);
    }

}

CCombFilterBase::~CCombFilterBase()
{
}

Error_t CCombFilterBase::resetInstance()
{

    return kNoError;
}

Error_t CCombFilterBase::setParam( CCombFilterIf::FilterParam_t eParam, float fParamValue )
{
    if (!isInParamRange(eParam, fParamValue))
        return kFunctionInvalidArgsError;

    this->m_afParam[eParam] = fParamValue;

    return kNoError;
}

float CCombFilterBase::getParam( CCombFilterIf::FilterParam_t eParam ) const
{
    return this->m_afParam[eParam];
}

bool CCombFilterBase::isInParamRange( CCombFilterIf::FilterParam_t eParam, float fValue )
{
    if (fValue < m_aafParamRange[eParam][0] || fValue > m_aafParamRange[eParam][1])q
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

    for (int n = 0; n < iNumberOfFrames; n++) {
        for (int c = 0; c < this->m_iNumChannels; c++) {
            ppfOutputBuffer[c][n] = ppfInputBuffer[c][n] + (getParam(CCombFilterIf::FilterParam_t kParamGain))*(m_ppCRingBuffer[c]->getPostInc());
            m_ppCRingBuffer[c]->putPostInc(ppfInputBuffer[c][n]);
        }
    }
    return kNoError;
}


CCombFilterIir::CCombFilterIir (int iMaxDelayInFrames, int iNumChannels) : CCombFilterBase(iMaxDelayInFrames, iNumChannels)
{
}

Error_t CCombFilterIir::process( float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames )
{
    for (int n = 0; n < iNumberOfFrames; n++) {
        for (int c = 0; c < this->m_iNumChannels; c++) {
            ppfOutputBuffer[c][n] = ppfInputBuffer[c][n] + (getParam(CCombFilterIf::FilterParam_t kParamGain))*(m_ppCRingBuffer[c]->getPostInc());
            m_ppCRingBuffer[c]->putPostInc(ppfOutputBuffer[c][n]);
        }
    }
    return kNoError;
}
