#ifndef _INCLUDE_GEMPLUGIN__TEXINBLACKMAGIXDESIGN_TEXINBLACKMAGIXDESIGN_H_
#define _INCLUDE_GEMPLUGIN__TEXINBLACKMAGIXDESIGN_TEXINBLACKMAGIXDESIGN_H_

#include "plugins/texin.h"
#include "Gem/Image.h"


#include <DeckLinkAPI.h>

namespace gem { namespace plugins {
    class GEM_EXPORT texinBlackMagicDesign : public texin {
 private:
   std::string m_name; // 'BlackMagicDesign'
   std::string m_devname; // Card Name
   int m_devid; // Card ID

   Properties m_props;

   GLuint m_textureObj;

   IDeckLink*              m_deckLink;

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

#endif	// for header file
