set(PLUGIN_NAME "Motion Maps")
set(PLUGIN_PREFIX "motionmaps")
set(COMPANY_NAME "Motion Maps")

# ActiveX constants:
set(FBTYPELIB_NAME motionmapsLib)
set(FBTYPELIB_DESC "motionmaps 1.0 Type Library")
set(IFBControl_DESC "motionmaps Control Interface")
set(FBControl_DESC "motionmaps Control Class")
set(IFBComJavascriptObject_DESC "motionmaps IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "motionmaps ComJavascriptObject Class")
set(IFBComEventSource_DESC "motionmaps IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID de7e9d7f-aa6a-5e76-9b35-8dfbb1f2cfb7)
set(IFBControl_GUID 358c5352-cc81-588d-a695-73af380be8f2)
set(FBControl_GUID 3606fe95-61b0-5391-a3c8-88f1b31f83ed)
set(IFBComJavascriptObject_GUID 653a0b29-5b59-5d3a-b97c-b2daa72776ea)
set(FBComJavascriptObject_GUID 65baec86-9004-5eda-bf02-f8760037ff18)
set(IFBComEventSource_GUID 0042c9ae-820a-5a3f-ab68-f75671e914f6)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 7fe40bc7-484d-536c-882b-f46032a33c93)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID d4b2eb7a-8745-5395-94cd-878340ecf227)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "motionmaps.motionmaps")
set(MOZILLA_PLUGINID "motionmaps.com/motionmapsrc")

# strings
set(FBSTRING_CompanyName "Motion Maps")
set(FBSTRING_PluginDescription "Motion Maps")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Motion Maps")
set(FBSTRING_PluginFileName "npmotionmaps.dll")
set(FBSTRING_ProductName "Motion Maps")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "Motion Maps")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "Motion Maps_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-motionmaps")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
