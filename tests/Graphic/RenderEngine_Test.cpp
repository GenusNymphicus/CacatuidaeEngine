/** \addtogroup TestCases
 *  @{
 */

#include <iostream>
#include <Graphic/RenderEngine.h>
#include <Graphic/OGLRenderer.h>
#include "gtest/gtest.h"


TEST(Renderer, renderer_initialization)
{
    cac::RenderEngine<cac::OGLRenderer> renderEngine;
    EXPECT_TRUE(renderEngine.initialize(cac::WindowDesc("TEST", 800 ,600, false)));
}



/** @}*/