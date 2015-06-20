#ifndef _INCLUDE_GEMPLUGIN__TEXINBLACKMAGIXDESIGN_TEXINBLACKMAGIXDESIGN_H_
#define _INCLUDE_GEMPLUGIN__TEXINBLACKMAGIXDESIGN_TEXINBLACKMAGIXDESIGN_H_

#include "plugins/texin.h"
#include "Gem/Image.h"

#include <map>

#include <DeckLinkAPI.h>

class PinnedMemoryAllocator;

namespace gem { namespace plugins {
    class GEM_EXPORT texinBlackMagicDesign : public texin {
 private:
   std::string m_name; // 'BlackMagicDesign'
   std::string m_devname; // Card Name
   int m_devid; // Card ID

   Properties m_props;

   GLuint m_textureObj;

   IDeckLink*              m_deckLink;
   PinnedMemoryAllocator*  m_CaptureAllocator;

 public:
   texinBlackMagicDesign(void);

   virtual ~texinBlackMagicDesign(void);

   virtual bool open(gem::Properties&props);
   virtual GLuint getFrame(void);

   virtual std::vector<std::string>enumerate(void);
   virtual bool	setDevice(int ID);
   virtual bool	setDevice(const std::string);


   virtual bool enumProperties(gem::Properties&readable,
			       gem::Properties&writeable);
   virtual void setProperties(gem::Properties&props);
   virtual void getProperties(gem::Properties&props);

   // for pix_video: query whether this backend provides access to this class of devices
   // (e.g. "dv")
   virtual bool provides(const std::string);
   // get a list of all provided devices
   virtual std::vector<std::string>provides(void);

   // get's the name of the backend (e.g. "BlackMagicDesign")
   virtual const std::string getName(void);

   virtual bool isThreadable(void) {return false; return true;}
   virtual bool reset(void) {return true;}
   virtual void releaseFrame(void) {}
   virtual bool grabAsynchronous(bool) {return false; return true;}
   virtual bool setColor(int) {return false;}

   virtual void close(void);
   virtual bool start(void) {return true;};
   virtual bool stop(void)  {return true;};
};
};}; // namespace


////////////////////////////////////////////
// PinnedMemoryAllocator
////////////////////////////////////////////
class PinnedMemoryAllocator : public IDeckLinkMemoryAllocator
{
public:
   PinnedMemoryAllocator(/* QGLWidget* context, */ const char* name, unsigned cacheSize);
   virtual ~PinnedMemoryAllocator();

   GLuint bufferObjectForPinnedAddress(int bufferSize, const void* address);
   void unPinAddress(const void* address);

   // IUnknown methods
   virtual HRESULT STDMETHODCALLTYPE   QueryInterface(REFIID iid, LPVOID *ppv);
   virtual ULONG STDMETHODCALLTYPE     AddRef(void);
   virtual ULONG STDMETHODCALLTYPE     Release(void);

   // IDeckLinkMemoryAllocator methods
   virtual HRESULT STDMETHODCALLTYPE   AllocateBuffer (uint32_t bufferSize, void* *allocatedBuffer);
   virtual HRESULT STDMETHODCALLTYPE   ReleaseBuffer (void* buffer);
   virtual HRESULT STDMETHODCALLTYPE   Commit ();
   virtual HRESULT STDMETHODCALLTYPE   Decommit ();

private:
   // QGLWidget*                    mContext;
   int                              mRefCount;
   std::map<const void*, GLuint>    mBufferHandleForPinnedAddress;
   std::vector<void*>               mFrameCache;
   const char*                      mName;
   unsigned                         mFrameCacheSize;
};

#endif	// for header file
