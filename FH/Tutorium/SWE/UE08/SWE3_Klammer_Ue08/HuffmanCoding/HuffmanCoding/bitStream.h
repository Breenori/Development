#ifndef BIT_STREAM_H
#define BIT_STREAM_H

#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

// bitStream
class bitStream {
public:
    bitStream(std::string fName) {
        
        assert(!fName.empty());
        fileName = fName;
    }
    virtual ~bitStream() = default;
    virtual void readContent() = 0;
    virtual std::string getContent() {
        
        return content;
    }

protected:
    std::string fileName;
    std::string content;

};

// bitStringStream
class bitStringStream : public bitStream {
public:
    bitStringStream(std::string fName) : bitStream{ fName } {
        
        this->readContent();
    }
    void readContent() {
        
        std::ifstream fileStream{ fileName };
        char c;

        while (fileStream.get(c)) {
            
            content += c;
        }

        fileStream.close();
    }

};

#endif // !BIT_STREAM_H