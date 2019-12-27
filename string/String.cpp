//
//  main.cpp
//  string
//
//  Created by Olga Chernova on 04/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#include <iostream>
#include <utility>
#include <algorithm>

#include "String.h"

String::String(char c, size_t count){
    this->word = new char[count];
    for (int i = 0; i < count; ++i) {
        word[i] = c;
    }
    (*this).sizeOfArray = count;
}

size_t String::sizeofmystr() const{
    return sizeOfArray;
}
size_t String::length() const{
    return sizeOfArray;
}

char& String::at(size_t pos) const {
    return this->word[pos];
}

const char& String::operator [] (size_t pos) const{
    return this->at(pos);
}
const char& String::front() const{
    return this->at(0);
}
const char& String::back() const{
    return this->at(this->sizeOfArray - 1);
}
char* String::data() const{//вернуть массив чаров
    return this->word;
}

char* String::c_str() const{
    char* temp = new char[this->sizeOfArray];
    for (int i = 0; i < this->sizeOfArray; ++i) {
        temp[i] = this->word[i];
    }
    return temp;
}
bool String::empty() const{
    return !(this->sizeOfArray);
}

void String::clear(){
    for (int index = 0; index < this->sizeofmystr(); ++index) {
        this->word = 0;
    }
}

void String::push_back(char needToAdd) {
    int* toCopy = new int[this->sizeofmystr()];
    
    for(int i = 0; i < this->sizeofmystr(); i++){
        toCopy[i] = this->word[i];
    }
    delete [] this->word;
    this->word = new char[this->sizeofmystr() + 1];
    for(int i = 0; i < this->sizeofmystr(); i++){
        this->word[i] = toCopy[i];
    }
    delete [] toCopy;
    this->word[this->sizeofmystr()] = needToAdd;
    ++(this->sizeOfArray);
}
void String::insert(char toInsert, size_t count, int index) {
    String temp1 = String();
    
    for (int index = 0; index < this->sizeofmystr(); ++index) {
        temp1.push_back(this->word[index]);
    }
}

String& String::operator += (const String &other)
{
    for (int i = 0; i < other.sizeofmystr(); ++i) {
        this->push_back(other[i]);
    }
    return *this;
}

std::ostream& operator << (std::ostream& stream, const String& out)
{
    for (int i = 0; i < out.length(); ++i) {
        stream  << out[i];
    }
    return stream;
}

