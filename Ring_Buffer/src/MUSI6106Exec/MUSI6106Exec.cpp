
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "RingBuffer.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    // You don't need to use an audio file this time, though you can try if you want.
    // std::string             sInputFilePath,                 //!< file paths
    //                         sOutputFilePath;
    // static const int        kBlockSize          = 1024;
    // float                   **ppfAudioData      = 0;
    // CAudioFileIf            *phAudioFile        = 0;
    // CAudioFileIf::FileSpec_t stFileSpec;
    // long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    CRingBuffer<float>      *pCRingBuffer       = 0;
    float                   *pfTestSignal       = 0;
    float                   fGain               = 1.f;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    time                    = clock();


    // fill the test signal - a ramp function from 0 - 2047
    const int iTestSignalLength = 16;
    pfTestSignal = new float [iTestSignalLength];

    for (int i = 0; i < iTestSignalLength; i++)
    {
        pfTestSignal[i] = i;
    }

    cout << "----- \n Test Signal: " ;
    for (int i = 0; i < iTestSignalLength; i++)
    {
         cout << pfTestSignal[i] << " ";
    }
    cout << endl;

    //////////////////////////////////////////////////////////////////////////////
    // do processing and tests

    pCRingBuffer = new CRingBuffer<float>(8);

    // Testing `put()` function
    cout << "------ \n Testing put()" << endl;
    pCRingBuffer->put(100.4);
    cout << "result: " << pCRingBuffer->get() << "\t expected: " << 100.4 << endl; // should be `100.4`

    // Testing `setWriteIdx()` function
    cout << "------ \n Testing get() and setWriteIdx()" << endl;
    pCRingBuffer->setWriteIdx(6);
    pCRingBuffer->put(65);
    cout << "result: " << pCRingBuffer->get(6) << "\t expected: " << 65<< endl; // should be `65`
    cout << "result: " << pCRingBuffer->getWriteIdx() << "\t expected: " << 6 << endl; // should be `6`

    cout << "------ \n Testing putPostInc() and getPostInc()" << endl;
    pCRingBuffer->reset(); // Reset Buffer
    cout << "result: ";
    for (int i=0; i<iTestSignalLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);
        cout << pCRingBuffer->getPostInc() << ' ';
    }
    cout <<endl << "expected: " << "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" << endl;

    cout << "------ \n Testing Contents of Buffer" << endl;
    pCRingBuffer->setReadIdx(0);
    cout << "result: ";
    for (int i=0; i<8; i++)
    {
        cout << pCRingBuffer->getPostInc() << ' ';
    }
    cout << endl << "expected: " << "8 9 10 11 12 13 14 15" << endl;


    cout << "processing done in: \t"    << (clock()-time)*1.F/CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up

    return 0;
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable for Ring Buffer Assignment" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

