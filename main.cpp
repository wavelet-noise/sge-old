﻿/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define GLM_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gamewindow.h"

#include "sql.h"

int main( int argc, char* const argv[] )
{
    try {
        GameWindow gw;
        gw.Mainloop();
    }
    catch( const std::exception& e )
    {
        LOG(fatal) << e.what();
    }
    catch( ... )
    {
        LOG(fatal) << "unknown exception";
    }

    void* v1 = new GameWindow();
    std::shared_ptr<void> v = std::shared_ptr<void>(v1);
    v.reset();

    return 0;
}
