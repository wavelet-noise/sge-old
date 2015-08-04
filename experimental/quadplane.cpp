#include "quadplane.h"
#include <glm/gtx/transform.hpp>
#include "ClassicNoise.h"
#include "TextureGenerator.h"
#include "sge_ui/wins.h"

QuadPlane::QuadPlane()
{
}

int GetLevel()
{
    return 1;
}

bool QuadPlane::is_terminal() const
{
    return m_parts[0] == nullptr || m_parts[1] == nullptr || m_parts[2] == nullptr || m_parts[3] == nullptr;
}

void QuadPlane::GenerateSubTexture(std::shared_ptr<Material> &t, SphereParamsStorage *parent)
{
    const float res = 256.0f;
    TextureGenerator tg;
    std::shared_ptr<Texture> height_map = std::make_shared<Texture>(glm::vec2{res,res});
    std::shared_ptr<Texture> grad_map = std::make_shared<Texture>(glm::vec2{res,res});


    tg.SetShader(parent->height_shader);
    tg.AddTexture("samplerPerlinPerm2D", parent->noise_map);
    tg.AddTexture("samplerPerlinGrad2D", parent->grad_map);
    tg.SetParams(offset.x);
    tg.SetParams(offset.y);
    tg.SetParams(scale);
    tg.SetResultTexture(height_map);
    tg.RenderOnTempFbo();

    t->height = height_map;

    TextureGenerator grad_gen;
    grad_gen.SetShader(parent->grad_shader);
    grad_gen.AddTexture("height_map", height_map);
    grad_gen.SetResultTexture(grad_map);
    grad_gen.SetParams(height_map->width);
    grad_gen.SetParams(height_map->height);
    grad_gen.SetParams(scale);
    grad_gen.RenderOnTempFbo();

    t->grad = grad_map;
}

void QuadPlane::Render(const Camera &cam,
                       int side,
                       SphereParamsStorage *parent)
{
    if(is_terminal())
    {
        parent->basic->Use();
        //float distance = glm::distance(cam.Position(), parent->center);
        glUniform1f(parent->basic->vars[0], parent->R );
        glUniform1f(parent->basic->vars[1], parent->s );

        if(status == READY)
        {
            terminal_mesh->Render(cam, parent->world);
            float pre_size = 222.f;
            //texture vis
            //WinS::ws->sb->drawQuad(glm::vec2(10,10) + pre_size*offset + glm::vec2(pre_size,0)*(float)(side/2) + glm::vec2(0,pre_size)*(float)(side%2), glm::vec2(pre_size)*scale, *terminal_mesh->material->grad, Color::White);
            //quadtree vis
            //WinS::ws->sb->drawRect(glm::vec2(10,10) + pre_size*offset + glm::vec2(pre_size,0)*(float)(side/2) + glm::vec2(0,pre_size)*(float)(side%2), glm::vec2(pre_size)*scale, glm::vec4(rand()%255/255.0,rand()%255/255.0,rand()%255/255.0,1 ));
        }
        else
        {
            std::shared_ptr<Material> sub_texture = std::make_shared<Material>(*parent->mat);
            GenerateSubTexture(sub_texture, parent);
            sub_texture->texture = parent->mat->texture;
            sub_texture->global_height = parent->mat->global_height;

            terminal_mesh->material = sub_texture;
            terminal_mesh->shader = parent->basic;

            int size = parent->tess_size;
            terminal_mesh->indices.reserve(size * size * 6);
            terminal_mesh->vertices.reserve((size + 1) * (size + 1));
            int co = 0;

            float xs = (-0.5 + offset.x); /*< x координата начала сектора сферы с отступом*/
            float ys = (-0.5 + offset.y); /*< y координата начала сектора сферы с отступом*/
            float dd = ((1.0*scale)/((float)size)); /*< размер 1 квада сектора сферы*/

            //Генерация R=1 сферы. Нормализуемые плоскости имеют координаты [-0.5, 0.5]. В шейдере сфера приводится к радиусу R

            for(int j = -1; j < size + 2; j++)
            {
                for(int i = -1; i < size + 2; i++)
                {
                    VertPosUvUv a;
                    a.position = {xs + i * dd, ys + j * dd, 0.5f};

                    a.position = glm::normalize(a.position);
                    if(j == -1 || i == -1 || j == size + 1 || i == size +1)
                        a.position *= 0.99;

                    a.uv = {i * (1.0/(float)size), j * (1.0/(float)size) };

                    a.uv_glob = {xs + i * dd + 0.5f, ys + j * dd + 0.5f};

                    terminal_mesh->vertices.push_back(a);
                }
            }


            //трансформация вершин сферы в соответствии с матрицей трансформации, заданной при создании объекта сферы
            //матрица трансформации разворачивает части сферы в соответствующие стороны
            for(size_t j = 0; j < terminal_mesh->vertices.size(); j++)
            {
                terminal_mesh->vertices[j].position =
                        glm::vec3(transformation *
                        glm::vec4(terminal_mesh->vertices[j].position, 1));
            }

            subsurface_centers[0] = glm::vec3(transformation *
                                              glm::normalize(glm::vec4(xs + dd * size/4.0,
                                                                       ys + dd * size/4.0,
                                                                       0.5,
                                                                       0)
                                                             )
                                              );
            subsurface_centers[1] = glm::vec3(transformation *
                                              glm::normalize(glm::vec4(xs + dd * size/(3/4.0),
                                                                       ys + dd * size/4.0,
                                                                       0.5,
                                                                       0)
                                                             )
                                              );
            subsurface_centers[2] = glm::vec3(transformation *
                                              glm::normalize(glm::vec4(xs + dd * size/4.0,
                                                                       ys + dd * size/(3/4.0),
                                                                       0.5,
                                                                       0)
                                                             )
                                              );
            subsurface_centers[3] = glm::vec3(transformation *
                                              glm::normalize(glm::vec4(xs + dd * size/(3/4.0),
                                                                       ys + dd * size/(3/4.0),
                                                                       0.5,
                                                                       0)
                                                             )
                                              );

            terminal_mesh->indices = parent->Indeces;
            terminal_mesh->ForgetBind();
            //terminal_mesh->BindExistingIBO(parent->ibo, parent->Indeces.size());
            status = READY;
            terminal_mesh->Render(cam, parent->world);
        }
    }
    else
    {
        for(int i = 0; i < 4; ++i)
            m_parts[i]->Render(cam, side, parent);
    }

}

