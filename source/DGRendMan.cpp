#include "DGRendMan.hpp"

namespace DGRendMan {
	DGRendMan(u32 gpFIFO_size)
	{
		GXColor clear_clr; // stack + 0x1C
		u32 fbSize = 0x96000; // TODO: figure out where to put, it's register based, not global/stack

		m_InstanceNum++;
		if (m_GpFIFO == NULL)
		{
			m_GpFIFO_Size = ALIGN(gpFIFO_size, 32);
			m_GpFIFO = mAlloc(m_GpFIFO_Size);
			m_GpFIFO_Obj = GXInit(m_GpFIFO, m_GpFIFO_Size);
		}

		if (m_RenderMode == NULL)
		{
			m_RenderMode = mAlloc(sizeof(GXRenderModeObj));
			SetRenderMode(&GXNtsc480IntDf);
			OSReport("fbSize = %d\n", fbSize);
			m_FrameBuf1 = mAlloc(fbSize);
			m_CurrentBuf = mAlloc(fbSize);
			m_FrameBuf2 = m_CurrentBuf;
			memset(m_FrameBuf1, 0, fbSize);
			memset(m_FrameBuf2, 0, fbSize);
			DisplaySetting();
			clear_clr = m_BGColor;
			GXSetCopyClear(clear_clr, m_BGZValue);
			GXCopyDisp(m_CurrentBuf, 1);
			GXDrawDone();
			VISetNextFrameBuffer(m_CurrentBuf);
			VIFlush();
		}
		/*
		this->lights[0] = NULL;
		this->lights[1] = NULL;
		this->lights[2] = NULL;
		this->lights[3] = NULL;
		this->lights[4] = NULL;
		this->lights[5] = NULL;
		this->lights[6] = NULL;
		this->lights[7] = NULL;
		this->lights[8] = NULL;
		this->field_0x24 = 0;
		this->field_0x28 = 0;
		this->field_0x2c = 0;
		this->field_0x30 = 0;
		this->field_0x34 = 0;
		this->field_0x38 = 0;
		this->field_0x3c = 0;
		this->field_0x40 = 0;
		this->field_0x44 = 0;
		*/
	}
	~DGRendMan(void)
	{
	}
	DrawBegin(void)
	{
	}
	DrawEnd(u8, u8)
	{
	}
	Draw(enumRendManDrawMode)
	{
	}
	CopyRenderingBuffer(u8)
	{
	}
	ClearRenderingList(void)
	{
	}
	AddModel(DGModel*)
	{
	}
	AddLight(DGLight*)
	{
	}
	AddCamera(DGCamera*)
	{
	}
	SetTexProjection(u8, DGTexPro*)
	{
	}
	SetRenderMode(_GXRenderModeObj*)
	{
	}
	GetBaseRenderMode(void)
	{
	}
	DisplaySetting(void)
	{
	}
	SetScissor(u32, u32, u32, u32)
	{
	}
	SetScissorDefault(void)
	{
	}
	SetViewport(f32, f32, f32, f32, f32, f32)
	{
	}
	SetViewportDefault(void)
	{
	}
	SetDispCopySrcDefault(void)
	{
	}
	SetDispCopyYScaleDefault(void)
	{
	}
	SetDispCopyDstDefault(void)
	{
	}
	SetDispCopyGamma(_GXGamma)
	{
	}
	SetAdjustForOverscanDefault(void)
	{
	}
	SetBGColor(_GXColor)
	{
	}
	SetBGZValue(u32)
	{
	}
	GetxfbHeight(void)
	{
	}
}