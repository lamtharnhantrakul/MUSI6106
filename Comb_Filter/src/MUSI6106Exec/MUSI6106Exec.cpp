
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
void    testImpulseOutputFIR(float**& ppfOutputSignal, int iNumChannels, int delay, float gain);
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
    float                   iGain = 0.0;

    /////////////////////////////////////////////////////////////////////////////

    initOutput(ppfOutputSignal, iNumChannels, iTestSignalLength, false);
    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);

    generateTestImpulseSignal(ppfInputSignal, iNumChannels, iTestSignalLength, true);

    // Define a simple delay line where the sampling rate is 1 Hz
    CCombFilterIf::create(pInstance);
    iDelay = 1; iGain = 0.8;
    pInstance->init(CCombFilterIf::kCombFIR, 10.0f, 1.0f, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, iGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);

    printOutput(ppfOutputSignal, iNumChannels, iTestSignalLength);
    testImpulseOutputFIR(ppfOutputSignal, iNumChannels, iDelay, iGain);

    initOutput(ppfOutputSignal, iNumChannels, iTestSignalLength, false);

    pInstance->init(CCombFilterIf::kCombFIR, 10.0f, 1.0f, iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamDelay, iDelay);
    pInstance->setParam(CCombFilterIf::kParamGain, iGain);
    pInstance->process(ppfInputSignal, ppfOutputSignal, iTestSignalLength);


    /*
    for (int l = 0; l < 2; ++l) {
        for (int i = 0; i < iTestSignalLength; ++i) {
            cout << ppfOutputSignal[l][i] << ' ';
        }
        cout << endl;
    }
    pInstance->reset();
    pInstance->init(CCombFilterIf::kCombIIR, 10.0f, 1.0f, 2);
    pInstance->setParam(CCombFilterIf::kParamDelay, 1);
    pInstance->setParam(CCombFilterIf::kParamGain, 0.5);
    pInstance->process(ppfInputSignal, ppfOutputSignal, 100);

    cout << "********************" << endl;
    for (int l = 0; l < 2; ++l) {
        for (int i = 0; i < 100; ++i) {
            cout << ppfOutputSignal[l][i] << ' ';
        }
        cout << endl;
    }

    return 0;
    */
}

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
 * Tests if a simple unit impulse through the delay line yields a delayed `1*iGain` at a location offset by `iDelay`
 */
void testImpulseOutputFIR(float**& ppfOutputSignal, int iNumChannels, int iDelay, float iGain) {
    for (int c = 0; c < iNumChannels; c++) {
        assert(ppfOutputSignal[c][iDelay] = iGain*ppfOutputSignal[c][0]);
    }
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

}

