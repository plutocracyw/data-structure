/*******************************************************************************
* FileName:         MyString.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2023/03/23 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #5
*                   完成程度：
*                       简要说一下自己写了多少，完成了哪些函数
*******************************************************************************/
#include <cstdio>
#include <cstdlib>
#include "MyString.h"


MyString::MyString(const char* s){
    if (s) {
        len = 0;
        while (s[len] != '\0') {
            len++;
        }
        str = new char[len + 1];
        for (int i = 0; i < len; i++) {
            str[i] = s[i];
        }
        str[len] = '\0';
    } else {
        str = new char[1];
        str[0] = '\0';
        len = 0;
    }
}

MyString::~MyString(){

}

int MyString::length() const{
    return len;

}

void MyString::replace(const char* replace, int loc){
    if(loc < 0 || loc >len){
        return;
    }
    if(!replace){
        return;
    }
    int replacement_len = 0;
    while(replace[replacement_len] != '\0'){
        replacement_len++;
    }
    char* new_str = new char[loc + replacement_len + 1];
    for (int i = 0; i < loc;i++){
        new_str[i] = str[i];
    }
    for (int i = 0; i < replacement_len; i++) {
        new_str[loc + i] = replace[i];
    }
    new_str[loc + replacement_len] = '\0';
    delete[] str;
    str = new_str;
    len = loc + replacement_len;
}

int MyString::find(const char* str) const{
    if(!str || str[0] == '\0'){
        return -1;
    }
    int search_len = 0;
    while(str[search_len] != '\0'){
        search_len++;
    }

    if(search_len>len){
        return -1;
    }

    for(int i=0;i<=len - search_len;i++){
        bool match = true;
        for(int j=0;j<search_len;j++){
            if(this->str[i + j] != str[j]){
                match = false;
                break;
            }
        }
        if(match){
            return i;
        }
    }
    return -1;
}

const char* MyString::c_string() const{
    return str;
}