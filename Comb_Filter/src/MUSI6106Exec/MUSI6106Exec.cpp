
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
    float                   fDelaySecs;
    float                   fGain;
    float                   fMaxDelay;
    float                   fMaxDelaySecs;
    float                   fSamplingRate;
    bool                    bAutoPrint;
} structTestSpec;

void    showClInfo ();
void    initOutput(float**& ppfOutputSignal,TestSpec_t structTestSpec);
void    generateTestImpulseSignal(float**& ppfInputSignal, TestSpec_t structTestSpec);
void    printOutput(float**& ppfOutputSignal, TestSpec_t structTestSpec);
void    testImpulseOutputFIR(float**& ppfOutputSignal, TestSpec_t structTestSpec);
void    testImpulseOutputIIR(float**& ppfOutputSignal, TestSpec_t structTestSpec);

void    generateTestImpulseTrailSignal(float**& ppfInputSignal, TestSpec_t structTestSpec);
void    testImpulseTrailOutputFIR(float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec);
void    testImpulseTrailOutputIIR(float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec);
void    processCombFilter(CCombFilterIf*& pInstance, CCombFilterIf::CombFilterType_t eFilterType, float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec);
/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
        sOutputFilePath;

    static const int        kBlockSize = 1024;

    clock_t                 time = 0;

    float                   **ppfAudioData = 0;
    float                   **ppfAudioDataOutput = 0;

    CAudioFileIf            *phAudioFile = 0;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;

    CCombFilterIf   *pInstance = 0;
    CCombFilterIf::create(pInstance);
    showClInfo();

    float                   **ppfInputSignal = 0;
    float                   **ppfOutputSignal = 0;



    /////////////////////////////////////////////////////////////////////////////
    /*
     *  READING AUDIO FILE
     */
    // parse command line arguments
    if (argc < 2)
    {
        cout << "Missing audio input path!";
        return -1;
    }
    else
    {
        sInputFilePath = argv[1];
        sOutputFilePath = sInputFilePath + ".txt";
    }
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    if (!phAudioFile->isOpen())
    {
        cout << "Wave file open error!";
        return -1;
    }
    phAudioFile->getFileSpec(stFileSpec);
    // open the output text file
    hOutputFile.open(sOutputFilePath.c_str(), std::ios::out);
    if (!hOutputFile.is_open())
    {
        cout << "Text file open error!";
        return -1;
    }
    // allocate memory
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        ppfAudioData[i] = new float[kBlockSize]();

    ppfAudioDataOutput = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        ppfAudioDataOutput[i] = new float[kBlockSize]();

    time = clock();

    // Configure `structTestSpec` with parameters for reading an audio file
    structTestSpec.iNumChannels = 2;
    structTestSpec.fDelaySecs = 0.5F;
    structTestSpec.fGain = 0.5;
    structTestSpec.fMaxDelaySecs = 1.0F;
    structTestSpec.fSamplingRate = stFileSpec.fSampleRateInHz;

    // get audio data and write it to the output file
    CCombFilterIf::create(pInstance);
    pInstance->init(CCombFilterIf::kCombIIR, structTestSpec.fMaxDelaySecs, structTestSpec.fSamplingRate, structTestSpec.iNumChannels);
    pInstance->setParam(CCombFilterIf::kParamGain, structTestSpec.fGain);
    pInstance->setParam(CCombFilterIf::kParamDelay, structTestSpec.fDelaySecs);

    int iii = 1;
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile->readData(ppfAudioData, iNumFrames);

        cout << "\r" << "reading and writing";
        pInstance->process(ppfAudioData, ppfAudioDataOutput, iNumFrames);

        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioDataOutput[c][i] << "\t";
            }
            hOutputFile << endl;
        }
    }

    cout << "\nreading/writing done in: \t" << (clock() - time)*1.F / CLOCKS_PER_SEC << " seconds." << endl;


    /////////////////////////////////////////////////////////////////////////////
    // Configure `structTestSpec` with parameters for reading for test signals
    structTestSpec.iTestSignalLength = 10;
    structTestSpec.iNumChannels = 3;
    structTestSpec.iDelay = 3;
    structTestSpec.fGain = 0.8;
    structTestSpec.fMaxDelay = 10.0f;
    structTestSpec.fSamplingRate = 1.0f;
    structTestSpec.bAutoPrint = false;

    /*
     * TEST 1: IMPULSE SIGNAL
     */
    generateTestImpulseSignal(ppfInputSignal, structTestSpec);

    // Initialize output array to 0
    initOutput(ppfOutputSignal, structTestSpec);
    // Define a simple FIR delay line where the sampling rate is 1 Hz
    processCombFilter(pInstance, CCombFilterIf::kCombFIR, ppfInputSignal, ppfOutputSignal, structTestSpec);
    // Print output
    if (structTestSpec.bAutoPrint) {printOutput(ppfOutputSignal, structTestSpec);}
    // Run the test
    testImpulseOutputFIR(ppfOutputSignal, structTestSpec);

    initOutput(ppfOutputSignal, structTestSpec);
    processCombFilter(pInstance, CCombFilterIf::kCombIIR, ppfInputSignal, ppfOutputSignal, structTestSpec);
    if (structTestSpec.bAutoPrint) {printOutput(ppfOutputSignal, structTestSpec);}
    testImpulseOutputIIR(ppfOutputSignal, structTestSpec);


    /*
     * TEST 2: IMPULSE TRAIL
     */
    generateTestImpulseTrailSignal(ppfInputSignal, structTestSpec);

    initOutput(ppfOutputSignal, structTestSpec);
    processCombFilter(pInstance, CCombFilterIf::kCombFIR, ppfInputSignal, ppfOutputSignal, structTestSpec);
    if (structTestSpec.bAutoPrint) {printOutput(ppfOutputSignal, structTestSpec);}
    testImpulseTrailOutputFIR(ppfInputSignal, ppfOutputSignal, structTestSpec);

    initOutput(ppfOutputSignal, structTestSpec);
    processCombFilter(pInstance, CCombFilterIf::kCombIIR, ppfInputSignal, ppfOutputSignal, structTestSpec);
    if (structTestSpec.bAutoPrint) {printOutput(ppfOutputSignal, structTestSpec);}
    testImpulseTrailOutputIIR(ppfInputSignal, ppfOutputSignal, structTestSpec);

    /*
    * TEST 3:
    */


    //////////////////////////////////////////////////
    /*
     * Cleaning up audio signals
     */

    CAudioFileIf::destroy(phAudioFile);
    hOutputFile.close();

    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        delete[] ppfAudioData[i];
    delete[] ppfAudioData;
    ppfAudioData = 0;

    for (int j = 0; j < stFileSpec.iNumChannels; ++j) {
        delete[] ppfAudioDataOutput[j];
    }
    delete[] ppfAudioDataOutput;
    ppfAudioDataOutput = 0;
    CAudioFileIf::destroy(phAudioFile);
    CCombFilterIf::destroy(pInstance);
    phAudioFile = 0;

    /*
     * Cleaning up test signals
     */

    // Delete Combfilter Interface
    CCombFilterIf::destroy(pInstance);

    // Delete output signal array
    for (int c = 0; c < structTestSpec.iNumChannels; c++)
    {
        delete[] ppfOutputSignal[c];
    }
    delete [] ppfOutputSignal;
    ppfOutputSignal = nullptr;

    // Delete input signal array
    for (int c = 0; c < structTestSpec.iNumChannels; c++)
    {
        delete[] ppfInputSignal[c];
    }
    delete [] ppfInputSignal;
    ppfInputSignal = nullptr;

    // Struct will be automatically deleted when it is no longer in scope
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
        assert(ppfOutputSignal[c][structTestSpec.iDelay] == structTestSpec.fGain*ppfOutputSignal[c][0]);
    }
}

