#ifndef INCLUDE_DGRENDMAN_HPP
#define INCLUDE_DGRENDMAN_HPP

#include <dolphin.h>
#include "DUMacro.hpp"

namespace DGRendMan {
public:
	DGRendMan(u32 gpFIFO_size);
	~DGRendMan(void);
	DrawBegin(void);
	DrawEnd(u8, u8);
	Draw(enumRendManDrawMode);
	CopyRenderingBuffer(u8);
	ClearRenderingList(void);
	AddModel(DGModel*);
	AddLight(DGLight*);
	AddCamera(DGCamera*);
	SetTexProjection(u8, DGTexPro*);
	SetRenderMode(_GXRenderModeObj*);
	GetBaseRenderMode(void);
	DisplaySetting(void);
	SetScissor(u32, u32, u32, u32);
	SetScissorDefault(void);
	SetViewport(f32, f32, f32, f32, f32, f32);
	SetViewportDefault(void);
	SetDispCopySrcDefault(void);
	SetDispCopyYScaleDefault(void);
	SetDispCopyDstDefault(void);
	SetDispCopyGamma(_GXGamma);
	SetAdjustForOverscanDefault(void);
	SetBGColor(_GXColor);
	SetBGZValue(u32);
	GetxfbHeight(void);
private: // TODO: figure out which one to put vars in
	// defined
	GXColor m_BGColor = { 0 };

	// bss
	u32 m_InstanceNum;
	u32 m_GpFIFO_Size;
	void* m_GpFIFO;
	GXFifoObj* m_GpFIFO_Obj;

	GXRenderModeObj* m_RenderMode;
	void* m_CurrentBuf; // TODO: not void*?
	void* m_FrameBuf1;
	void* m_FrameBuf2;
	u32 m_BGZValue;


}

#endif