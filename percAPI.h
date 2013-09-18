#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "perc.h"

#ifndef H_percAPI
#define H_percAPI

class percAPI : public FB::JSAPIAuto
{
public:
    percAPI(const percPtr& plugin, const FB::BrowserHostPtr& host);

    virtual ~percAPI() {};

    percPtr getPlugin();

    FB_JSAPI_EVENT(frame, 1, (const int));

private:
    percWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

#endif // H_percAPI
