#ifndef IRENDERER_H_INCLUDED
#define IRENDERER_H_INCLUDED

class IRenderer {
public:
    virtual void render(int x, int y, int red, int green, int blue) = 0;
};

class NullRenderer : public IRenderer {
public:
    void render(int x, int y, int red, int green, int blue) {};
};


#endif // IRENDERER_H_INCLUDED
