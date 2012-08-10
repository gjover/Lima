#ifndef HWVIDEOCTRLOBJ_H
#define HWVIDEOCTRLOBJ_H
#include <list>
#include "Debug.h"
#include "Constants.h"
#include "SizeUtils.h"
#include "HwBufferMgr.h"
#include "HwBufferCtrlObj.h"

namespace lima
{
  class HwVideoCtrlObj
  {
    DEB_CLASS(DebModHardware,"HwVideoCtrlObj");
  public:
    class ImageCallback
    {
      friend class HwVideoCtrlObj;
      DEB_CLASS_NAMESPC(DebModControl,"Video::ImageCallback", 
			"Hardware");

    public:
      ImageCallback() {}
      virtual ~ImageCallback() {}
    protected:
      virtual bool newImage(char *,int width,int height,VideoMode) = 0;
    };

    HwVideoCtrlObj();
      
    virtual ~HwVideoCtrlObj();
 
    virtual void getSupportedVideoMode(std::list<VideoMode> &aList) const = 0;
    virtual void setVideoMode(VideoMode) = 0;
    virtual void getVideoMode(VideoMode&) const = 0;
    
    virtual void setLive(bool) = 0;
    virtual void getLive(bool&) const = 0;
    
    virtual void getGain(double&) const = 0;
    virtual void setGain(double) = 0;
    
    virtual void checkBin(Bin& bin) = 0;
    virtual void checkRoi(const Roi& set_roi, Roi& hw_roi) = 0;
    
    virtual void setBin(const Bin&) = 0;
    virtual void setRoi(const Roi&) = 0;
    
    void registerImageCallback(ImageCallback &cb);
    void unregisterImageCallback(ImageCallback &cb);
    
    HwBufferCtrlObj& getHwBufferCtrlObj();
    StdBufferCbMgr& getBuffer();
    
    bool callNewImage(char *data,int width,int height,VideoMode aVideoMode);

  protected:
    ImageCallback* m_image_cbk;
  private:
    SoftBufferCtrlObj		m_hw_buffer_ctrl_obj;
  };

  inline bool HwVideoCtrlObj::callNewImage(char *data,int width,int height,
					   VideoMode aVideoMode)
  {
    bool continueFlag = false;
    if(m_image_cbk)
      continueFlag = m_image_cbk->newImage(data,width,height,aVideoMode);
    return continueFlag;
  }

}
#endif
