#pragma once

#include "../renderer.h"

#include <QQueue>

class Pacer;

class IVsyncRenderer {
public:
    virtual ~IVsyncRenderer() {}
    virtual void renderFrameAtVsync(AVFrame* frame) = 0;
};

class IVsyncSource {
public:
    virtual ~IVsyncSource() {}
    virtual bool initialize(SDL_Window* window) = 0;
};

class Pacer
{
public:
    Pacer(IVsyncRenderer* renderer);

    ~Pacer();

    void submitFrame(AVFrame* frame);

    bool initialize(SDL_Window* window, int maxVideoFps);

    void vsyncCallback();

    void drain();

private:
    QQueue<AVFrame*> m_FrameQueue;
    QQueue<int> m_FrameQueueHistory;
    SDL_SpinLock m_FrameQueueLock;

    IVsyncSource* m_VsyncSource;
    IVsyncRenderer* m_VsyncRenderer;
    int m_MaxVideoFps;
    int m_DisplayFps;
};