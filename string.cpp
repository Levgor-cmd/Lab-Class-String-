#include <cstddef>
#include <iostream>

class String
{
public:
    ~String()
    {
        delete[] Data;
    }

    String()
    {
        Data = nullptr;
    }

    String(const String& rhs)
    {
        int len = rhs.Size();
        Data = new char[len + 1];
        for (int j = 0; j < len; j++)
        {
            Data[j] = rhs.Data[j];
        }
        Data[len] = '\0';
    }

    String(const char* data)
    {
        if (data == nullptr)
        {
            Data = nullptr;
            return;
        }
        int i = 0;
        while (data[i] != '\0')
        {
            i++;
        }
        Data = new char[i + 1];
        for (int j = 0; j < i; j++)
        {
            Data[j] = data[j];
        }
        Data[i] = '\0';
    }

    String& operator=(const String& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        delete[] this->Data;

        int len = rhs.Size();
        Data = new char[len + 1];
        for (int j = 0; j < len; j++)
        {
            Data[j] = rhs.Data[j];
        }
        Data[len] = '\0';

        return *this;
    }

    String& operator+=(const String& rhs)
    {
        int thisLen = Size();
        int rhsLen = rhs.Size();

        if (rhsLen == 0)
        {
            return *this;
        }

        int totalLength = thisLen + rhsLen;
        char* newData = new char[totalLength + 1];

        for (int i = 0; i < thisLen; i++)
        {
            newData[i] = this->Data[i];
        }
        for (int i = 0; i < rhsLen; i++)
        {
            newData[thisLen + i] = rhs.Data[i];
        }
        newData[totalLength] = '\0';

        delete[] this->Data;
        this->Data = newData;
        return *this;
    }

    String& operator*=(unsigned int m)
    {
        if (m == 0)
        {
            delete[] this->Data;
            this->Data = nullptr;
            return *this;
        }

        int len = Size();
        if (len == 0)
        {
            return *this;
        }

        char* newData = new char[len * m + 1];
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < len; k++)
            {
                newData[j * len + k] = this->Data[k];
            }
        }
        newData[len * m] = '\0';

        delete[] this->Data;
        this->Data = newData;
        return *this;
    }

    bool operator==(const String& rhs) const
    {
        int thisLen = Size();
        int rhsLen = rhs.Size();

        if (thisLen != rhsLen)
        {
            return false;
        }

        for (int i = 0; i < thisLen; i++)
        {
            if (this->Data[i] != rhs.Data[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator<(const String& rhs) const
    {
        int thisLen = Size();
        int rhsLen = rhs.Size();
        int minLen = (thisLen < rhsLen) ? thisLen : rhsLen;

        for (int i = 0; i < minLen; i++)
        {
            if (this->Data[i] != rhs.Data[i])
            {
                return (int)this->Data[i] < (int)rhs.Data[i];
            }
        }

        return thisLen < rhsLen;
    }

    size_t Find(const String& substr) const
    {
        int DataLength = Size();
        int subLength = substr.Size();

        if (subLength == 0 || DataLength < subLength)
        {
            return -1;
        }

        for (int k = 0; k <= DataLength - subLength; k++)
        {
            bool found = true;
            for (int i = 0; i < subLength; i++)
            {
                if (this->Data[k + i] != substr.Data[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return k;
            }
        }
        return -1;
    }

    void Replace(char oldSymbol, char newSymbol)
    {
        int length = Size();
        if (length == 0)
        {
            return;
        }

        char* newData = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            if (this->Data[i] != oldSymbol)
            {
                newData[i] = this->Data[i];
            }
            else
            {
                newData[i] = newSymbol;
            }
        }
        newData[length] = '\0';

        delete[] this->Data;
        this->Data = newData;
    }

    size_t Size() const
    {
        if (Data == nullptr)
        {
            return 0;
        }
        int length = 0;
        while (Data[length] != '\0')
        {
            length++;
        }
        return length;
    }

    bool Empty() const
    {
        return Data == nullptr || Data[0] == '\0';
    }

    char operator[](size_t index) const
    {
        int length = Size();
        if (index >= length)
        {
            std::cerr << "Error: incorrect index!" << std::endl;
            return '\0';
        }
        else
        {
            return this->Data[index];
        }
    }

    char& operator[](size_t index)
    {
        int length = Size();
        if (index >= length)
        {
            std::cerr << "Error: incorrect index!" << std::endl;
            static char zero_t = '\0';
            return zero_t;
        }
        else
        {
            return this->Data[index];
        }
    }

    void RTrim(char symbol)
    {
        int quantityOfTrim = 0;
        int length = Size();
        if (length == 0)
        {
            return;
        }
        int lastIndex = length - 1;
        while (lastIndex >= 0 && this->Data[lastIndex] == symbol)
        {
            quantityOfTrim++;
            lastIndex--;
        }
        if (quantityOfTrim == 0)
        {
            return;
        }
        char* newData = new char[length - quantityOfTrim + 1];
        for (int i = 0; i < length - quantityOfTrim; i++)
        {
            newData[i] = this->Data[i];
        }
        newData[length - quantityOfTrim] = '\0';
        delete[] this->Data;
        this->Data = newData;
    }

    void LTrim(char symbol)
    {
        int quantityOfTrim = 0;
        int length = Size();
        if (length == 0)
        {
            return;
        }
        int firstIndex = 0;
        while (firstIndex < length && this->Data[firstIndex] == symbol)
        {
            quantityOfTrim++;
            firstIndex++;
        }
        if (quantityOfTrim == 0)
        {
            return;
        }
        char* newData = new char[length - quantityOfTrim + 1];
        for (int i = 0; i < length - quantityOfTrim; i++)
        {
            newData[i] = this->Data[i + quantityOfTrim];
        }
        newData[length - quantityOfTrim] = '\0';
        delete[] this->Data;
        this->Data = newData;
    }

    void swap(String& oth)
    {
        std::swap(this->Data, oth.Data);
    }

    friend std::ostream& operator<<(std::ostream&, const String&);

private:
    char* Data;
};

String operator+(const String& a, const String& b)
{
    String newString = "";
    newString += a;
    newString += b;
    return newString;
}

String operator*(const String& a, unsigned int b)
{
    String newString = a;
    newString *= b;
    return newString;
}

bool operator!=(const String& a, const String& b)
{
    return !(a == b);
}

bool operator>(const String& a, const String& b)
{
    return b < a;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    if (str.Data != nullptr)
    {
        out << str.Data;
    }
    return out;
}

int main()
{
    return 0;
}
