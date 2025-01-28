#!/bin/bash
g++ -shared -o libwxinterface.dll wxlib.cpp \
    -I./wxWidgets-3.2.6/include \
    -I./wxWidgets-3.2.6/lib/gcc_dll/mswu \
    -L./wxWidgets-3.2.6/lib/gcc_dll \
    -L/mingw64/lib \
    -lwxmsw32u_core -lwxbase32u -lwxmsw32u_adv -lwxmsw32u_html -lwxmsw32u_gl \
    -lwxpng -lz -lwxjpeg -lwxregexu -lwxexpat \
    -lkernel32 -luser32 -lgdi32 -lole32 -loleaut32 -luuid -lcomctl32 -lcomdlg32 \
    -ladvapi32 -lwinspool -lwsock32