/*
 * Tests if a simple unit impulse produces the first few expected values in the output
 */
void testImpulseOutputIIR(float**& ppfOutputSignal, TestSpec_t structTestSpec) {
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        for (int c = 0; c < structTestSpec.iNumChannels; c++) {
            assert(ppfOutputSignal[c][1 * structTestSpec.iDelay] == structTestSpec.fGain * ppfOutputSignal[c][0]);
            assert(ppfOutputSignal[c][2 * structTestSpec.iDelay] == structTestSpec.fGain * ppfOutputSignal[c][1 * structTestSpec.iDelay]);
        }
    }
}

void testImpulseTrailOutputFIR(float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec) {
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
       for (int i = structTestSpec.iDelay; i < structTestSpec.iTestSignalLength; i++) {
           assert(ppfOutputSignal[c][i] == ppfInputSignal[c][i] + (structTestSpec.fGain*1));
       }
    }
}

void testImpulseTrailOutputIIR(float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec) {
    for (int c = 0; c < structTestSpec.iNumChannels; c++) {
        for (int i = 0; i < structTestSpec.iDelay; i++) {
            int idx = structTestSpec.iDelay;
            assert(ppfOutputSignal[c][idx + i]     == ppfInputSignal[c][idx] + structTestSpec.fGain * ppfOutputSignal[c][i]);
            assert(ppfOutputSignal[c][idx + i + 1] == ppfInputSignal[c][idx + 1] + structTestSpec.fGain * ppfOutputSignal[c][i + 1]);

            assert(ppfOutputSignal[c][2*idx + i]     == ppfInputSignal[c][2*idx] + structTestSpec.fGain * ppfOutputSignal[c][idx]);
            assert(ppfOutputSignal[c][2*idx + i + 1] == ppfInputSignal[c][2*idx + i] + structTestSpec.fGain * ppfOutputSignal[c][idx + i + 1]);
        }

    }
}

/*
 * Process test signal using specified type of comb filter
 */
void processCombFilter(CCombFilterIf*& pInstance, CCombFilterIf::CombFilterType_t eFilterType, float**& ppfInputSignal, float**& ppfOutputSignal, TestSpec_t structTestSpec){
    pInstance->init(eFilterType, structTestSpec.fMaxDelay, structTestSpec.fSamplingRate, structTestSpec.iNumChannels);
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

