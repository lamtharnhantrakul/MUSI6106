#if !defined(__RingBuffer_hdr__)
#define __RingBuffer_hdr__

#include <cassert>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;

/*! \brief implement a circular buffer of type T
*/
template <class T> 
class CRingBuffer
{
public:
    explicit CRingBuffer (int iBufferLengthInSamples) :
        m_iBuffLength(iBufferLengthInSamples),
        m_iReadIdx(0),                          
        m_iWriteIdx(0),
        m_ptBuff(0)
    {
        assert(iBufferLengthInSamples > 0);

        m_ptBuff        = new T [m_iBuffLength];
        reset();
    }

    virtual ~CRingBuffer ()
    {
        delete [] m_ptBuff;
        m_ptBuff    = 0;
    }

    /*! add a new value of type T to write index
    \param tNewValue the new value
    \return void
    */
    void put(T tNewValue)
    {
        // to be implemented
        m_ptBuff[m_iWriteIdx] = tNewValue;
        // *(m_ptBuff + m_iWriteIdx) = tNewValue;  // NOTE: this is the same thing as above
    }

    //Removed redundant `get()`

    /*! return the current index for writing/put
    \return int
    */
    int getWriteIdx () const
    {
        return m_iWriteIdx;
    }

    /*! move the write index to a new position
    \param iNewWriteIdx: new position
    \return void
    */
    void setWriteIdx (int iNewWriteIdx)
    {
        if (isValidIdx(iNewWriteIdx)) {
            m_iWriteIdx = iNewWriteIdx;
        }
        else
        {
            cout << "Invalid Write Index" << endl ;
        }
    }

    /*! return the current index for reading/get
    \return int
    */
    int getReadIdx () const
    {
        return m_iReadIdx;
    }

    /*! move the read index to a new position
    \param iNewReadIdx: new position
    \return void
    */
    void setReadIdx (int iNewReadIdx)
    {
        if (isValidIdx(iNewReadIdx))
        {
            m_iReadIdx = iNewReadIdx;
        }
        else
        {
            cout << "Invalid Read Index" << endl;
        }
    }

    /*! add a new value of type T to write index and increment write index
    \param tNewValue the new value
    \return void
    */
    void putPostInc (T tNewValue)
    {
        m_ptBuff[m_iWriteIdx] = tNewValue;
        m_iWriteIdx++;
        if (m_iWriteIdx >= m_iBuffLength)
        {
            m_iWriteIdx = 0;  // wrap the index around the ring buffer
        }
    }

    /*! return the value at the current read index and increment the read pointer
    \return type T the value from the read index
    */
    T getPostInc ()
    {
        // to be implemented
        int iTempIdx = m_iReadIdx;
        m_iReadIdx++;
        if (m_iReadIdx >= m_iBuffLength)
        {
            m_iReadIdx = 0;  // wrap the index around the ring buffer
        }
        return  m_ptBuff[iTempIdx];
    }

    /*! return the value at the index with an arbitrary offset
    \param iOffset: read at offset from read index
    \return type T the value from the read index
    */
    T get (int iOffset = 0) const
    {
        if (isValidOffset(iOffset)) {
            // if `iOffset` is positive and greater than `m_iBuffLength`, then "wrap around" to the start of the buffer
            // if `iOffset` is negative and smaller than 0, then "wrap around" to the end of the buffer
            // These two scenarious can be elegantly handled with an add and modulo.
            int iTempIdx = modulo((m_iReadIdx + iOffset), m_iBuffLength);  // c++ `%` did not behave as we expected with negative numbers
            return m_ptBuff[iTempIdx];
        } else {
            cout << "Invalid offset value" << endl;
        }
    }
    
    /*! set buffer content and indices to 0
    \return void
    */
    void reset ()
    {
        memset (m_ptBuff, 0, sizeof(T)*m_iBuffLength);
        m_iReadIdx  = 0;
        m_iWriteIdx = 0;
    }

    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
    \return int
    */
    int getNumValuesInBuffer () const
    {
        return (m_iWriteIdx - m_iReadIdx + m_iBuffLength)%m_iBuffLength;
    }

    /*! returns the length of the internal buffer
    \return int
    */
    int getLength () const
    {
        return m_iBuffLength;
    }
private:
    CRingBuffer ();
    CRingBuffer(const CRingBuffer& that);

    int m_iBuffLength,              //!< length of the internal buffer
        m_iReadIdx,                 //!< current read index
        m_iWriteIdx;                //!< current write index

    T   *m_ptBuff;                  //!< data buffer

    bool isValidIdx(int iIdx)
    {
        if ((iIdx < 0) || (iIdx > m_iBuffLength)) {
            return false;
        }
        else {
            return true;
        }
    }

    bool isValidOffset(T value) const
    {
        if (value >= m_iBuffLength || value <= -m_iBuffLength)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // c++ `%` is a remainder function and does make negative numbers positive!
    int modulo(int x,int N) const
    {
        return (x % N + N) %N;
    }

};
#endif // __RingBuffer_hdr__
