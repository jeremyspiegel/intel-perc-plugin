#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"
#include "percAPI.h"
#include "util_pipeline.h"
#include "gesture_render.h"
#include <windows.h>

class MyPipeline: public UtilPipeline
{
public:
    MyPipeline( percAPI& percAPI )
        : m_percAPI( percAPI )
    {
		EnableGesture();
	}

    virtual bool OnNewFrame();

    percAPI& m_percAPI;
};

bool MyPipeline::OnNewFrame()
{
    if ( m_percAPI.Stop() )
        return false;

    // PXCGesture* detector = QueryGesture();
    // PXCGesture::GeoNode node;
    // detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY, &node );
    // FB::VariantMap frame;
    // fbPositionWorld["x"] = node.positionWorld.x;
    // fbPositionWorld["y"] = node.positionWorld.y;
    // fbPositionWorld["z"] = node.positionWorld.z;

    // m_percAPI.fire_frame( frame );

    PXCGesture* detector = QueryGesture();
    FB::VariantMap result;

    PXCGesture::GeoNode middleFinger;
    if ( detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY|PXCGesture::GeoNode::LABEL_FINGER_MIDDLE, &middleFinger ) != PXC_STATUS_ITEM_UNAVAILABLE )
    {
        PXCGesture::GeoNode hand;
        detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY, &hand );

        result["x"] = hand.normal.x;
        result["y"] = hand.normal.y;
        result["z"] = hand.normal.z;

        FB::VariantMap fbMassCenterWorld;
        fbMassCenterWorld["x"] = hand.massCenterWorld.x;
        fbMassCenterWorld["y"] = hand.massCenterWorld.y;
        fbMassCenterWorld["z"] = hand.massCenterWorld.z;
        result["massCenterWorld"] = fbMassCenterWorld;
    }
    m_percAPI.OnFrame( result );
    return true;

 //    PXCGesture::GeoNode nodes[2][11] = { 0 };
	// detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY, 10, nodes[0] );
	// detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY, 10, nodes[1] );
	// detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_ELBOW_PRIMARY, &nodes[0][10] );
	// detector->QueryNodeData( 0, PXCGesture::GeoNode::LABEL_BODY_ELBOW_SECONDARY, &nodes[1][10] );

 //    FB::VariantList fbNodes;
 //    for ( int i = 0; i < 2; i++ )
 //    {
 //        for ( int j = 0; j < 11; j++ )
 //        {
 //            const PXCGesture::GeoNode& node = nodes[i][j];
 //            if ( node.body <= 0 )
 //                continue;

 //            FB::VariantMap body;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_BODY ) == PXCGesture::GeoNode::LABEL_BODY_ELBOW_PRIMARY )
 //                body["elbowPrimary"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_BODY ) == PXCGesture::GeoNode::LABEL_BODY_ELBOW_SECONDARY )
 //                body["elbowSecondary"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_BODY ) == PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY )
 //                body["handPrimary"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_BODY ) == PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY )
 //                body["handSecondary"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_FINGER_THUMB )
 //                body["fingerThumb"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_FINGER_INDEX )
 //                body["fingerIndex"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_FINGER_MIDDLE )
 //                body["fingerMiddle"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_FINGER_RING )
 //                body["fingerRing"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_FINGER_PINKY )
 //                body["fingerPinky"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_HAND_FINGERTIP )
 //                body["handFingertip"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_HAND_UPPER )
 //                body["handUpper"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_HAND_MIDDLE )
 //                body["handMiddle"] = true;
 //            if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_HAND_LOWER )
 //                body["handLower"] = true;

 //            FB::VariantMap fbNode;
 //            fbNode["body"] = body;

 //            FB::VariantMap fbPositionWorld;
 //            fbPositionWorld["x"] = node.positionWorld.x;
 //            fbPositionWorld["y"] = node.positionWorld.y;
 //            fbPositionWorld["z"] = node.positionWorld.z;
 //            fbNode["positionWorld"] = fbPositionWorld;

 //            FB::VariantMap fbPositionImage;
 //            fbPositionImage["x"] = node.positionImage.x;
 //            fbPositionImage["y"] = node.positionImage.y;
 //            fbNode["positionImage"] = fbPositionImage;

 //            // if ( node.side == PXCGesture::GeoNode::LABEL_LEFT )
 //            //     fbNode["sideLeft"] = true;
 //            // if ( node.side == PXCGesture::GeoNode::LABEL_RIGHT )
 //            //     fbNode["sideRight"] = true;

 //            // fbNode["confidence"] = node.confidence;

 //            // if ( ( node.body & PXCGesture::GeoNode::LABEL_MASK_DETAILS ) == PXCGesture::GeoNode::LABEL_HAND_FINGERTIP )
 //            // {
 //            //     fbNode["radiusWorld"] = node.radiusWorld;
 //            //     fbNode["radiusImage"] = node.radiusImage;
 //            // }

 //            if ( node.body == PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY
 //              || node.body == PXCGesture::GeoNode::LABEL_BODY_HAND_SECONDARY )
 //            {
 //                FB::VariantMap fbMassCenterWorld;
 //                fbMassCenterWorld["x"] = node.massCenterWorld.x;
 //                fbMassCenterWorld["y"] = node.massCenterWorld.y;
 //                fbMassCenterWorld["z"] = node.massCenterWorld.z;
 //                fbNode["massCenterWorld"] = fbMassCenterWorld;

 //                FB::VariantMap fbMassCenterImage;
 //                fbMassCenterImage["x"] = node.massCenterImage.x;
 //                fbMassCenterImage["y"] = node.massCenterImage.y;
 //                fbNode["massCenterImage"] = fbMassCenterImage;

 //                FB::VariantMap fbNormal;
 //                fbNormal["x"] = node.normal.x;
 //                fbNormal["y"] = node.normal.y;
 //                fbNormal["z"] = node.normal.z;
 //                fbNode["normal"] = fbNormal;

 //                fbNode["openness"] = node.openness;

 //                if ( node.opennessState == PXCGesture::GeoNode::LABEL_CLOSE )
 //                    fbNode["palmOpen"] = true;
 //                if ( node.opennessState == PXCGesture::GeoNode::LABEL_OPEN )
 //                    fbNode["palmClosed"] = true;
 //            }


 //            // if ( node.openness == PXCGesture::GeoNode::LABEL_LEFT )
 //            //     fbNode["sideLeft"] = true;

 //            fbNodes.push_back( fbNode );
 //       }
 //   }

 //    FB::VariantMap gesture;
 //    gesture["nodes"] = fbNodes;

 //    FB::VariantMap frame;
 //    frame["gesture"] = gesture;
 //    m_percAPI.fire_frame( frame );

    return true;
}

