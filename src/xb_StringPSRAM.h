/*
 WStringPSRAM.h - StringPSRAM library for Wiring & Arduino
 ...mostly rewritten by Paul Stoffregen...
 Copyright (c) 2009-10 Hernando Barragan.  All right reserved.
 Copyright 2011, Paul Stoffregen, paul@pjrc.com

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef xb_StringPSRAM_class_h
#define xb_StringPSRAM_class_h
#ifdef __cplusplus

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pgmspace.h>

// An inherited class for holding the result of a concatenation.  These
// result objects are assumed to be writable by subsequent concatenations.
class StringPSRAMSumHelper;

// an abstract class used as a means to proide a unique pointer type
// but really has no body
class __FlashStringPSRAMHelper;
#define F(string_literal) (reinterpret_cast<const __FlashStringPSRAMHelper *>(PSTR(string_literal)))

// The string class
class StringPSRAM
{
    // use a function pointer to allow for "if (s)" without the
    // complications of an operator bool(). for more information, see:
    // http://www.artima.com/cppsource/safebool.html
    typedef void (StringPSRAM::*StringPSRAMIfHelperType)() const;
    void StringPSRAMIfHelper() const
    {
    }

public:
    // constructors
    // creates a copy of the initial value.
    // if the initial value is null or invalid, or if memory allocation
    // fails, the string will be marked as invalid (i.e. "if (s)" will
    // be false).
    StringPSRAM(const char *cstr = "");
    StringPSRAM(const StringPSRAM &str);
    StringPSRAM(const __FlashStringPSRAMHelper *str) : StringPSRAM(reinterpret_cast<const char *>(str)) {};
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    StringPSRAM(StringPSRAM &&rval);
    StringPSRAM(StringPSRAMSumHelper &&rval);
#endif
    explicit StringPSRAM(char c);
    explicit StringPSRAM(unsigned char, unsigned char base = 10);
    explicit StringPSRAM(int, unsigned char base = 10);
    explicit StringPSRAM(unsigned int, unsigned char base = 10);
    explicit StringPSRAM(long, unsigned char base = 10);
    explicit StringPSRAM(unsigned long, unsigned char base = 10);
    explicit StringPSRAM(float, unsigned char decimalPlaces = 2);
    explicit StringPSRAM(double, unsigned char decimalPlaces = 2);
    ~StringPSRAM(void);

    // memory management
    // return true on success, false on failure (in which case, the string
    // is left unchanged).  reserve(0), if successful, will validate an
    // invalid string (i.e., "if (s)" will be true afterwards)
    unsigned char reserve(unsigned int size);
    inline unsigned int length(void) const
    {
        if(buffer) {
            return len;
        } else {
            return 0;
        }
    }

    // creates a copy of the assigned value.  if the value is null or
    // invalid, or if the memory allocation fails, the string will be
    // marked as invalid ("if (s)" will be false).
    StringPSRAM & operator =(const StringPSRAM &rhs);
    StringPSRAM & operator =(const char *cstr);
    StringPSRAM & operator = (const __FlashStringPSRAMHelper *str);
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    StringPSRAM & operator =(StringPSRAM &&rval);
    StringPSRAM & operator =(StringPSRAMSumHelper &&rval);
#endif

    // concatenate (works w/ built-in types)

    // returns true on success, false on failure (in which case, the string
    // is left unchanged).  if the argument is null or invalid, the
    // concatenation is considered unsucessful.
    unsigned char concat(const StringPSRAM &str);
    unsigned char concat(const char *cstr);
    unsigned char concat(char c);
    unsigned char concat(unsigned char c);
    unsigned char concat(int num);
    unsigned char concat(unsigned int num);
    unsigned char concat(long num);
    unsigned char concat(unsigned long num);
    unsigned char concat(float num);
    unsigned char concat(double num);
    unsigned char concat(const __FlashStringPSRAMHelper * str);

    // if there's not enough memory for the concatenated value, the string
    // will be left unchanged (but this isn't signalled in any way)
    StringPSRAM & operator +=(const StringPSRAM &rhs)
    {
        concat(rhs);
        return (*this);
    }
    StringPSRAM & operator +=(const char *cstr)
    {
        concat(cstr);
        return (*this);
    }
    StringPSRAM & operator +=(char c)
    {
        concat(c);
        return (*this);
    }
    StringPSRAM & operator +=(unsigned char num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator +=(int num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator +=(unsigned int num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator +=(long num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator +=(unsigned long num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator +=(float num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator +=(double num)
    {
        concat(num);
        return (*this);
    }
    StringPSRAM & operator += (const __FlashStringPSRAMHelper *str)
    {
        concat(str);
        return (*this);
    }

    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, const StringPSRAM &rhs);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, const char *cstr);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, char c);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, unsigned char num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, int num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, unsigned int num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, long num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, unsigned long num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, float num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, double num);
    friend StringPSRAMSumHelper & operator +(const StringPSRAMSumHelper &lhs, const __FlashStringPSRAMHelper *rhs);

    // comparison (only works w/ StringPSRAMs and "strings")
    operator StringPSRAMIfHelperType() const
    {
        return buffer ? &StringPSRAM::StringPSRAMIfHelper : 0;
    }
    int compareTo(const StringPSRAM &s) const;
    unsigned char equals(const StringPSRAM &s) const;
    unsigned char equals(const char *cstr) const;
    unsigned char operator ==(const StringPSRAM &rhs) const
    {
        return equals(rhs);
    }
    unsigned char operator ==(const char *cstr) const
    {
        return equals(cstr);
    }
    unsigned char operator !=(const StringPSRAM &rhs) const
    {
        return !equals(rhs);
    }
    unsigned char operator !=(const char *cstr) const
    {
        return !equals(cstr);
    }
    unsigned char operator <(const StringPSRAM &rhs) const;
    unsigned char operator >(const StringPSRAM &rhs) const;
    unsigned char operator <=(const StringPSRAM &rhs) const;
    unsigned char operator >=(const StringPSRAM &rhs) const;
    unsigned char equalsIgnoreCase(const StringPSRAM &s) const;
    unsigned char equalsConstantTime(const StringPSRAM &s) const;
    unsigned char startsWith(const StringPSRAM &prefix) const;
    unsigned char startsWith(const StringPSRAM &prefix, unsigned int offset) const;
    unsigned char endsWith(const StringPSRAM &suffix) const;

    // character acccess
    char charAt(unsigned int index) const;
    void setCharAt(unsigned int index, char c);
    char operator [](unsigned int index) const;
    char& operator [](unsigned int index);
    void getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index = 0) const;
    void toCharArray(char *buf, unsigned int bufsize, unsigned int index = 0) const
    {
        getBytes((unsigned char *) buf, bufsize, index);
    }
    const char * c_str() const
    {
        return buffer;
    }

    // search
    int indexOf(char ch) const;
    int indexOf(char ch, unsigned int fromIndex) const;
    int indexOf(const StringPSRAM &str) const;
    int indexOf(const StringPSRAM &str, unsigned int fromIndex) const;
    int lastIndexOf(char ch) const;
    int lastIndexOf(char ch, unsigned int fromIndex) const;
    int lastIndexOf(const StringPSRAM &str) const;
    int lastIndexOf(const StringPSRAM &str, unsigned int fromIndex) const;
    StringPSRAM substring(unsigned int beginIndex) const
    {
        return substring(beginIndex, len);
    }
    ;
    StringPSRAM substring(unsigned int beginIndex, unsigned int endIndex) const;

    // modification
    void replace(char find, char replace);
    void replace(const StringPSRAM& find, const StringPSRAM& replace);
    void remove(unsigned int index);
    void remove(unsigned int index, unsigned int count);
    void toLowerCase(void);
    void toUpperCase(void);
    void trim(void);

    // parsing/conversion
    long toInt(void) const;
    float toFloat(void) const;
    double toDouble(void) const;

protected:
    char *buffer;	        // the actual char array
    unsigned int capacity;  // the array length minus one (for the '\0')
    unsigned int len;       // the StringPSRAM length (not counting the '\0')
protected:
    void init(void);
    void invalidate(void);
    unsigned char changeBuffer(unsigned int maxStrLen);
    unsigned char concat(const char *cstr, unsigned int length);

    // copy and move
    StringPSRAM & copy(const char *cstr, unsigned int length);
    StringPSRAM & copy(const __FlashStringPSRAMHelper *pstr, unsigned int length);
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    void move(StringPSRAM &rhs);
#endif
};

class StringPSRAMSumHelper: public StringPSRAM
{
public:
    StringPSRAMSumHelper(const StringPSRAM &s) :
        StringPSRAM(s)
    {
    }
    StringPSRAMSumHelper(const char *p) :
        StringPSRAM(p)
    {
    }
    StringPSRAMSumHelper(char c) :
        StringPSRAM(c)
    {
    }
    StringPSRAMSumHelper(unsigned char num) :
        StringPSRAM(num)
    {
    }
    StringPSRAMSumHelper(int num) :
        StringPSRAM(num)
    {
    }
    StringPSRAMSumHelper(unsigned int num) :
        StringPSRAM(num)
    {
    }
    StringPSRAMSumHelper(long num) :
        StringPSRAM(num)
    {
    }
    StringPSRAMSumHelper(unsigned long num) :
        StringPSRAM(num)
    {
    }
    StringPSRAMSumHelper(float num) :
        StringPSRAM(num)
    {
    }
    StringPSRAMSumHelper(double num) :
        StringPSRAM(num)
    {
    }
};

#endif  // __cplusplus
#endif  // StringPSRAM_class_h
