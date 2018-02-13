
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

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

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
//    if (argc < 2)
//    {
//        cout << "Missing audio input path!";
//        return -1;
//    }
//    else
//    {
//        sInputFilePath = argv[1];
//        sOutputFilePath = sInputFilePath + ".txt";
//    }

    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
//    CAudioFileIf::create(phAudioFile);
//    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
//    if (!phAudioFile->isOpen())
//    {
//        cout << "Wave file open error!";
//        return -1;
//    }
//    phAudioFile->getFileSpec(stFileSpec);

    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
//    hOutputFile.open(sOutputFilePath.c_str(), std::ios::out);
//    if (!hOutputFile.is_open())
//    {
//        cout << "Text file open error!";
//        return -1;
//    }

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
//    ppfAudioData = new float*[stFileSpec.iNumChannels];
//    for (int i = 0; i < stFileSpec.iNumChannels; i++)
//        ppfAudioData[i] = new float[kBlockSize];
//
//    time = clock();
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output file
//    while (!phAudioFile->isEof())
//    {
//        long long iNumFrames = kBlockSize;
//        phAudioFile->readData(ppfAudioData, iNumFrames);
//
//        cout << "\r" << "reading and writing";
//
//        for (int i = 0; i < iNumFrames; i++)
//        {
//            for (int c = 0; c < stFileSpec.iNumChannels; c++)
//            {
//                hOutputFile << ppfAudioData[c][i] << "\t";
//            }
//            hOutputFile << endl;
//        }
//    }
//
//    cout << "\nreading/writing done in: \t" << (clock() - time)*1.F / CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
//    CAudioFileIf::destroy(phAudioFile);
//    hOutputFile.close();
//
//    for (int i = 0; i < stFileSpec.iNumChannels; i++)
//        delete[] ppfAudioData[i];
//    delete[] ppfAudioData;
//    ppfAudioData = 0;

    // simple test

//    float input[2][100], output[2][100];

    float **input, **output;

    input = new float*[2];
    output = new float*[2];
    for (int k = 0; k < 2; ++k) {
        input[k] = new float[100]();
        output[k] = new float[100]();
    }

    input[0][0] = input[1][0] = 1;

//    for (int m = 0; m < 100; ++m) {
//        input[0][m] = input[1][m] = m;
//    }

    int iTestSignalLength = 10;

    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < iTestSignalLength; ++i) {
            cout << input[j][i] << ' ';
        }
        cout << endl;
    }
    CCombFilterIf::create(pInstance);
    pInstance->init(CCombFilterIf::kCombFIR, 4.0f, 1.0f, 2);
    pInstance->setParam(CCombFilterIf::kParamDelay, 4);
    pInstance->setParam(CCombFilterIf::kParamGain, 0.5);
    pInstance->process(input, output, iTestSignalLength);


    for (int l = 0; l < 2; ++l) {
        for (int i = 0; i < iTestSignalLength; ++i) {
            cout << output[l][i] << ' ';
        }
        cout << endl;
    }
    pInstance->reset();
    pInstance->init(CCombFilterIf::kCombIIR, 10.0f, 1.0f, 2);
    pInstance->setParam(CCombFilterIf::kParamDelay, 1);
    pInstance->setParam(CCombFilterIf::kParamGain, 0.5);
    pInstance->process(input, output, 100);

    cout << "********************" << endl;
    for (int l = 0; l < 2; ++l) {
        for (int i = 0; i < 100; ++i) {
            cout << output[l][i] << ' ';
        }
        cout << endl;
    }

    return 0;

}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