void LoopFrames( percAPI& api )
{
    MyPipeline pipeline( api );
    if ( !pipeline.LoopFrames() )
        api.Error();
}

percAPI::percAPI( const percPtr& plugin, const FB::BrowserHostPtr& host )
    : m_plugin( plugin )
    , m_host( host )
    , m_stop( false )
{
    registerProperty( "version",
                      make_property( this,
                                     &percAPI::get_version ) );

    registerMethod( "loopFrames", make_method( this, &percAPI::loopFrames ) );
}

percAPI::~percAPI()
{
    m_stop = true;
    m_thread.join();
}

percPtr percAPI::getPlugin()
{
    percPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

std::string percAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void percAPI::loopFrames( const FB::JSObjectPtr& onFrame, const FB::JSObjectPtr& onError )
{
    m_stop = true;
    m_thread.join();
    m_stop = false;

    m_onFrame = onFrame;
    m_onError = onError;
    m_thread = boost::thread( boost::bind( &LoopFrames, boost::ref( *this ) ) );
}

void percAPI::OnFrame( const FB::VariantMap& frame )
{
    m_onFrame->InvokeAsync( "", FB::variant_list_of( frame ) );
}

void percAPI::Error()
{
    m_onError->InvokeAsync( "", std::vector<FB::variant>() );
}
