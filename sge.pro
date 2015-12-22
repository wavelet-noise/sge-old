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
    resources/texturebase.cpp \
    core/object.cpp \
    core/dynamicobject.cpp \
    core/objectstatic.cpp \
    core/agent.cpp \
    core/sector.cpp \
    core/level.cpp \
    core/offset.cpp \
    core/db.cpp \
    core/objecthelper.cpp \
    core/agents/chest.cpp \
    core/agents/itemspawner.cpp \
    core/agents/stacked.cpp \
    core/scheme.cpp \
    core/agents/entity.cpp \
    core/agents/itembase.cpp \
    core/agents/referencer.cpp \
    sge_level_debug_info.cpp \
    core/remoteclient.cpp \
    core/remoteserver.cpp \
    core/levelgen.cpp \
    core/agents/tags.cpp \
    core/agents/walkable.cpp \
    core/agents/simpleinteract.cpp \
    core/agents/transparent.cpp \
    core/agents/passsound.cpp \
    core/agents/sound.cpp \
    core/agents/script.cpp

VERSION = 0.1.0

win32:LIBS += \
-L$$PWD/3rdparty/lib/ \
-L$$PWD/3rdparty/boost/stage/lib \
-lopengl32 -lglew32 -lglfw3dll -lfreetype

CONFIG(debug, debug|release) {
    LIBS += -llibboost_log-vc120-mt-gd-1_59 -lsquirreld -lsqstdlibd
}
else {
    LIBS += -llibboost_log-vc120-mt-1_59 -lsquirrel -lsqstdlib
}

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
    resources/texturebase.h \
    core/object.h \
    core/dynamicobject.h \
    core/objectstatic.h \
    core/agent.h \
    core/sector.h \
    core/level.h \
    core/offset.h \
    core/core_const.h \
    rapidjson/internal/pow10.h \
    rapidjson/internal/stack.h \
    rapidjson/internal/strfunc.h \
    rapidjson/document.h \
    rapidjson/filestream.h \
    rapidjson/genericstream.h \
    rapidjson/prettywriter.h \
    rapidjson/rapidjson.h \
    rapidjson/reader.h \
    rapidjson/stringbuffer.h \
    rapidjson/writer.h \
    core/db.h \
    core/objecthelper.h \
    core/agents/chest.h \
    core/agents/itemspawner.h \
    core/agents/stacked.h \
    core/scheme.h \
    core/agents/entity.h \
    core/agents/agentfactory.h \
    core/agents/itembase.h \
    core/serialize.h \
    core/agents/referencer.h \
    core/agents/agents.hpp \
    sge_level_debug_info.h \
    core/remoteclient.h \
    core/remoteserver.h \
    core/levelgen.h \
    core/agents/tags.h \
    core/agents/walkable.h \
    core/agents/simpleinteract.h \
    core/agents/transparent.h \
    core/agents/passsound.h \
    core/agents/sound.h \
    core/agents/script.h

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
    data/shaders/defered_jarg.glsl \
    rapidjson/license.txt \
    data/textures/atlas/asfalt.png \
    data/textures/atlas/asfalt_br.png \
    data/textures/atlas/bath1.png \
    data/textures/atlas/bath2.png \
    data/textures/atlas/bath3.png \
    data/textures/atlas/bath4.png \
    data/textures/atlas/bath5.png \
    data/textures/atlas/bed1.png \
    data/textures/atlas/bed2.png \
    data/textures/atlas/bed3.png \
    data/textures/atlas/bed4.png \
    data/textures/atlas/bed5.png \
    data/textures/atlas/bochka.png \
    data/textures/atlas/briwall1.png \
    data/textures/atlas/bush1.png \
    data/textures/atlas/chair1.png \
    data/textures/atlas/cone1.png \
    data/textures/atlas/cone2.png \
    data/textures/atlas/conk1.png \
    data/textures/atlas/crates1.png \
    data/textures/atlas/crates2.png \
    data/textures/atlas/crates3.png \
    data/textures/atlas/cur_mouse.png \
    data/textures/atlas/cur_resize.png \
    data/textures/atlas/cvet.png \
    data/textures/atlas/cvet1.png \
    data/textures/atlas/cvet2.png \
    data/textures/atlas/cvet3.png \
    data/textures/atlas/dirt1.png \
    data/textures/atlas/door1.png \
    data/textures/atlas/door1_open.png \
    data/textures/atlas/door2.png \
    data/textures/atlas/door2_open.png \
    data/textures/atlas/door3.png \
    data/textures/atlas/door4.png \
    data/textures/atlas/error.png \
    data/textures/atlas/fence_s.png \
    data/textures/atlas/fence_s1.png \
    data/textures/atlas/fence_s2.png \
    data/textures/atlas/fence_w.png \
    data/textures/atlas/fence_w1.png \
    data/textures/atlas/fence_w2.png \
    data/textures/atlas/foodpolka.png \
    data/textures/atlas/foodpolka1.png \
    data/textures/atlas/foodpolka2.png \
    data/textures/atlas/foodpolka3.png \
    data/textures/atlas/foodpolka4.png \
    data/textures/atlas/frame.png \
    data/textures/atlas/fridge1.png \
    data/textures/atlas/fridge2.png \
    data/textures/atlas/glass_hor.png \
    data/textures/atlas/glass_ver.png \
    data/textures/atlas/grass_m.png \
    data/textures/atlas/grass1.png \
    data/textures/atlas/grass2.png \
    data/textures/atlas/grass3.png \
    data/textures/atlas/grass4.png \
    data/textures/atlas/grass5.png \
    data/textures/atlas/grass6.png \
    data/textures/atlas/grass7.png \
    data/textures/atlas/heater.png \
    data/textures/atlas/liqpolka.png \
    data/textures/atlas/liqpolka1.png \
    data/textures/atlas/liqpolka2.png \
    data/textures/atlas/liqpolka3.png \
    data/textures/atlas/mbush1.png \
    data/textures/atlas/mbush2.png \
    data/textures/atlas/mbush3.png \
    data/textures/atlas/medpolka.png \
    data/textures/atlas/medpolka1.png \
    data/textures/atlas/medpolka2.png \
    data/textures/atlas/medpolka3.png \
    data/textures/atlas/medpolka4.png \
    data/textures/atlas/none.png \
    data/textures/atlas/notex.png \
    data/textures/atlas/palka.png \
    data/textures/atlas/plita.png \
    data/textures/atlas/rakovina.png \
    data/textures/atlas/rakovina2.png \
    data/textures/atlas/rakovina3.png \
    data/textures/atlas/rakovina4.png \
    data/textures/atlas/rock1.png \
    data/textures/atlas/rock2.png \
    data/textures/atlas/rock3.png \
    data/textures/atlas/rock4.png \
    data/textures/atlas/s1console1.png \
    data/textures/atlas/s1console2.png \
    data/textures/atlas/s1console3.png \
    data/textures/atlas/s1console4.png \
    data/textures/atlas/s1console5.png \
    data/textures/atlas/s1console6.png \
    data/textures/atlas/s1console7.png \
    data/textures/atlas/s1console8.png \
    data/textures/atlas/s1console9.png \
    data/textures/atlas/s1console10.png \
    data/textures/atlas/s1console11.png \
    data/textures/atlas/s1console12.png \
    data/textures/atlas/s1console13.png \
    data/textures/atlas/s1console14.png \
    data/textures/atlas/s1console15.png \
    data/textures/atlas/s1console16.png \
    data/textures/atlas/s1console17.png \
    data/textures/atlas/s1console18.png \
    data/textures/atlas/safe1.png \
    data/textures/atlas/safe2.png \
    data/textures/atlas/shkaf.png \
    data/textures/atlas/shkaf2.png \
    data/textures/atlas/shkaf3.png \
    data/textures/atlas/steelwall1.png \
    data/textures/atlas/steelwall2.png \
    data/textures/atlas/steelwall3.png \
    data/textures/atlas/steelwall4.png \
    data/textures/atlas/steelwall5.png \
    data/textures/atlas/steelwall6.png \
    data/textures/atlas/table_hor_left.png \
    data/textures/atlas/table_hor_mid.png \
    data/textures/atlas/table_hor_right.png \
    data/textures/atlas/table1.png \
    data/textures/atlas/trashcan.png \
    data/textures/atlas/trashcan1.png \
    data/textures/atlas/tree1.png \
    data/textures/atlas/tree2.png \
    data/textures/atlas/tumba1.png \
    data/textures/atlas/tumba2.png \
    data/textures/atlas/washer.png \
    data/textures/atlas/wearpolka.png \
    data/textures/atlas/wearpolka1.png \
    data/textures/atlas/wearpolka2.png \
    data/textures/atlas/wearpolka3.png \
    data/textures/atlas/wearpolka4.png \
    data/json/core.json \
    data/json/items.json \
    data/textures/atlas/arrow_down.png \
    data/textures/atlas/arrow_up.png \
    data/textures/atlas/asf1.png \
    data/textures/atlas/bag.png \
    data/textures/atlas/bandana1.png \
    data/textures/atlas/banner.png \
    data/textures/atlas/bdec.png \
    data/textures/atlas/biskup.png \
    data/textures/atlas/blank1.png \
    data/textures/atlas/blank2.png \
    data/textures/atlas/blank3.png \
    data/textures/atlas/blank4.png \
    data/textures/atlas/car.png \
    data/textures/atlas/caracter.png \
    data/textures/atlas/collar1.png \
    data/textures/atlas/conk2.png \
    data/textures/atlas/cross1.png \
    data/textures/atlas/dog.png \
    data/textures/atlas/engine1.png \
    data/textures/atlas/floor1.png \
    data/textures/atlas/forest1.png \
    data/textures/atlas/gear.png \
    data/textures/atlas/gem.png \
    data/textures/atlas/gem1.png \
    data/textures/atlas/gem3.png \
    data/textures/atlas/glass1.png \
    data/textures/atlas/glass2.png \
    data/textures/atlas/glass3.png \
    data/textures/atlas/haer1.png \
    data/textures/atlas/haer2.png \
    data/textures/atlas/haer3.png \
    data/textures/atlas/haer4.png \
    data/textures/atlas/hdzombie.png \
    data/textures/atlas/house1.png \
    data/textures/atlas/jeans.png \
    data/textures/atlas/jeans_br.png \
    data/textures/atlas/ljacket.png \
    data/textures/atlas/map.png \
    data/textures/atlas/nothing1.png \
    data/textures/atlas/p1.png \
    data/textures/atlas/pants_mil.png \
    data/textures/atlas/pants_mil2.png \
    data/textures/atlas/pants1.png \
    data/textures/atlas/pfire.png \
    data/textures/atlas/plate1.png \
    data/textures/atlas/plate2.png \
    data/textures/atlas/plate3.png \
    data/textures/atlas/plate4.png \
    data/textures/atlas/rabbit.png \
    data/textures/atlas/redsq.png \
    data/textures/atlas/resp1.png \
    data/textures/atlas/s1shipfl1.png \
    data/textures/atlas/s1shipfl2.png \
    data/textures/atlas/s1shipfl3.png \
    data/textures/atlas/s1shipfl4.png \
    data/textures/atlas/s1shipfl5.png \
    data/textures/atlas/s1shipfl6.png \
    data/textures/atlas/s1shipfl7.png \
    data/textures/atlas/s1shipfl8.png \
    data/textures/atlas/s1shipfl9.png \
    data/textures/atlas/s1shipfl10.png \
    data/textures/atlas/seat1.png \
    data/textures/atlas/transparent_pixel.png \
    data/textures/atlas/t-shirt1.png \
    data/textures/atlas/wheel1.png \
    data/textures/atlas/whitesq.png \
    data/textures/atlas/zombie.png \
    data/textures/atlas/zombie_corp.png \
    data/json/hero.json \
    data/json/sounds.json
