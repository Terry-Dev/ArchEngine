#pragma once

#define NOMINMAX
#define PACKETDATA (PK_X | PK_Y | PK_BUTTONS | PK_CURSOR | PK_STATUS | PK_NORMAL_PRESSURE | PK_ORIENTATION)
#define PACKETMODE 0

#include <vector>
#include <array>
#include <Windows.h>

#include "module.h"
#include "math/vector2.h"
#include "input/input_state.h"
#include "io/logging.h"

#include "Wintab/msgpack.h"
#include "Wintab/wintab.h"
#include "Wintab/pktdef.h"

#define FIX_DOUBLE(x) (static_cast<double>(INT(x))+(static_cast<double>(FRAC(x)) / 65536.0))

namespace arch
{

namespace wintab
{

struct info
{
	int max;			// �ő�l
	int min;			// �ŏ��l
	double resolution;	// �𑜓x
};

class device final
{
public:
	device();
	~device();

	bool initialize();
	void finalize();

	void reset();

	bool registerWindow(HWND hwnd);
	void unregisterWindow(HWND hwnd);

	void onMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	uint getVersion() const;
	const int2& getPosition() const;
	const int2& getMaxPosition() const;
	const int2& getMinPosition() const;
	double getPressure() const;
	double getAzimuthRadian() const;
	double getAltitudeRadian() const;
	const info& getPressureInfo() const;
	const info& getAzimuthInfo() const;
	const info& getAltitudeInfo() const;

	bool supportsWintab() const;
	bool supportsPressure() const;
	bool supportsTilt() const;
	bool isEraser() const;

private:
	struct Handle
	{
		HWND windowHandle;
		HCTX contextHandle;
		LOGCONTEXT context;
	};

	typedef decltype(WTInfoA)* WTInfoAFuncPtr;
	typedef decltype(WTInfoW)* WTInfoWFuncPtr;
	typedef decltype(WTOpenA)* WTOpenAFuncPtr;
	typedef decltype(WTOpenW)* WTOpenWFuncPtr;
	typedef decltype(WTGetA)* WTGetAFuncPtr;
	typedef decltype(WTGetW)* WTGetWFuncPtr;
	typedef decltype(WTSetA)* WTSetAFuncPtr;
	typedef decltype(WTSetW)* WTSetWFuncPtr;
	typedef decltype(WTClose)* WTCloseFuncPtr;
	typedef decltype(WTEnable)* WTEnableFuncPtr;
	typedef decltype(WTPacket)* WTPacketFuncPtr;
	typedef decltype(WTOverlap)* WTOverlapFuncPtr;
	typedef decltype(WTSave)* WTSaveFuncPtr;
	typedef decltype(WTConfig)* WTConfigFuncPtr;
	typedef decltype(WTRestore)* WTRestoreFuncPtr;
	typedef decltype(WTExtSet)* WTExtSetFuncPtr;
	typedef decltype(WTExtGet)* WTExtGetFuncPtr;
	typedef decltype(WTQueueSizeSet)* WTQueueSizeSetFuncPtr;
	typedef decltype(WTDataPeek)* WTDataPeekFuncPtr;
	typedef decltype(WTPacketsGet)* WTPacketsGetFuncPtr;
	typedef decltype(WTMgrOpen)* WTMgrOpenFuncPtr;
	typedef decltype(WTMgrClose)* WTMgrCloseFuncPtr;
	typedef decltype(WTMgrDefContext)* WTMgrDefContextFuncPtr;
	typedef decltype(WTMgrDefContextEx)* WTMgrDefContextExFuncPtr;

	void onPacket(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void onActivate(HWND hwnd, WPARAM wParam, LPARAM lParam);

private:
	bool					m_HasInitialized;
	bool					m_SupportsWintab;
	bool					m_SupportsPressure;		// �M���ɑΉ����Ă���
	bool					m_SupportsTilt;			// �X���ɑΉ����Ă���
	bool					m_IsEraser;				// �����S�����ł���

	int						m_WintabVersion;		// Wintab�̃o�[�W����
	int2					m_Position;				// �^�u���b�g��̈ʒu
	int2					m_MaxPosition;			// �^�u���b�g��̍ő���W
	int2					m_MinPosition;			// �^�u���b�g��̍ŏ����W
	double2					m_PositionResolution;	// �^�u���b�g��̉𑜓x
	double					m_Pressure;				// �^�u���b�g��̕M��(0-1)
	info					m_PressureInfo;			// �^�u���b�g��̕M�����
	double					m_AzimuthRadian;		// �^�u���b�g��̕��ʊp(�^�u���b�g�̕��ʏ�ɓ��e�������̃y���̊p�x)(0-2��)
	info					m_AzimuthInfo;			// �^�u���b�g��̕��ʊp���
	double					m_AltitudeRadian;		// �^�u���b�g��̍���(�^�u���b�g�̕��ʂɐ����Ȋp�x)(0-��/2)
	info					m_AltitudeInfo;			// �^�u���b�g��̍������

	std::array<input_state, 8>	m_Keys;
	std::vector<Handle>			m_Handles;
	win32::module				m_WintabDLL;
	WTInfoAFuncPtr				m_WTInfoFunction;
	WTOpenAFuncPtr				m_WTOpenFunction;
	WTGetAFuncPtr				m_WTGetFunction;
	WTSetAFuncPtr				m_WTSetFunction;
	WTCloseFuncPtr				m_WTCloseFunction;
	WTEnableFuncPtr				m_WTEnableFunction;
	WTPacketFuncPtr				m_WTPacketFunction;
	WTOverlapFuncPtr			m_WTOverlapFunction;
	WTSaveFuncPtr				m_WTSaveFunction;
	WTConfigFuncPtr				m_WTConfigFunction;
	WTRestoreFuncPtr			m_WTRestoreFunction;
	WTExtSetFuncPtr				m_WTExtSetFunction;
	WTExtGetFuncPtr				m_WTExtGetFunction;
	WTQueueSizeSetFuncPtr		m_WTQueueSizeSetFunction;
	WTDataPeekFuncPtr			m_WTDataPeekFunction;
	WTPacketsGetFuncPtr			m_WTPacketsGetFunction;
	WTMgrOpenFuncPtr			m_WTMgrOpenFunction;
	WTMgrCloseFuncPtr			m_WTMgrCloseFunction;
	WTMgrDefContextFuncPtr		m_WTMgrDefContextFunction;
	WTMgrDefContextExFuncPtr	m_WTMgrDefContextExFunction;
};

}

}