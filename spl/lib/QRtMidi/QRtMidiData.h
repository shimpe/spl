/*-------------------------------------------------------------------------
	    Copyright 2013 Damage Control Engineering, LLC

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*-------------------------------------------------------------------------*/
#ifndef DcMidiData_h__
#define DcMidiData_h__

#include <QDebug>
#include <QMetaType>
#include <QByteArray>
#include <vector>

// Example TimeLine Preset Fetch: F0 00 01 55 12 01 63 hi lo F7
// If p is the 14 bit preset id, then:
// p = (hi<<7)&7F + lo&7F
//     and
// hi=(p>>7)&7F and lo=p&7F
#define getHi(P) ((P>>7)&0x7F)
#define getLo(P) (P&0x7F)
#define mk14 (H,L) ((H)<<7)|((L)&7F)

// Midi data container class that can be used with buffered signal and slots
// That is, signal and slots connecting different threads.
// 
// Note: The meta-type must be registered before the first use of the type.
//       This can be done by calling qRegisterMetaType<DcMidiData>(); in main, 
//       before the first use.
class QRtMidiData
{

public:

    QRtMidiData();
    
    QRtMidiData(const QRtMidiData &other);
    
    ~QRtMidiData();

    QRtMidiData(const char* data);
    
    QRtMidiData(const QByteArray& ba);
    
    QRtMidiData(const QString& st);
    
    QRtMidiData(const qint32 data);

    QRtMidiData(const std::vector<unsigned char>& vector);

    // Append the given integer
    bool appendNum(quint32 x );

    QByteArray numHexToByteArray( quint32 x);


    // Returns the data as a base16 QString
    QString toString() const;
    QString toString(const char ch) const;

    // Returns a std::vector
    std::vector<unsigned char> toStdVector();

    // Returns true if the midi data starts with the given hex string
    // e.g. startsWith("F0");
    bool contains(const char* hex_string) const;
    
    bool contains(const QByteArray&) const;
    bool contains(const QRtMidiData& md) const;

    // Return the midi byte at idx
    inline unsigned char at(int idx) const;

    // Returns the byte count
    inline int length() const;

    // Return the sum of each byte between start and end
    unsigned char sumOfSection(int start, int len);

    // Returns the nth midi byte from the end
    inline unsigned char fromEnd(int nth_from_end);
    
    // Returns true if empty
    inline bool isEmpty() const;

    // Return the sub range specified
    inline QRtMidiData left(int len ) const;
    
    const char* data() const { return _data.data();}

    QByteArray mid ( int pos, int len = -1 ) const;

    QByteArray replace  ( int pos, int len, const QByteArray & after );

    // Copies the midi data into the given std::vector
    void copyToStdVec( std::vector<unsigned char>& vec ) const;

    // Returns the 14 bit MIDI value located at the given offset, if the offset
    // is out of range, the defualtValue is returned
    int get14bit(int offset, int defaultValue = 0 ) const;
    
    // Set the 2 byte 14 bit MIDI value at the given byte offset, 
    // if the offset is out of range, false is returned.
    bool set14bit(int offset, int val);

    // Convert the specified range to an integer.  Each MIDI byte
    // is accumulated as an 8bit value.
    int toInt(int offset, int cnt, int defaultValue = 0 ) const;



/*

    QRtMidiData &prepend(char c)
    {
        _data.prepend(c);
        return *this;
    }

    QRtMidiData &prepend(const char *s)
    {
        _data.prepend(s);
        return *this;
    }

    QRtMidiData &prepend(const QByteArray &a)
    {
        _data.prepend(a);
        return *this;
    }
 */

    QRtMidiData &append(char c)
    {
        _data.append(c);
        return *this;
    }
    QRtMidiData &append(const char *s)
    {
        
        append(QRtMidiData(s));
        return *this;
    }
//     QRtMidiData &append(const QByteArray &a)
//     {
//         _data.append(a);
//         return *this;
//     }
    
    QRtMidiData &append(const QRtMidiData &a)
    {
        _data.append(a.toByteArray());
        return *this;
    }


    bool operator==(const QRtMidiData &d1) const
    { 
        return d1._data == _data; 
    }

