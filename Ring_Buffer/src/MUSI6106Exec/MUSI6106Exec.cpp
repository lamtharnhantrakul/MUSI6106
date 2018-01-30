
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "RingBuffer.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();


// Declare test functions
void generateTestSignal(float*&, int, bool);
void testPutGet(CRingBuffer<float> * , float );
void testRingBufferRead(CRingBuffer<float> *, float *, int, int);
void testOffset(CRingBuffer<float> *, float *, int,  int, int);

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
    int                     iTestSignalLength   = 16;
    int                     iRingBufferLength    = 8;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    time                    = clock();



    //////////////////////////////////////////////////////////////////////////////
    // do processing and tests

    // For our tests, we will use the same RingBuffer, but call the `->reset()` method on it


    pCRingBuffer = new CRingBuffer<float>(iRingBufferLength);

    // Test `put()` and `get()` functions
    testPutGet(pCRingBuffer, 100.4);
    testPutGet(pCRingBuffer, 10);

    // Test `setWriteIdx()` and `get(offset)`


    // Generate Test signal
    generateTestSignal(pfTestSignal, iTestSignalLength, true);

    //Test Reading and Writing
    testRingBufferRead(pCRingBuffer, pfTestSignal, iRingBufferLength, iTestSignalLength);

    //Test offset
    testOffset(pCRingBuffer, pfTestSignal, iRingBufferLength, iTestSignalLength, 4);
    testOffset(pCRingBuffer, pfTestSignal, iRingBufferLength, iTestSignalLength, -4);

    /*

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
    */

    cout << "processing done in: \t"    << (clock()-time)*1.F/CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up

    return 0;
}

// Define Test functions
void generateTestSignal(float*& pfTestSignal, int iTestSignalLength, bool bAutoPrint){
    // fill the test signal - a ramp function from 0 - 2047
    pfTestSignal = new float [iTestSignalLength];

    for (int i = 0; i < iTestSignalLength; i++)
    {
        pfTestSignal[i] = i;
    }

    if (bAutoPrint) {
        cout << "----- \n Test Signal: " ;
        for (int i = 0; i < iTestSignalLength; i++)
        {
            cout << pfTestSignal[i] << " ";
        }
        cout << "\n-----" << endl;
    }

}

void testPutGet(CRingBuffer<float> * pCRingBuffer, float value){
    pCRingBuffer->put(value);
    if (pCRingBuffer->get() == value) {
        cout << "`testPutGet` passed using value: " << value << endl;
    } else {
        cout << "`testPutGet` failed using value: " << value << endl;
    }
}

void testRingBufferRead(CRingBuffer<float> * pCRingBuffer, float * pfTestSignal, int iRingBufferLength, int iTestSignalLength)
{
    pCRingBuffer->reset();

    bool arrayPass = true;
    for (int i=0; i<iTestSignalLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);  // increment `write_idx`
        //cout << pCRingBuffer->getPostInc() << ' '; // increment `read_idx`
        if (pCRingBuffer->getPostInc() != pfTestSignal[i]) {
            cout << "`testRingBufferRead()` Failed" << endl;
            arrayPass = false;
            break;
        }
    }
    if (arrayPass){
        cout << "`testRingBufferRead()` individual Read/Write of values Passed" << endl;
    }

    bool bufferPass = true;
    pCRingBuffer->setReadIdx(0); // Need to set `read_idx` back to 0
    for (int i=0; i<iRingBufferLength; i++)
    {
        //cout << pCRingBuffer->getPostInc() << ' ';
        int iTestSignalOffset = iTestSignalLength - iRingBufferLength;  // `iTestSignalOffset` shifts the index
        //cout << pfTestSignal[iTestSignalOffset + i] << ' ';

        if (pCRingBuffer->getPostInc() != pfTestSignal[iTestSignalOffset + i]) {
            cout << "`testRingBufferRead()` Failed" << endl;
            bufferPass = false;
            break;
        }
    }
    if (bufferPass){
        cout << "`testRingBufferRead()` most recent buffer contents Passed " << endl;
    }

}

void testOffset(CRingBuffer<float> * pCRingBuffer, float * pfTestSignal, int iRingBufferLength, int iTestSignalLength, int offset)
{
    pCRingBuffer->reset();

    for (int i=0; i<iTestSignalLength; i++)
    {
        pCRingBuffer->putPostInc(pfTestSignal[i]);  // increment `write_idx`
    }

    pCRingBuffer->setReadIdx(iRingBufferLength/2); // int division
    float val1 = pCRingBuffer->get(-offset);

    pCRingBuffer->setReadIdx((iRingBufferLength/2 - offset) % iRingBufferLength); // I am testing the idea implemented in `setReadIdx()` with the exact idea of modulo
    float val2 = pCRingBuffer->get();

    // This is the hard coded version
    // pCRingBuffer->setReadIdx(4)
    // pCRingBuffer->get(-2)
    //
    // pCRingBuffer->setReadIdx(2)
    // pCRingBuffer->get()

    cout << val1 << "\t" << val2 << endl;

    if (val1 == val2) {
        cout << "`testOffset()` passed" << endl;
    } else {
        cout << "`testOffset()` failed" << endl;
    }
}


void     showClInfo()
{
    cout << "GTCMT MUSI6106 Executable for Ring Buffer Assignment" << endl;
    cout << "(c) 2014-2018 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

