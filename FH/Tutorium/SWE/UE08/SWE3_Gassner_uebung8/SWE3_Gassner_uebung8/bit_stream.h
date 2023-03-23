//
//  bit_stream.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef bit_stream_h
#define bit_stream_h

#include "bit_code.h"
#include <sstream>

class bit_stream {
public:
    bit_stream();
    virtual ~bit_stream();
    virtual void write(bit_code const& code) = 0;
    virtual void flush() = 0;

};

class bit_binary_stream : public bit_stream {
public:
    bit_binary_stream(std::ostream& stream);
    ~bit_binary_stream() override;
    virtual void write(bit_code const& code) override;
    virtual void flush() override;

private:
    std::ostream& m_stream;
    char m_bit_buffer;
    int m_bit_count;
};

class bit_string_stream : public bit_stream {
public:
    bit_string_stream();
    ~bit_string_stream() override;
    virtual void write(bit_code const& code) override;
    virtual void flush() override;
    std::string str() const;

private:
    std::stringstream m_stream;
};


#endif /* bit_stream_h */
