#include <stdint.h>

#include "psyqo/primitives/common.hh"
#include "psyqo/primitives/lines.hh"
#include "psyqo/primitives/rectangles.hh"
#include "psyqo/primitives/triangles.hh"
#include "third_party/nugget/common/syscalls/syscalls.h"
#include "third_party/nugget/psyqo/application.hh"
#include "third_party/nugget/psyqo/font.hh"
#include "third_party/nugget/psyqo/gpu.hh"
#include "third_party/nugget/psyqo/scene.hh"


/*
    TODO take what I learned from my lamejam44 attempt and
         draw lines, cubes, etc. 

         Try to understand the fundamentals of 3D graphics
         tailored to PSX

    NEXT TASK: Draw a moving line

    NOTE My eventual goal is to 'demake' Rocket League to  
         just about any console I can get an SDK for. PSX/P/2 are just
         all consoles that have a special place in my heart.
*/


// A PSYQo software needs to declare one \`Application\` object.
// This is the one we're going to do for our hello world.
class LearnGPU final : public psyqo::Application {

    void prepare() override;
    void createScene() override;

  public:
    psyqo::Font<> m_font;
};


class GfxScene final : public psyqo::Scene {
    void frame() override;

    // TODO do shit
    psyqo::Color bg {{.r = 0, .g = 64, .b = 91}};

    // white text I think
    psyqo::Color text_color {{.r = 255, .g = 255, .b = 255}};

    psyqo::Color line_color {{.r = 0, .g = 255, .b = 160}};
    psyqo::Prim::Line line;

    psyqo::Color rect_color {{.r = 150, .g = 0, .b = 255}};
    psyqo::Prim::Rectangle rect;

    psyqo::Prim::Triangle tri;

    public: 
        void prepare(); // config to reduce calls per cycle (maybe?)
    
};

// We're instantiating the two objects above right now.
// NOTE these might not need to be static like I was doing before lol
LearnGPU learn_gpu;
GfxScene gfx_scene;

// Boilerplate
void LearnGPU::prepare() {
    psyqo::GPU::Configuration config;
    config.set(psyqo::GPU::Resolution::W320)
        .set(psyqo::GPU::VideoMode::AUTO)
        .set(psyqo::GPU::ColorMode::C15BITS)
        .set(psyqo::GPU::Interlace::PROGRESSIVE);
    gpu().initialize(config);
}

void LearnGPU::createScene() {
    m_font.uploadSystemFont(gpu());
    pushScene(&gfx_scene);

    gfx_scene.prepare();
}

void GfxScene::frame() {
    // TODO draw a triangle
    // TODO move, rotate and transform the shapes
    // TODO attempt a the cube 

    learn_gpu.gpu().clear(this->bg);

    learn_gpu.m_font.print(learn_gpu.gpu(), "Learning how to use the GPU in PsyQo!", {{.x = 16, .y = 32}}, this->text_color);

    // diagnal line?
    line.pointA.x = 50;
    line.pointA.y = 50;

    line.pointB.x = 300;
    line.pointB.y = 300;

    learn_gpu.gpu().sendPrimitive(line);

    // Rectangle (diff from quad?)

    rect.position = {{.x = 200, .y = 200}};
    rect.size = {{.w = 10, .h = 10}};

    learn_gpu.gpu().sendPrimitive(rect);

    // Triangle

    tri.pointA.x = 320;
    tri.pointA.y = 240;

    tri.pointB.x = 320;
    tri.pointB.y = 200;

    tri.pointC.x = 300;
    tri.pointC.y = 220;

    learn_gpu.gpu().sendPrimitive(tri);
}

void GfxScene::prepare() {
    // Scene items to run once
    // This might not be useful

    // NOTE how to make useful for dynamic scenes? 
    this->line.setColor(this->line_color);
    this->rect.setColor(this->rect_color);
    this->tri.setColor(this->line_color);
}

int main() { return learn_gpu.run(); }
