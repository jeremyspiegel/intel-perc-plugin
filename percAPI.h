#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "perc.h"
#include <boost/thread/thread.hpp>

#ifndef H_percAPI
#define H_percAPI

class percAPI : public FB::JSAPIAuto
{
public:
    percAPI(const percPtr& plugin, const FB::BrowserHostPtr& host);
    ~percAPI();

    percPtr getPlugin();
    std::string get_version();

    //FB_JSAPI_EVENT( frame, 1, ( FB::VariantMap ) );

    void loopFrames( const FB::JSObjectPtr& onFrame, const FB::JSObjectPtr& onError );

    bool Stop() { return m_stop; }

    void OnFrame( const FB::VariantMap& );
    void Error();

private:
    percWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
    FB::JSObjectPtr m_onFrame;
    FB::JSObjectPtr m_onError;
    bool m_stop;
    boost::thread m_thread;
};

#endif
