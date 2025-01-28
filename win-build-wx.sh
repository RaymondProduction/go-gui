#!/bin/bash
cd wxWidgets-3.2.6/build/msw
mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release
