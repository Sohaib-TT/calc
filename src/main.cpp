#include "app-window.h"
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include "nodes.hpp"
#include "displayBuilder.hpp"
#include <vector>



#ifdef __ANDROID__
extern "C" void slint_main()
#else
int main(int argc, char **argv)
#endif
{   
    auto ui = AppWindow::create();

    auto model = std::make_shared<slint::VectorModel<slint::SharedString>>();
    ui->set_display_list(model);
    

    Node* dsplyHead = new Node();
    dsplyHead->value = "Start";
    Node* cursor = dsplyHead;
    int cursor_index = 0;
    


    ui->on_button_pressed([&](slint::SharedString val) {
        std::string value = std::string(val);
        if (value == "del") {del(&cursor);}
        else if(value == "ac"){printf("ac");}
        else if(value == "="){printf("=");}
        else if(value == "<" || value == ">" ){moveCursor(&cursor,value);}
        else {add(&cursor,value);}
        ui->set_cursor_index(cursor_index);
        //displayCMD(dsplyHead,cursor);
        displaySlint (model,dsplyHead,cursor);
    });


    ui->on_open_docs([]() {
        #if defined(_WIN32)
            system("start readme.html");
        #elif defined(__APPLE__)
            system("open readme.html");
        #else
            system("xdg-open readme.html");
        #endif
    });
    ui->on_open_info([]() {
        #if defined(_WIN32)
            system("start https://github.com/Sohaib-TT/calc");
        #elif defined(__APPLE__)
            system("open https://github.com/Sohaib-TT/calc");
        #else
            system("xdg-open https://github.com/Sohaib-TT/calc");
        #endif
    });

    ui->set_cursor_index(cursor_index);
    ui->run();
}