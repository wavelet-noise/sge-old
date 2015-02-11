#include "SphereTesselator.h"
#include "mesh.h"

Mesh* Tesselator::Tesselate(int iters, const Mesh& mesh)
{
    Mesh* m = new Mesh(mesh);
    for (int i = 0; i< iters; ++i)
    {
        auto temp = SubTesselate(*m);
        delete m;
        m = temp;
    }
    return m;
}

Mesh* Tesselator::SphereTesselate(int iters, const Mesh& mesh)
{
    Mesh* m = new Mesh(mesh);
    for (int i = 0; i< iters; ++i)
    {
        auto temp = SphereSubTesselate(*m);
        delete m;
        m = temp;
        temp = nullptr;
    }
    return m;
}

static const int Seed = 123;

inline float Noise2D__(float x, float y) {
    int n = (int) (x + y*57);
    n = (n << 13) ^ n;
    double value = (1.0f - ((n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff)/1073741824.0f);
    return abs(value);
}

inline float Noise2D(float x, float y){
    return Noise2D__(x,y)/10+0.9;
}

inline float SmoothedNoise2D(float x, float y) {
    float corners = (Noise2D(x - 1, y - 1) + Noise2D(x + 1, y - 1) + Noise2D(x - 1, y + 1) +
        Noise2D(x + 1, y + 1))/16;
    float sides = (Noise2D(x - 1, y) + Noise2D(x + 1, y) + Noise2D(x, y - 1) + Noise2D(x, y + 1))/8;
    float center = Noise2D(x, y)/4;
    return corners + sides + center;
}

Mesh* Tesselator::SphereSubTesselate(const Mesh& mesh)
{
    Mesh* m = new Mesh();

    int off = 0;
    for (int i =0; i< mesh.Indices.size() -2; i+= 3)
    {
        VertPosNormTanBiTex t;

        VertPosNormTanBiTex v0 = mesh.Vertices[mesh.Indices[i]];
        VertPosNormTanBiTex v1 = mesh.Vertices[mesh.Indices[i+1]];
        VertPosNormTanBiTex v2 = mesh.Vertices[mesh.Indices[i+2]];

        t = v0;
        t.Position = glm::normalize(t.Position);
        //	t.Position *= SmoothedNoise2D(t.Position.x, t.Position.y + t.Position.z);
        m->Vertices.push_back(t);
        t = v1;
        t.Position = glm::normalize(t.Position);
        //	t.Position *= SmoothedNoise2D(t.Position.x, t.Position.y + t.Position.z);
        m->Vertices.push_back(t);
        t = v2;
        t.Position = glm::normalize(t.Position);
        //t.Position *= SmoothedNoise2D(t.Position.x, t.Position.y + t.Position.z);
        m->Vertices.push_back(t);

        t = (v0 + v1)/2;
        t.Position = glm::normalize(t.Position);
        //t.Position *= SmoothedNoise2D(t.Position.x, t.Position.y + t.Position.z);
        m->Vertices.push_back(t);

        t = (v0 + v2)/2;
        t.Position = glm::normalize(t.Position);
        //t.Position *= SmoothedNoise2D(t.Position.x, t.Position.y + t.Position.z);
        m->Vertices.push_back(t);

        t = (v1 + v2)/2;
        t.Position = glm::normalize(t.Position);
        //t.Position *= SmoothedNoise2D(t.Position.x, t.Position.y + t.Position.z);
        m->Vertices.push_back(t);

        m->Indices.push_back(off+0);
        m->Indices.push_back(off+3);
        m->Indices.push_back(off+4);

        m->Indices.push_back(off+3);
        m->Indices.push_back(off+1);
        m->Indices.push_back(off+5);

        m->Indices.push_back(off+5);
        m->Indices.push_back(off+2);
        m->Indices.push_back(off+4);

        m->Indices.push_back(off+3);
        m->Indices.push_back(off+5);
        m->Indices.push_back(off+4);

        off+=6;
    }
    return m;
}

Mesh* Tesselator::SubTesselate(const Mesh& mesh)
{
    Mesh* m = new Mesh();

    int off = 0;
    for (int i =0; i< mesh.Indices.size() -2; i+= 3)
    {
        VertPosNormTanBiTex t;

        m->Vertices.push_back(mesh.Vertices[mesh.Indices[i]]);
        m->Vertices.push_back(mesh.Vertices[mesh.Indices[i+1]]);
        m->Vertices.push_back(mesh.Vertices[mesh.Indices[i+2]]);

        t.Position.x = (mesh.Vertices[mesh.Indices[i]].Position.x + mesh.Vertices[mesh.Indices[i+1]].Position.x)/2;
        t.Position.y = (mesh.Vertices[mesh.Indices[i]].Position.y + mesh.Vertices[mesh.Indices[i+1]].Position.y)/2;
        t.Position.z = (mesh.Vertices[mesh.Indices[i]].Position.z + mesh.Vertices[mesh.Indices[i+1]].Position.z)/2;
        t.Uv.x = (mesh.Vertices[mesh.Indices[i]].Uv.x + mesh.Vertices[mesh.Indices[i+1]].Uv.x)/2;
        t.Uv.y = (mesh.Vertices[mesh.Indices[i]].Uv.y + mesh.Vertices[mesh.Indices[i+1]].Uv.y)/2;
        m->Vertices.push_back(t);

        t.Position.x = (mesh.Vertices[mesh.Indices[i]].Position.x + mesh.Vertices[mesh.Indices[i+2]].Position.x)/2;
        t.Position.y = (mesh.Vertices[mesh.Indices[i]].Position.y + mesh.Vertices[mesh.Indices[i+2]].Position.y)/2;
        t.Position.z = (mesh.Vertices[mesh.Indices[i]].Position.z + mesh.Vertices[mesh.Indices[i+2]].Position.z)/2;
        t.Uv.x = (mesh.Vertices[mesh.Indices[i]].Uv.x + mesh.Vertices[mesh.Indices[i+2]].Uv.x)/2;
        t.Uv.y = (mesh.Vertices[mesh.Indices[i]].Uv.y + mesh.Vertices[mesh.Indices[i+2]].Uv.y)/2;
        m->Vertices.push_back(t);

        t.Position.x = (mesh.Vertices[mesh.Indices[i+1]].Position.x + mesh.Vertices[mesh.Indices[i+2]].Position.x)/2;
        t.Position.y = (mesh.Vertices[mesh.Indices[i+1]].Position.y + mesh.Vertices[mesh.Indices[i+2]].Position.y)/2;
        t.Position.z = (mesh.Vertices[mesh.Indices[i+1]].Position.z + mesh.Vertices[mesh.Indices[i+2]].Position.z)/2;
        t.Uv.x = (mesh.Vertices[mesh.Indices[i+1]].Uv.x + mesh.Vertices[mesh.Indices[i+2]].Uv.x)/2;
        t.Uv.y = (mesh.Vertices[mesh.Indices[i+1]].Uv.y + mesh.Vertices[mesh.Indices[i+2]].Uv.y)/2;
        m->Vertices.push_back(t);

        m->Indices.push_back(off+0);
        m->Indices.push_back(off+3);
        m->Indices.push_back(off+4);

        m->Indices.push_back(off+3);
        m->Indices.push_back(off+1);
        m->Indices.push_back(off+5);

        m->Indices.push_back(off+5);
        m->Indices.push_back(off+2);
        m->Indices.push_back(off+4);

        m->Indices.push_back(off+3);
        m->Indices.push_back(off+5);
        m->Indices.push_back(off+4);

        off+=6;
    }
    return m;
}
