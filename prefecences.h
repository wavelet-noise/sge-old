#ifndef PREFECENCES_H
#define PREFECENCES_H
#include "singleton.h"
#include <glm/glm.hpp>
#include <string>

class Prefecences : public Singleton
{
public:
    Prefecences();
    ~Prefecences();

    /*!
     * \brief current window resolution
     */
    glm::vec2 resolution = glm::vec2(800, 600);

    /*!
     * \brief data_dir
     */
    std::string data_dir = "data/";

    /*!
     * \brief texture_data_subdir
     */
    std::string texture_data_subdir = "textures/";
    /*!
     * \brief getTexturesDir
     * \return textures directory name
     */
    std::string getTexturesDir()
    {
        return data_dir + texture_data_subdir;
    }

    /*!
     * \brief shaders_data_subdir
     */
    std::string shaders_data_subdir = "shaders/";
    /*!
     * \brief getShadersDir
     * \return shaders directory name
     */
    std::string getShadersDir()
    {
        return data_dir + shaders_data_subdir;
    }

    /*!
     * \brief shaders_data_subdir
     */
    std::string fonts_data_subdir = "fonts/";
    /*!
     * \brief getFontsDir
     * \return fonts directory name
     */
    std::string getFontsDir()
    {
        return data_dir + fonts_data_subdir;
    }
};

#endif // PREFECENCES_H