    bool operator!=(const QRtMidiData &d1)
    { 
        return d1._data != _data; 
    }


    bool operator==(const QByteArray &a)
    { 
        return a == _data; 
    }

     bool operator==(const char* midistr)
     {
         QRtMidiData t = QRtMidiData(midistr);
         return _data == t._data;
     }


//      QRtMidiData &operator+=(char c);
//      QRtMidiData &operator+=(const char *s);
//      QRtMidiData &operator+=(const QRtMidiData &a
//      inline QRtMidiData &QRtMidiData::operator+=(char c)
//      { return append(c); }
// 
//      inline QRtMidiData &QRtMidiData::operator+=(const char *s)
//      { return append(s); }
     
//      inline QRtMidiData &QRtMidiData::operator+=(const QByteArray &a)
//      { return append(a); }
//      
//      inline QRtMidiData &QRtMidiData::operator+=(const QRtMidiData &a)
//      { 
//          return a.append(a); 
//      }
// 
// 
// 
//      QRtMidiData operator+(const QByteArray &ba)
//       { 
//           _data += ba;
//           return *this;
//       }

//      QRtMidiData &operator+=(const QRtMidiData &a)
//      {
//          this->append(a);
//          return *this;
//      }
// 
//      QRtMidiData &operator+=(const QByteArray &ba)
//      {
//          this->_data.append(ba);
//          return *this;
//      }

//      QRtMidiData operator+(const QRtMidiData &md)
//      { 
//          _data += md._data;
//          return *this;
//      }
//      
//      QRtMidiData operator+(const char* s)
//      { 
//          append(s);
//          return *this;
//      }

     //      inline const QRtMidiData operator+(const QRtMidiData &a1, const char *a2)
//      { return QRtMidiData(a1) += a2; }
//      inline const QRtMidiData operator+(const QRtMidiData &a1, char a2)
//      { return QRtMidiData(a1) += a2; }
//      inline const QRtMidiData operator+(const char *a1, const QRtMidiData &a2)
//      { return QByteArray(a1) += a2; }
//      inline const QRtMidiData operator+(char a1, const QRtMidiData &a2)
//      { return QRtMidiData(&a1, 1) += a2; }
//
     QByteArray toByteArray() const { return _data; }
     QByteArray toByteArray(const char ch) const
     {
         QString str = toString(ch);
         const std::string stdstr = str.toStdString();
         return QByteArray(stdstr.c_str());
     }

     void clear();
      
     void setData(const char* fmt, ...);
     void setText( const char* data );
     //void setData(const QString& fmt, ...);

private:
    
    void vSetData( const char* fmt, va_list args );
    
    // Returns true if the string starts with '0x'
    bool is0xHexStr( QString &str );

    

    // TODO: Use std::vector, the lower MIDI io does.  Does it matter?
    QByteArray _data;
};

inline const QRtMidiData  operator+(const QRtMidiData  &md1, const QRtMidiData  &md2)
{ 
    return QRtMidiData(md1.toByteArray() + md2.toByteArray()); 
}

inline const QRtMidiData  operator+(const QRtMidiData  &a1, const char* c)
{ 
    return QRtMidiData(a1.toByteArray() + c); 
}

inline const QRtMidiData  operator+(const QRtMidiData  &a1, const QByteArray  &a2)
{ 
    return QRtMidiData(QRtMidiData(a1.toByteArray() + a2)); 
}
//-------------------------------------------------------------------------
unsigned char QRtMidiData::fromEnd( int n)
{
    // Return the byte n from the end
    if(length() > n && n >= 0)
    {
        return _data.at(length()-n);
    }
    else
    {
        // TODO: throw an error
        return 0xFF;
    }
}

//-------------------------------------------------------------------------
unsigned char QRtMidiData::at( int idx ) const
{
    return _data.at(idx);
}

//-------------------------------------------------------------------------
int QRtMidiData::length() const
{
    return _data.size();
}

//-------------------------------------------------------------------------
bool QRtMidiData::isEmpty() const
{
    return _data.isEmpty();
}


Q_DECLARE_METATYPE(QRtMidiData);

#endif // DcMidiData_h__

