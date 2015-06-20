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
  post("texinBlackMagicDesign::open()");

  IDeckLinkIterator*  deckLinkIterator = NULL;
  IDeckLink*          deckLink;
  HRESULT             err;

  deckLinkIterator = CreateDeckLinkIteratorInstance();
  if (deckLinkIterator == NULL)
  {
    fprintf(stderr, "A DeckLink iterator could not be created.  The DeckLink drivers may not be installed.");
    return false;
  }

  if(m_devname.empty()){
    int idx = m_devid;

    while ((err = deckLinkIterator->Next(&deckLink)) == S_OK)
    {
      if (idx == 0)
        break;
      --idx;

      deckLink->Release();
    }
  } else {

  }
  return true;
}

GLuint texinBlackMagicDesign::getFrame(void) {
  return m_textureObj;
}

std::vector<std::string>texinBlackMagicDesign::enumerate(void) {
  std::vector<std::string>result;

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

    // *** Print the model name of the DeckLink card
    err = deckLink->GetModelName((const char **) &deviceNameString);
    if (err == S_OK)
    {
      result.push_back(deviceNameString);
      // printf("=============== %s ===============\n\n", deviceNameString);
      free(deviceNameString);
    }
    // Release the IDeckLink instance when we've finished with it to prevent leaks
    deckLink->Release();
  }

  return result;
}

bool texinBlackMagicDesign::setDevice(int ID) {
  m_devname.clear();
  m_devid=ID;
  return false;
}
bool texinBlackMagicDesign::setDevice(std::string device) {
  m_devname.clear();
  m_devname=device;
  return true;
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
    int               itemCount;
    HRESULT           err;

    // Query the DeckLink for its configuration interface
    err = deckLink->QueryInterface(IID_IDeckLinkAttributes, (void**)&deckLinkAttributes);
    if (err != S_OK)
    {
      fprintf(stderr, "Could not obtain the IDeckLinkAttributes interface - result = %08x\n", err);
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


    // print_attributes(deckLink);

    // ** List the video output display modes supported by the card
    // print_output_modes(deckLink);

    // ** List the video input display modes supported by the card
    // print_input_modes(deckLink);

    // ** List the input and output capabilities of the card
    // print_capabilities(deckLink);

    // Release the IDeckLink instance when we've finished with it to prevent leaks
    deckLink->Release();
  }

  return result;
}

const std::string texinBlackMagicDesign::getName(void) {
  return m_name;
}

////////////////////////////////////////////
// PinnedMemoryAllocator
////////////////////////////////////////////

// PinnedMemoryAllocator implements the IDeckLinkMemoryAllocator interface and can be used instead of the
// built-in frame allocator, by setting with SetVideoInputFrameMemoryAllocator() or SetVideoOutputFrameMemoryAllocator().
//
// For this sample application a custom frame memory allocator is used to ensure each address
// of frame memory is aligned on a 4kB boundary required by the OpenGL pinned memory extension.
// If the pinned memory extension is not available, this allocator will still be used and
// demonstrates how to cache frame allocations for efficiency.
//
// The frame cache delays the releasing of buffers until the cache fills up, thereby avoiding an
// allocate plus pin operation for every frame, followed by an unpin and deallocate on every frame.
PinnedMemoryAllocator::PinnedMemoryAllocator(/* QGLWidget* context, */ const char *name, unsigned cacheSize) :
  /* mContext(context), */
  mRefCount(1),
  mName(name),
  mFrameCacheSize(cacheSize)  // large cache size will keep more GPU memory pinned and may result in out of memory errors
{
}

PinnedMemoryAllocator::~PinnedMemoryAllocator()
{
}

GLuint PinnedMemoryAllocator::bufferObjectForPinnedAddress(int bufferSize, const void* address)
{
  // Store all input memory buffers in a map to lookup corresponding pinned buffer handle
  if (mBufferHandleForPinnedAddress.count(address) == 0)
  {
    // This method assumes the OpenGL context is current

    // Create a handle to use for pinned memory
    GLuint bufferHandle;
    glGenBuffers(1, &bufferHandle);

    // Pin memory by binding buffer to special AMD target.
    glBindBuffer(GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD, bufferHandle);

    // glBufferData() sets up the address so any OpenGL operation on this buffer will use client memory directly
    // (assumes address is aligned to 4k boundary).
    glBufferData(GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD, bufferSize, address, GL_STREAM_DRAW);
    GLenum result = glGetError();
    if (result != GL_NO_ERROR)
    {
      fprintf(stderr, "%s allocator: Error pinning memory with glBufferData(GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD, size=%d ...) error=%s\n", mName, bufferSize, gluErrorString(result));
      exit(1);
    }
    glBindBuffer(GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD, 0);   // Unbind buffer to target

    mBufferHandleForPinnedAddress[address] = bufferHandle;
  }

  return mBufferHandleForPinnedAddress[address];
}

void PinnedMemoryAllocator::unPinAddress(const void* address)
{
  // un-pin address only if it has been pinned
  if (mBufferHandleForPinnedAddress.count(address) > 0)
  {
    // mContext->makeCurrent();

    // The buffer is un-pinned by the GPU when the buffer is deleted
    GLuint bufferHandle = mBufferHandleForPinnedAddress[address];
    glDeleteBuffers(1, &bufferHandle);
    mBufferHandleForPinnedAddress.erase(address);
  }
}

// IUnknown methods
HRESULT STDMETHODCALLTYPE PinnedMemoryAllocator::QueryInterface(REFIID /*iid*/, LPVOID* /*ppv*/)
{
  return E_NOTIMPL;
}

ULONG STDMETHODCALLTYPE   PinnedMemoryAllocator::AddRef(void)
{
  int oldValue = mRefCount;
  mRefCount++;
  return (ULONG)(oldValue + 1);
}

ULONG STDMETHODCALLTYPE   PinnedMemoryAllocator::Release(void)
{
  int oldValue = mRefCount;
  mRefCount--;
  if (oldValue == 1)    // i.e. current value will be 0
    delete this;

  return (ULONG)(oldValue - 1);
}

// IDeckLinkMemoryAllocator methods
HRESULT STDMETHODCALLTYPE PinnedMemoryAllocator::AllocateBuffer (uint32_t bufferSize, void* *allocatedBuffer)
{
  if (mFrameCache.empty())
  {
    // alignment to 4K required when pinning memory
    if (posix_memalign(allocatedBuffer, 4096, bufferSize) != 0)
      return E_OUTOFMEMORY;
  }
  else
  {
    // Re-use most recently ReleaseBuffer'd address
    *allocatedBuffer = mFrameCache.back();
    mFrameCache.pop_back();
  }
  return S_OK;
}

HRESULT STDMETHODCALLTYPE PinnedMemoryAllocator::ReleaseBuffer (void* buffer)
{
  if (mFrameCache.size() < mFrameCacheSize)
  {
    mFrameCache.push_back(buffer);
  }
  else
  {
    // No room left in cache, so un-pin (if it was pinned) and free this buffer
    unPinAddress(buffer);
    free(buffer);
  }
  return S_OK;
}

HRESULT STDMETHODCALLTYPE PinnedMemoryAllocator::Commit ()
{
  return S_OK;
}

HRESULT STDMETHODCALLTYPE PinnedMemoryAllocator::Decommit ()
{
  while (! mFrameCache.empty())
  {
    // Cleanup any frames allocated and pinned in AllocateBuffer() but not freed in ReleaseBuffer()
    unPinAddress( mFrameCache.back() );
    free( mFrameCache.back() );
    mFrameCache.pop_back();
  }
  return S_OK;
}
