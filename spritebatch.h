#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "texture.h"
#include <string>
#include <memory>
#include "shader.h"
#include "unordered_map"
#include "font.h"

#define SIZE 10000
class SpriteBatch
{
public:

    enum ALIGN{
        ALIGN_LEFT,
        ALIGN_RIGHT,
        ALIGN_CENTER,
        ALIGN_HOR_CENTER
    };

    SpriteBatch();
    ~SpriteBatch();

    glm::vec3 *pos = nullptr;
    glm::vec2 *uv = nullptr;
    glm::vec4 *col = nullptr;

    GLuint *index = nullptr;
    unsigned int cur = 0;

    GLuint current = 0;
    GLuint m_vbo[4];

    glm::mat4 uniform;

    std::shared_ptr<JargShader> font_program = std::make_shared<JargShader>(),
                                basic_program = std::make_shared<JargShader>(),
                                color_program = std::make_shared<JargShader>(),
                                current_program;
    glm::vec2 scis_min, scis_size;

    void setUniform(const glm::mat4 &uni);

    void render();
    void drawRect(const glm::vec2 &loc, const glm::vec2 &size, const glm::vec4 &_col);
    void drawQuad(const glm::vec2 &loc, const glm::vec2 &size, const Texture &tex, const glm::vec4 &col_);
    void drawQuadAtlas(const glm::vec2 &loc, const glm::vec2 &size, const Texture &tex, int apos, const glm::vec4 &col_);
    void drawLine(const glm::vec2 &start, const glm::vec2 &end, float width, const glm::vec4 &color);
    void drawText(const std::string &text, const glm::vec2 &pos, Font *font, const glm::vec4 &col_);
    void drawText(const std::string &text, const glm::vec2 &pos, const glm::vec2 &size, Font *font, const glm::vec4 &col_, ALIGN align);
    void reduceScissor(glm::vec2 loc, glm::vec2 size);
    void resetScissor();
    glm::vec2 measureText(const std::string &text, Font *font);
private:
    glm::vec2 drawText(const std::u32string &text32, float x, float y,
                       Font *font, const glm::vec4 &col_, bool no_draw = false);
    void drawQuadText(const glm::vec2 &loc, const Font::CharInfo &inf, const Texture &tex, const glm::vec4 &color);
};
#endif // SPRITEBATCH_H
