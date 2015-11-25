/** \addtogroup TestCases
 *  @{
 */

#include <iostream>
#include <Graphics/RenderEngine.h>
#include <Graphics/Renderer/OGLRenderer.h>
#include "gtest/gtest.h"


TEST(Renderer, renderer_initialization)
{
    cac::RenderEngine<cac::OGLRenderer> renderEngine;
    EXPECT_TRUE(renderEngine.initialize(cac::WindowDesc("TEST", 800 ,600, false)));
}



/** @}*/