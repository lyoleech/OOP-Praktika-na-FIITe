//
//  Header.h
//  string
//
//  Created by Olga Chernova on 05/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#ifndef string_h
#define string_h

class String {
private:
    static constexpr size_t npos = 1;
    size_t sizeOfArray = 0;
    char* word;
    static char* addToArray(char toAdd, char* arrayToIncrease, size_t size);
    
public:
    explicit String() = default;
    
    explicit String(char c, size_t count = 0);
    
    explicit String(const String& other,
                    size_t pos,
                    size_t count = npos);
    
    char& at(size_t pos) const;
    
    const char& operator [] (size_t pos) const;
    String& operator += (const String &other);
    const char& front() const;
    const char& back() const;
    char* data() const;
    char* c_str() const;
    void clear();
    void push_back(char needToAdd);
    void insert(char toInsert, size_t count, int index);
    
    bool empty() const;
    
    size_t sizeofmystr() const;
    size_t length() const;
    
    ~String() {
        std::cout << "Array was destroyed" << std::endl;
    }
    
};

std::ostream& operator << (std::ostream& stream, const String& toOutput);

#endif
