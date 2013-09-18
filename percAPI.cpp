#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"
#include "percAPI.h"
#include "util_pipeline.h"
#include "gesture_render.h"
#include <process.h>
#include <windows.h>

class MyPipeline: public UtilPipeline
{
public:
    MyPipeline( percAPI& percAPI )
        : UtilPipeline()
        , m_render( L"Gesture Viewer" )
        , m_percAPI( percAPI )
    {
		EnableGesture();
	}

    virtual bool OnNewFrame()
    {
        MyOnNewFrame();
        return m_render.RenderFrame(QueryImage(PXCImage::IMAGE_TYPE_DEPTH), QueryGesture(), &m_gdata);
    }

protected:
    void MyOnNewFrame();

    GestureRender       m_render;
    PXCGesture::Gesture m_gdata;
    percAPI&            m_percAPI;
};

void MyPipeline::MyOnNewFrame()
{
    //PXCGesture* detector = QueryGesture();
    //m_percAPI.fire_frame(5);
}

void LoopFrames( void* arg )
{
    MyPipeline pipeline( *static_cast<percAPI*>( arg ) );
    if (!pipeline.LoopFrames()) MessageBox(NULL, L"Failed to initialize or stream data", L"", 0);
}

percAPI::percAPI(const percPtr& plugin, const FB::BrowserHostPtr& host) :
    m_plugin(plugin), m_host(host)
{
    _beginthread( &LoopFrames, 0, this );
	MessageBox(NULL, L"percAPI::percAPI", L"", 0);
    //registerMethod("frame", make_method(this, &percAPI::frame));
}

percPtr percAPI::getPlugin()
{
    percPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}