void QuadPlane::Update(const Camera &camera, float Rs, float eps, int max_divide, SphereParamsStorage *parent)
{
    glm::vec3 cent[4];
    for(int i = 0; i < 4; i++)
    {
        cent[i] = glm::vec3(parent->world * glm::vec4(subsurface_centers[i] + parent->center, 0));
    }

    if(is_terminal() &&
       (glm::distance(cent[0] * Rs, camera.Position()) < eps * scale ||
        glm::distance(cent[1] * Rs, camera.Position()) < eps * scale ||
        glm::distance(cent[2] * Rs, camera.Position()) < eps * scale ||
        glm::distance(cent[3] * Rs, camera.Position()) < eps * scale)
            && level < max_divide)
    {
        m_parts[0] = std::make_shared<QuadPlane>();
        m_parts[0]->terminal_mesh = std::make_shared< UMesh<VertPosUvUv> >();
        m_parts[0]->offset = offset;
        m_parts[0]->scale = scale/2.0f;
        m_parts[0]->level = level + 1;
        m_parts[0]->transformation = transformation;
        m_parts[0]->parent = this;

        m_parts[1] = std::make_shared<QuadPlane>();
        m_parts[1]->terminal_mesh = std::make_shared< UMesh<VertPosUvUv> >();
        m_parts[1]->offset = offset + glm::vec2(0.5f, 0) * scale;
        m_parts[1]->scale = scale/2.0f;
        m_parts[1]->level = level + 1;
        m_parts[1]->transformation = transformation;
        m_parts[1]->parent = this;

        m_parts[2] = std::make_shared<QuadPlane>();
        m_parts[2]->terminal_mesh = std::make_shared< UMesh<VertPosUvUv> >();
        m_parts[2]->offset = offset + glm::vec2(0, 0.5f) * scale;
        m_parts[2]->scale = scale/2.0f;
        m_parts[2]->level = level + 1;
        m_parts[2]->transformation = transformation;
        m_parts[2]->parent = this;

        m_parts[3] = std::make_shared<QuadPlane>();
        m_parts[3]->terminal_mesh = std::make_shared< UMesh<VertPosUvUv> >();
        m_parts[3]->offset = offset + glm::vec2(0.5f, 0.5f) * scale;
        m_parts[3]->scale = scale/2.0f;
        m_parts[3]->level = level + 1;
        m_parts[3]->transformation = transformation;
        m_parts[3]->parent = this;

        //status = ERROR;
    }
    else
        if((glm::distance(cent[0] * Rs, camera.Position()) > eps * 1.1f * scale &&
            glm::distance(cent[1] * Rs, camera.Position()) > eps * 1.1f * scale &&
            glm::distance(cent[2] * Rs, camera.Position()) > eps * 1.1f * scale &&
            glm::distance(cent[3] * Rs, camera.Position()) > eps * 1.1f * scale))
    {
        for(int i = 0; i < 4; ++i)
            m_parts[i] = nullptr;
    }

    if(!is_terminal())
    {
        for(int i = 0; i < 4; ++i)
            m_parts[i]->Update(camera, Rs, eps, max_divide, parent);
    }
}

