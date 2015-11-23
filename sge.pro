TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
#CONFIG += precompile_header

#PRECOMPILED_HEADER  = helper.h

SOURCES += \
    logger.cpp \
    shader.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    lodepng/lodepng.cpp \
    colorextender.cpp \
    textureatlas.cpp \
    spritebatch.cpp \
    prefecences.cpp \
    gamewindow.cpp \
    gametimer.cpp \
    fpscounter.cpp \
    keyboard.cpp \
    mouse.cpp \
    singleton.cpp \
    font.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_valueiterator.inl \
    main.cpp \
    basicjargshader.cpp \
    ClassicNoise.cpp \
    sge_ui/button.cpp \
    sge_ui/component.cpp \
    sge_ui/graph.cpp \
    sge_ui/label.cpp \
    sge_ui/list_container.cpp \
    sge_ui/panel.cpp \
    sge_ui/vertical_bar.cpp \
    sge_ui/win.cpp \
    sge_ui/wins.cpp \
    colorscheme.cpp \
    gbuffer.cpp \
    resources/resourcecontroller.cpp \
    resources/material.cpp \
    resources/texture.cpp \
    resources/pixmap.cpp \
    sge_perfomance.cpp \
    FrameBuffer.cpp \
    TextureGenerator.cpp \
    random.cpp \
    sge_ui/image_box.cpp \
    sge_ui/dragnumbox.cpp \
    sge_ui/connector.cpp \
    sge_renderbox.cpp \
    sge_texlab_rgb_to_luminance.cpp \
    sge_texlab.cpp \
    sge_texlab_float_selector.cpp \
    sge_texlab_toolbox.cpp \
    sge_texlab_lerp_by_map.cpp \
    helper.cpp \
    resources/umaterial.cpp \
    light.cpp \
    core/uniqueid.cpp \
    sql.cpp \
    sge_ui/treeview.cpp \
    core/tree.cpp \
    resources/texturebase.cpp

VERSION = 0.1.0

win32:LIBS += \
-L$$PWD/3rdparty/lib/ \
-L$$PWD/3rdparty/boost/stage/lib \
-lopengl32 -lglew32 -lglfw3dll -lfreetype -llibboost_serialization-vc120-mt-gd-1_59

unix:LIBS += -lGL -lGLEW -lglfw3 -lfreetype -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lXinerama -lXcursor
unix:INCLUDEPATH += /usr/include/freetype2

win32:INCLUDEPATH += $$PWD/3rdparty/include
win32:INCLUDEPATH += $$PWD/3rdparty/boost

HEADERS += \
    logger.h \
    colorextender.h \
    shader.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/reader.h \
    json/value.h \
    json/writer.h \
    lodepng/lodepng.h \
    textureatlas.h \
    spritebatch.h \
    singleton.h \
    prefecences.h \
    sge.h \
    gamewindow.h \
    gametimer.h \
    fpscounter.h \
    keyboard.h \
    mouse.h \
    font.h \
    utfcpp/utf8.h \
    utfcpp/utf8/checked.h \
    utfcpp/utf8/core.h \
    utfcpp/utf8/unchecked.h \
    basicjargshader.h \
    tangentcalc.h \
    utfcpp/utf8.h \
    helper.h \
    ClassicNoise.h \
    sge_ui/button.h \
    sge_ui/component.h \
    sge_ui/graph.h \
    sge_ui/label.h \
    sge_ui/list_container.h \
    sge_ui/panel.h \
    sge_ui/vertical_bar.h \
    sge_ui/wcontainer.h \
    sge_ui/win.h \
    sge_ui/wins.h \
    colorscheme.h \
    gbuffer.h \
    resources/resourcecontroller.h \
    resources/material.h \
    resources/pixmap.h \
    resources/texture.h \
    sge_perfomance.h \
    resources/error_image.h \
    FrameBuffer.h \
    TextureGenerator.h \
    resources/random_noise.h \
    sge_fielsystem.h \
    random.h \
    sge_ui/image_box.h \
    sge_texture_lab.h \
    sge_ui/dragnumbox.h \
    sge_ui/connector.h \
    sge_texture_lab_float_selector.h \
    sge_renderbox.h \
    sge_texlab_rgb_to_luminance.h \
    sge_texlab_toolbox.h \
    sge_texlab_lerp_by_map.h \
    resources/umaterial.h \
    light.h \
    core/uniqueid.h \
    sql.h \
    sge_ui/treeview.h \
    core/tree.h \
    resources/texturebase.h

DISTFILES += \
    data/fonts/DejaVuSansMono.ttf \
    data/shaders/basic.glsl \
    data/shaders/color.glsl \
    data/shaders/font.glsl \
    data/textures/cone1.png \
    data/shaders/minimal.glsl \
    sge_ui/.git \
    data/shaders/noise.lib.glsl \
    data/shaders/minimal_watertest.glsl \
    data/shaders/height.lib.glsl \
    data/shaders/celltexture.glsl \
    data/shaders/turbulence.lib.glsl \
    data/shaders/testgen1.glsl \
    data/shaders/gradient_builder.glsl \
    data/shaders/float.lib.glsl \
    data/textures/PerlinGrad2D.png \
    data/textures/PerlinPerm2D.png \
    README.md \
    LICENSE.txt \
    data/shaders/rgb_to_luminance.glsl \
    data/shaders/lerp_rgb_map.glsl \
    data/shaders/defered.glsl \
    data/shaders/tone_maping.glsl \
    data/shaders/gausian_blur.glsl \
    data/shaders/extract_glow.glsl \
    data/shaders/gausian_blur2.glsl \
    data/shaders/wireframe.lib.glsl \
    data/shaders/defered_color.glsl \
    data/shaders/normal.glsl \
    data/textures/cur_mouse.png \
    data/textures/cur_resize.png \
    data/shaders/defered_basic_render.glsl \
    data/textures/atlas/blank.png \
    data/shaders/defered_jarg.glsl \
    rapidjson/license.txt
