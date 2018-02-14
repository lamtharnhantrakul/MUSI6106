
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"
#include "assert.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using std::cout;
using std::endl;

// local function declarations
struct TestSpec_t
{
    int                     iTestSignalLength;
    int                     iNumChannels;
    int                     iDelay;
    float                   fGain;
    float                   fMaxDelay;
    float                   fSamplingRate;
    bool                    bAutoPrint;
} structTestSpec;

void    showClInfo ();
void    initOutput(float**& ppfOutputSignal,TestSpec_t structTestSpec);
void    generateTestImpulseSignal(float**& ppfInputSignal, TestSpec_t structTestSpec);
void    printOutput(float**& ppfOutputSignal, TestSpec_t structTestSpec);
void    testImpulseOutputFIR(float**& ppfOutputSignal, TestSpec_t structTestSpec);
void    testImpulseOutputIIR(float**& ppfOutputSignal, int iNumChannels, int iDelay, float fGain, float fMaxDelay);
void    generateTestImpulseTrailSignal(float**& ppfInputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint);
void    processCombFilter(CCombFilterIf*& pInstance, float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec);
/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
        sOutputFilePath;

    static const int        kBlockSize = 1024;

    clock_t                 time = 0;

    float                   **ppfAudioData = 0;

    CAudioFileIf            *phAudioFile = 0;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;

    CCombFilterIf   *pInstance = 0;
    CCombFilterIf::create(pInstance);
    showClInfo();

    float                   **ppfInputSignal = 0;
    float                   **ppfOutputSignal = 0;



    structTestSpec.iTestSignalLength = 10;
    structTestSpec.iNumChannels = 2;
    structTestSpec.iDelay = 0;
    structTestSpec.fGain = 0.0;
    structTestSpec.fMaxDelay = 10.0f;
    structTestSpec.fSamplingRate = 1.0f;
    structTestSpec.bAutoPrint = true;

    /////////////////////////////////////////////////////////////////////////////

    initOutput(ppfOutputSignal, structTestSpec);
    if (structTestSpec.bAutoPrint) {printOutput(ppfOutputSignal, structTestSpec);}

    generateTestImpulseSignal(ppfInputSignal, structTestSpec);

    structTestSpec.iDelay = 4;
    structTestSpec.fGain = 0.8;
    // Define a simple FIR delay line where the sampling rate is 1 Hz
    processCombFilter(pInstance, ppfInputSignal, ppfOutputSignal, structTestSpec);

    // Check output
    if (structTestSpec.bAutoPrint) {printOutput(ppfOutputSignal, structTestSpec);}
    testImpulseOutputFIR(ppfOutputSignal, structTestSpec);

    /*
    // Reset output array for next test
    initOutput(ppfOutputSignal, iNumChannels, iTestSignalLength, false);

    // Define a simple IIR delay line where the sampling rate is 1 Hz
    pInstance->init(CCombFilterIf::kCombIIR, fMaxDelay, fSamplingRate, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, fGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);
    // Check output
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);
    testImpulseOutputIIR(ppfOutputSignal, iNumChannels, iDelay, fGain, fMaxDelay);


    generateTestImpulseTrailSignal(ppfInputSignal, iNumChannels, iTestSignalLength, true);

    pInstance->init(CCombFilterIf::kCombFIR, fMaxDelay, fSamplingRate, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, fGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);

    // Check output
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);
    testImpulseOutputFIR(ppfOutputSignal, iNumChannels, iDelay, fGain);

    */



    /*
    * TEST 3:
    */

}

/*
 * Debugging function to initialize output buffer with dummy zeros
 */
void initOutput(float**& ppfOutputSignal, TestSpec_t structTestSpec) {
    ppfOutputSignal = new float*[structTestSpec.iNumChannels];
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        ppfOutputSignal[c] = new float[structTestSpec.iTestSignalLength]();
    }
    if (structTestSpec.bAutoPrint) {
        cout << "Init Output Signal: " << endl;
        for (int c = 0; c < structTestSpec.iNumChannels; c++) {
            for (int i = 0; i < structTestSpec.iTestSignalLength; i++) {
                cout << ppfOutputSignal[c][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void generateTestImpulseSignal(float**& ppfInputSignal, TestSpec_t structTestSpec) {
    ppfInputSignal = new float *[structTestSpec.iNumChannels];
    // init to 0
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        ppfInputSignal[c] = new float[structTestSpec.iTestSignalLength]();
    }
    // put a 1 at start for impulse
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        ppfInputSignal[c][0] = 1;
    }

    if (structTestSpec.bAutoPrint) {
        cout << "Test Signal: " << endl;
        for (int c = 0; c < structTestSpec.iNumChannels; c++) {
            for (int i = 0; i < structTestSpec.iTestSignalLength; i++) {
                cout << ppfInputSignal[c][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void generateTestImpulseTrailSignal(float**& ppfInputSignal, TestSpec_t structTestSpec) {
    ppfInputSignal = new float *[structTestSpec.iNumChannels];

    // init to 0
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        ppfInputSignal[c] = new float[structTestSpec.iTestSignalLength];
    }
    // put a 1 at start for impulse
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        for (int i = 0; i < structTestSpec.iTestSignalLength; i++){
            ppfInputSignal[c][i] = 1;
        }
    }

    if (structTestSpec.bAutoPrint) {
        cout << "Test Signal: " << endl;
        for (int c = 0; c < structTestSpec.iNumChannels; c++) {
            for (int i = 0; i < structTestSpec.iTestSignalLength; i++) {
                cout << ppfInputSignal[c][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

/*
 * Debugging function for printing out the output buffer
 */
void printOutput(float**& ppfOutputSignal, TestSpec_t structTestSpec){
    cout << "Current Output Signal: " << endl;
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        for (int i = 0; i < structTestSpec.iTestSignalLength; i++) {
            cout << ppfOutputSignal[c][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * Tests if a simple unit impulse through the FIR yields a delayed `1*iGain` at a location offset by `iDelay`
 */
void testImpulseOutputFIR(float**& ppfOutputSignal, TestSpec_t structTestSpec) {
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        assert(ppfOutputSignal[c][structTestSpec.iDelay] = structTestSpec.fGain*ppfOutputSignal[c][0]);
    }
}

/*
 * Tests if a simple unit impulse through the IIR yields a delayed `1*iGain` at a location offset by `iDelay`, and a subsequent location
 */
void testImpulseOutputIIR(float**& ppfOutputSignal, int iNumChannels, int iDelay, float fGain, float fMaxDelay){
    for (int c = 0; c < iNumChannels; c++) {
        assert(ppfOutputSignal[c][iDelay] = fGain * ppfOutputSignal[c][0]);
        assert(ppfOutputSignal[c][2*iDelay] = fGain * ppfOutputSignal[c][iDelay]);
        assert(ppfOutputSignal[c][3*iDelay] = fGain * ppfOutputSignal[c][2*iDelay]);
    }
}

void processCombFilter(CCombFilterIf*& pInstance, float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec){
    pInstance->init(CCombFilterIf::kCombFIR, structTestSpec.fMaxDelay, structTestSpec.fSamplingRate, structTestSpec.iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, structTestSpec.iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, structTestSpec.fGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, structTestSpec.iTestSignalLength);
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

}

