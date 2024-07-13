#pragma once
#include "BasicWidget.h"
#include"configure.h"
class PushButton :
    public BasicWidget
{
public:
    PushButton(const std::string& text = "Button", int x = 0, int y = 0, int w = 150, int h = 30);
    void show() override;
   
   
private:
    std::string m_text;
   
    
};

