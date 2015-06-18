#include "texinBlackMagicDesign.h"
#include "plugins/PluginFactory.h"

#include <m_pd.h>

using namespace gem::plugins;

REGISTER_TEXINFACTORY("BlackMagicDesign", texinBlackMagicDesign);


texinBlackMagicDesign::texinBlackMagicDesign(void)
  : m_name(std::string("BlackMagicDesign")),  m_textureObj(0)
{
}

texinBlackMagicDesign::~texinBlackMagicDesign(void) {
  close();
}

void texinBlackMagicDesign::close(void) {
}

bool texinBlackMagicDesign::open(gem::Properties&props) {
  /*
  if(m_devname.empty())return false;
  setProperties(props);
  if(m_client)close();
  m_client=rfbGetClient(8,3,4);
  if(!m_client) {
    return false;
  }

  m_client->GotFrameBufferUpdate = frameBufferCB;
  m_client->GetPassword          = passwordCB;
  rfbClientSetClientData(m_client, (void*)(rfb2gem), this);

  if(true) {
    char*devname=strdup(m_devname.c_str());
    char*argv[]={
      "gem", // fake program name
      devname // the connection string
    };
    int argc=sizeof(argv)/sizeof(*argv);
    rfbBool res=rfbInitClient(m_client, &argc, argv);
    free(devname);
    if(!res) {
      // rfbInitClient() will call rfbClientCleanup() on failure automatically!
      m_client=0;
      return false;
    }
  }
  */
  return true;
}

GLuint texinBlackMagicDesign::getFrame(void) {
  return m_textureObj;
}

std::vector<std::string>texinBlackMagicDesign::enumerate(void) {
  std::vector<std::string>result;
  // result.push_back("vnc");
  return result;
}

bool texinBlackMagicDesign::setDevice(int ID) {
  m_devname.clear();
  return false;
}
bool texinBlackMagicDesign::setDevice(std::string device) {
  m_devname.clear();
  // const std::string prefix="vnc://";
  /*
  if (!device.compare(0, prefix.size(), prefix)) {
    m_devname=device.substr(prefix.size());
    //post("VNC: device '%s'", m_devname.c_str());
    return true;
  }
  */
  return false;
}
bool texinBlackMagicDesign::enumProperties(gem::Properties&readable,
			       gem::Properties&writeable) {
  std::string dummy_s;
  int dummy_i=0;
  readable.clear();
  writeable.clear();

  /*
  readable.set("width", m_pixBlock.image.xsize);
  readable.set("height", m_pixBlock.image.ysize);

  writeable.set("password", dummy_s);

  writeable.set("mouse.x", dummy_i);
  writeable.set("mouse.y", dummy_i);
  writeable.set("mouse.mask", dummy_i);
  */

  return true;
}
void texinBlackMagicDesign::setProperties(gem::Properties&props) {
  m_props=props;

  bool doMouse=false;

  double num;
  std::string s;

  /*
  if(props.get("password", s)) {
    m_password=s;
  }
  if(props.get("mouse.x", num)) {
    doMouse=true;
    m_mouse.x=num;
  }
  if(props.get("mouse.y", num)) {
    doMouse=true;
    m_mouse.y=num;
  }
  if(props.get("mouse.mask", num)) {
    doMouse=true;
    m_mouse.mask=num;
  }
  */

  /*
  if(doMouse && m_client) {
    if ((m_mouse.x != -1) && (m_mouse.y != -1)) {
      SendPointerEvent 	(m_client, m_mouse.x, m_mouse.y, m_mouse.mask);
      m_mouse.x = -1; m_mouse.y = -1;
    }
  }
  */
}
void texinBlackMagicDesign::getProperties(gem::Properties&props) {
  std::vector<std::string>keys=props.keys();
  unsigned int i;
  for(i=0; i<keys.size(); i++) {
    if("width"==keys[i]) {

    }
    if("height"==keys[i]) {

    }
  }
}

/*
std::vector<std::string>texinBlackMagicDesign::dialogs(void) {
  std::vector<std::string>result;
  return result;
}
*/
bool texinBlackMagicDesign::provides(const std::string name) {
  return (name==m_name);
}
std::vector<std::string>texinBlackMagicDesign::provides(void) {
  std::vector<std::string>result;
  result.push_back(m_name);

  IDeckLinkIterator*  deckLinkIterator = NULL;
  IDeckLink*          deckLink;
  int                 numDevices = 0;
  HRESULT             err;

  deckLinkIterator = CreateDeckLinkIteratorInstance();
  if (deckLinkIterator == NULL)
  {
    fprintf(stderr, "A DeckLink iterator could not be created.  The DeckLink drivers may not be installed.");
    return result;
  }

  // Enumerate all cards in this system
  while (deckLinkIterator->Next(&deckLink) == S_OK)
  {
    char *    deviceNameString = NULL;

    // Increment the total number of DeckLink cards found
    numDevices++;

    IDeckLinkAttributes*    deckLinkAttributes = NULL;
    int64_t           ports;
    int             itemCount;

    // Query the DeckLink for its configuration interface
    err = deckLink->QueryInterface(IID_IDeckLinkAttributes, (void**)&deckLinkAttributes);
    if (err != S_OK)
    {
      fprintf(stderr, "Could not obtain the IDeckLinkAttributes interface - result = %08x\n", result);
      goto bail;
    }

    printf("Supported video input connections:\n  ");
    itemCount = 0;
    err = deckLinkAttributes->GetInt(BMDDeckLinkVideoInputConnections, &ports);
    if (err == S_OK)
    {
      if (ports & bmdVideoConnectionSDI)
      {
        result.push_back("SDI");
      }

      if (ports & bmdVideoConnectionHDMI)
      {
        result.push_back("HDMI");
      }

      if (ports & bmdVideoConnectionOpticalSDI)
      {
        result.push_back("Optical SDI");
      }

      if (ports & bmdVideoConnectionComponent)
      {
        result.push_back("Component");
      }

      if (ports & bmdVideoConnectionComposite)
      {
        result.push_back("Composite");
      }

      if (ports & bmdVideoConnectionSVideo)
      {
        result.push_back("S-Video");
      }
    }
    else
    {
      error("Could not obtain the list of input ports - error = %08x\n", err);
      goto bail;
    }

  bail:
    if (deckLinkAttributes != NULL)
      deckLinkAttributes->Release();


    // Release the IDeckLink instance when we've finished with it to prevent leaks
    deckLink->Release();
  }

  return result;
}

const std::string texinBlackMagicDesign::getName(void) {
  return m_name;
}