
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"
#include "assert.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();
void    initOutput(float**& ppfOutputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint);
void    generateTestImpulseSignal(float**& ppfInputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint);
void    printOutput(float**& ppfOutputSignal, int iNumChannels, int iTestSignalLength);
void    testImpulseOutputFIR(float**& ppfOutputSignal, int iNumChannels, int delay, float fGain);
void    testImpulseOutputIIR(float**& ppfOutputSignal, int iNumChannels, int iDelay, float fGain, float fMaxDelay);

void    generateTestImpulseTrailSignal(float**& ppfInputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint);
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
    int                     iTestSignalLength = 10;
    float                   **ppfOutputSignal = 0;
    int                     iNumChannels = 2;
    int                     iDelay = 0;
    float                   fGain = 0.0;
    float                   fMaxDelay = 10.0f;

    /////////////////////////////////////////////////////////////////////////////

    initOutput(ppfOutputSignal, iNumChannels, iTestSignalLength, false);
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);

    /*
     * TEST 1: TESTING COMB FILTER WITH UNIT IMPULSE
     */

    generateTestImpulseSignal(ppfInputSignal, iNumChannels, iTestSignalLength, false);

    // Define a simple FIR delay line where the sampling rate is 1 Hz
    CCombFilterIf::create(pInstance);
    iDelay = 4; fGain = 0.8;
    pInstance->init(CCombFilterIf::kCombFIR, fMaxDelay, 1.0f, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, fGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);
    // Check output
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);
    testImpulseOutputFIR(ppfOutputSignal, iNumChannels, iDelay, fGain);

    // Reset output array for next test
    initOutput(ppfOutputSignal, iNumChannels, iTestSignalLength, false);

    // Define a simple IIR delay line where the sampling rate is 1 Hz
    pInstance->init(CCombFilterIf::kCombIIR, fMaxDelay, 1.0f, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, fGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);
    // Check output
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);
    testImpulseOutputIIR(ppfOutputSignal, iNumChannels, iDelay, fGain, fMaxDelay);

    /*
    * TEST 2: TESTING COMB FILTER WITH IMPULSE TRAIL
    */
    generateTestImpulseTrailSignal(ppfInputSignal, iNumChannels, iTestSignalLength, true);

    pInstance->init(CCombFilterIf::kCombFIR, fMaxDelay, 1.0f, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, fGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);

    // Check output
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);
    testImpulseOutputFIR(ppfOutputSignal, iNumChannels, iDelay, fGain);




    /*
    * TEST 3:
    */

}

/*
 * Debugging function to initialize output buffer with dummy zeros
 */
void initOutput(float**& ppfOutputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint) {
    ppfOutputSignal = new float*[iNumChannels];
    for (int c = 0; c < iNumChannels; c++) {
        ppfOutputSignal[c] = new float[iTestSignalLength]();
    }
    if (bAutoPrint) {
        cout << "Init Output Signal: " << endl;
        for (int c = 0; c < iNumChannels; c++) {
            for (int i = 0; i < iTestSignalLength; i++) {
                cout << ppfOutputSignal[c][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void generateTestImpulseSignal(float**& ppfInputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint) {
    ppfInputSignal = new float *[iNumChannels];
    // init to 0
    for (int c = 0; c < iNumChannels; c++) {
        ppfInputSignal[c] = new float[iTestSignalLength]();
    }
    // put a 1 at start for impulse
    for (int c = 0; c < iNumChannels; c++) {
        ppfInputSignal[c][0] = 1;
    }

    if (bAutoPrint) {
        cout << "Test Signal: " << endl;
        for (int c = 0; c < iNumChannels; c++) {
            for (int i = 0; i < iTestSignalLength; i++) {
                cout << ppfInputSignal[c][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void generateTestImpulseTrailSignal(float**& ppfInputSignal, int iNumChannels, int iTestSignalLength, bool bAutoPrint) {
    ppfInputSignal = new float *[iNumChannels];

    // init to 0
    for (int c = 0; c < iNumChannels; c++) {
        ppfInputSignal[c] = new float[iTestSignalLength];
    }
    // put a 1 at start for impulse
    for (int c = 0; c < iNumChannels; c++) {
        for (int i = 0; i < iTestSignalLength; i++){
            ppfInputSignal[c][i] = 1;
        }
    }

    if (bAutoPrint) {
        cout << "Test Signal: " << endl;
        for (int c = 0; c < iNumChannels; c++) {
            for (int i = 0; i < iTestSignalLength; i++) {
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
void printOutput(float**& ppfOutputSignal, int iNumChannels, int iTestSignalLength){
    cout << "Current Output Signal: " << endl;
    for (int c = 0; c < iNumChannels; c++) {
        for (int i = 0; i < iTestSignalLength; i++) {
            cout << ppfOutputSignal[c][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * Tests if a simple unit impulse through the FIR yields a delayed `1*iGain` at a location offset by `iDelay`
 */
void testImpulseOutputFIR(float**& ppfOutputSignal, int iNumChannels, int iDelay, float fGain) {
    for (int c = 0; c < iNumChannels; c++) {
        assert(ppfOutputSignal[c][iDelay] = fGain*ppfOutputSignal[c][0]);
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


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

}

