#include "wintab/wintab_device.h"

using namespace arch;
using namespace arch::wintab;

device::device()
: m_HasInitialized(false), m_SupportsWintab(false), m_SupportsPressure(false), m_SupportsTilt(false), m_WintabVersion(0)
{
	m_WTInfoFunction = nullptr;
	m_WTOpenFunction = nullptr;
	m_WTGetFunction = nullptr;
	m_WTSetFunction = nullptr;
	m_WTCloseFunction = nullptr;
	m_WTEnableFunction = nullptr;
	m_WTPacketFunction = nullptr;
	m_WTOverlapFunction = nullptr;
	m_WTSaveFunction = nullptr;
	m_WTConfigFunction = nullptr;
	m_WTRestoreFunction = nullptr;
	m_WTExtSetFunction = nullptr;
	m_WTExtGetFunction = nullptr;
	m_WTQueueSizeSetFunction = nullptr;
	m_WTDataPeekFunction = nullptr;
	m_WTPacketsGetFunction = nullptr;
	m_WTMgrOpenFunction = nullptr;
	m_WTMgrCloseFunction = nullptr;
	m_WTMgrDefContextFunction = nullptr;
	m_WTMgrDefContextExFunction = nullptr;

	m_Position = int2::zero();
	m_MaxPosition = int2::zero();
	m_MinPosition = int2::zero();
	m_PositionResolution = double2::zero();
	m_Pressure = 0.0;
	m_PressureInfo.max = 0;
	m_PressureInfo.min = 0;
	m_PressureInfo.resolution = 0.0;
	m_AzimuthRadian = 0.0;
	m_AzimuthInfo.max = 0;
	m_AzimuthInfo.min = 0;
	m_AzimuthInfo.resolution = 0.0;
	m_AltitudeRadian = 0.0;
	m_AltitudeInfo.max = 0;
	m_AltitudeInfo.min = 0;
	m_AltitudeInfo.resolution = 0.0;

	for (auto& key : m_Keys)
	{
		key.pressed = false;
		key.released = false;
		key.clicked = false;
	}
}

device::~device()
{
	finalize();
}

bool device::initialize()
{
	if (m_HasInitialized)
	{
		return false;
	}

	m_WintabDLL = win32::module("Wintab32.dll");
	if (!m_WintabDLL)
	{
		logging::infomation("Wintab32.dllを読み込めませんでした。");
		return false;
	}

	m_WTInfoFunction = m_WintabDLL.function<WTInfoAFuncPtr>("WTInfoA");
	m_WTOpenFunction = m_WintabDLL.function<WTOpenAFuncPtr>("WTOpenA");
	m_WTGetFunction = m_WintabDLL.function<WTGetAFuncPtr>("WTGetA");
	m_WTSetFunction = m_WintabDLL.function<WTSetAFuncPtr>("WTSetA");
	m_WTCloseFunction = m_WintabDLL.function<WTCloseFuncPtr>("WTClose");
	m_WTEnableFunction = m_WintabDLL.function<WTEnableFuncPtr>("WTEnable");
	m_WTPacketFunction = m_WintabDLL.function<WTPacketFuncPtr>("WTPacket");
	m_WTOverlapFunction = m_WintabDLL.function<WTOverlapFuncPtr>("WTOverlap");
	m_WTSaveFunction = m_WintabDLL.function<WTSaveFuncPtr>("WTSave");
	m_WTConfigFunction = m_WintabDLL.function<WTConfigFuncPtr>("WTConfig");
	m_WTRestoreFunction = m_WintabDLL.function<WTRestoreFuncPtr>("WTRestore");
	m_WTExtSetFunction = m_WintabDLL.function<WTExtSetFuncPtr>("WTExtSet");
	m_WTExtGetFunction = m_WintabDLL.function<WTExtGetFuncPtr>("WTExtGet");
	m_WTQueueSizeSetFunction = m_WintabDLL.function<WTQueueSizeSetFuncPtr>("WTQueueSizeSet");
	m_WTDataPeekFunction = m_WintabDLL.function<WTDataPeekFuncPtr>("WTDataPeek");
	m_WTPacketsGetFunction = m_WintabDLL.function<WTPacketsGetFuncPtr>("WTPacketsGet");
	m_WTMgrOpenFunction = m_WintabDLL.function<WTMgrOpenFuncPtr>("WTMgrOpen");
	m_WTMgrCloseFunction = m_WintabDLL.function<WTMgrCloseFuncPtr>("WTMgrClose");
	m_WTMgrDefContextFunction = m_WintabDLL.function<WTMgrDefContextFuncPtr>("WTMgrDefContext");
	m_WTMgrDefContextExFunction = m_WintabDLL.function<WTMgrDefContextExFuncPtr>("WTMgrDefContextEx");

	// Wintabが利用可能か調べる
	if (!m_WTInfoFunction(0, 0, NULL))
	{
		return false;
	}

	// Wintabのバージョンを調べる
	ushort version;
	m_WTInfoFunction(WTI_INTERFACE, IFC_SPECVERSION, &version);
	m_WintabVersion = static_cast<uint>(version);

	m_SupportsWintab = true;
	m_HasInitialized = true;

	reset();

	return true;
}

void device::finalize()
{
	if (!m_HasInitialized)
	{
		return;
	}

	m_WTInfoFunction = nullptr;
	m_WTOpenFunction = nullptr;
	m_WTGetFunction = nullptr;
	m_WTSetFunction = nullptr;
	m_WTCloseFunction = nullptr;
	m_WTEnableFunction = nullptr;
	m_WTPacketFunction = nullptr;
	m_WTOverlapFunction = nullptr;
	m_WTSaveFunction = nullptr;
	m_WTConfigFunction = nullptr;
	m_WTRestoreFunction = nullptr;
	m_WTExtSetFunction = nullptr;
	m_WTExtGetFunction = nullptr;
	m_WTQueueSizeSetFunction = nullptr;
	m_WTDataPeekFunction = nullptr;
	m_WTPacketsGetFunction = nullptr;
	m_WTMgrOpenFunction = nullptr;
	m_WTMgrCloseFunction = nullptr;
	m_WTMgrDefContextFunction = nullptr;
	m_WTMgrDefContextExFunction = nullptr;

	m_WintabDLL.close();

	m_SupportsTilt = false;
	m_SupportsPressure = false;
	m_SupportsWintab = false;

	m_HasInitialized = false;
}

void device::reset()
{
	/*
	// 利用可能なWacomのデバイスを調べる
	String name;
	name.resize(50);
    m_WTInfoWFunction(WTI_deviceS, DVC_NAME, name.data());
	if (name != "WACOM")
	{
		// Wacomのタブレットがない場合
    }
	*/

	// X方向に関する情報を取得
	AXIS x;
	m_WTInfoFunction(WTI_DEVICES, DVC_X, &x);
	m_Position.x = 0;
	m_MaxPosition.x = x.axMax;								// X方向の最大座標
	m_MinPosition.x = x.axMin;								// X方向の最小座標
	m_PositionResolution.x = FIX_DOUBLE(x.axResolution);	// X方向の分解能の整数部[line/inch]

	// Y方向に関する情報を取得
	AXIS y;
	m_WTInfoFunction(WTI_DEVICES, DVC_Y, &y);
	m_Position.y = 0;
	m_MaxPosition.y = y.axMax;								// Y方向の最大座標
	m_MinPosition.y = y.axMin;								// Y方向の最小座標
	m_PositionResolution.y = FIX_DOUBLE(y.axResolution);	// Y方向の分解能の整数部[line/inch]

	// 筆圧に関する情報を取得
	AXIS pressure = {0};
	m_SupportsPressure = m_WTInfoFunction(WTI_DEVICES, DVC_NPRESSURE, &pressure) != 0;
	m_Pressure = 0.0;
	m_PressureInfo.max = pressure.axMax;							// 最大筆圧
	m_PressureInfo.min = pressure.axMin;							// 最小筆圧
	m_PressureInfo.resolution = FIX_DOUBLE(pressure.axResolution);	// 筆圧の解像度

	// 傾きに関する情報を取得
	AXIS tilt[3] = {0};
	m_SupportsTilt = m_WTInfoFunction(WTI_DEVICES, DVC_ORIENTATION, tilt) != 0;
	if (m_SupportsTilt)
	{
		// タブレットが方位角と傾き角をサポートしているか 
		m_SupportsTilt = tilt[0].axResolution && tilt[1].axResolution;
	}
	m_AzimuthRadian = 0.0;
	m_AzimuthInfo.max = tilt[0].axMax;								// 最大方位角
	m_AzimuthInfo.min = tilt[0].axMin;								// 最小方位角
	m_AzimuthInfo.resolution = FIX_DOUBLE(tilt[0].axResolution);	// 方位角の解像度

	m_AltitudeRadian = 0.0;
	m_AltitudeInfo.max = tilt[0].axMax;								// 最大高さ
	m_AltitudeInfo.min = tilt[0].axMin;								// 最小高さ
	m_AltitudeInfo.resolution = FIX_DOUBLE(tilt[1].axResolution);	// 高さの解像度

	m_IsEraser = false;
}

bool device::registerWindow(HWND hwnd)
{
	if (!m_HasInitialized || !m_SupportsWintab)
	{
		return false;
	}

	Handle handle = {0};
	LOGCONTEXT& context = handle.context;
	context.lcOptions |= CXO_SYSTEM;
	
	m_WTInfoFunction(WTI_DEFSYSCTX, 0, &context);

	context.lcOptions |= CXO_MESSAGES;
	context.lcMsgBase = WT_DEFBASE;
	context.lcPktData = PACKETDATA;
	context.lcPktMode = PACKETMODE;
	context.lcMoveMask = PACKETDATA;
	context.lcBtnUpMask = context.lcBtnDnMask;

	// スケーリングの初期化を行う
	context.lcInOrgX = 0;										// タブレットの入力時の開始X座標
	context.lcInOrgY = 0;										// タブレットの入力時の開始Y座標
	context.lcInExtX = m_MaxPosition.x;							// タブレットの入力時の最大X座標
	context.lcInExtY = m_MaxPosition.y;							// タブレットの入力時の最大Y座標
	context.lcOutOrgX = GetSystemMetrics(SM_XVIRTUALSCREEN);	// コンテキストの出力時の開始X座標
	context.lcOutOrgY = GetSystemMetrics(SM_YVIRTUALSCREEN);	// コンテキストの出力時の開始Y座標
	context.lcOutExtX = GetSystemMetrics(SM_CXVIRTUALSCREEN);	// コンテキストの出力時の最大X座標
	context.lcOutExtY = -GetSystemMetrics(SM_CYVIRTUALSCREEN);	// コンテキストの出力時の最大Y座標

	// コンテキストを作成
	handle.windowHandle = hwnd;
	handle.contextHandle = m_WTOpenFunction(hwnd, &context, TRUE);
	if (handle.contextHandle == NULL)
	{
		return false;
	}

	// ハンドルに追加
	m_Handles.push_back(std::move(handle));

	return true;
}

void device::unregisterWindow(HWND hwnd)
{
	auto itr = m_Handles.begin();
	while (itr != m_Handles.end())
	{
		if (itr->windowHandle == hwnd)
		{
			m_WTCloseFunction(itr->contextHandle);
			m_Handles.erase(itr);
			return;
		}
		itr++;
	}
}

void device::onMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WT_PACKET:
		onPacket(hwnd, wParam, lParam);
		break;
	case WM_ACTIVATE:
		onActivate(hwnd, wParam, lParam);
		break;
	}
}

uint device::getVersion() const
{
	return m_WintabVersion;
}

const int2& device::getPosition() const
{
	return m_Position;
}

const int2& device::getMaxPosition() const
{
	return m_MaxPosition;
}

const int2& device::getMinPosition() const
{
	return m_MinPosition;
}

double device::getPressure() const
{
	return m_Pressure;
}

double device::getAzimuthRadian() const
{
	return m_AzimuthRadian;
}

double device::getAltitudeRadian() const
{
	return m_AltitudeRadian;
}

const info& device::getPressureInfo() const
{
	return m_PressureInfo;
}

const info& device::getAzimuthInfo() const
{
	return m_AzimuthInfo;
}

const info& device::getAltitudeInfo() const
{
	return m_AltitudeInfo;
}

bool device::supportsWintab() const
{
	return m_SupportsWintab;
}

bool device::supportsPressure() const
{
	return m_SupportsPressure;
}

bool device::supportsTilt() const
{
	return m_SupportsTilt;
}

bool device::isEraser() const
{
	return m_IsEraser;
}


void device::onPacket(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HCTX handle = reinterpret_cast<HCTX>(lParam);
	PACKET packet;
	if (m_WTPacketFunction(handle, static_cast<UINT>(wParam), &packet))
	{
		uint state = HIWORD(packet.pkButtons);
		uint index = LOWORD(packet.pkButtons);
		
		if (m_Keys.size() <= index)
		{
			return;
		}

		bool down = false;
		switch (state)
		{
		// 変化なし
		case TBN_NONE:
			down = m_Keys[index].pressed;
			break;
		case TBN_UP:
			down = false;
			break;
		case TBN_DOWN:
			down = true;
			break;
		}

		m_Position.x = packet.pkX;
		m_Position.y = packet.pkY;

		m_Keys[index].clicked = m_Keys[index].pressed ? false : down;
		m_Keys[index].released = m_Keys[index].pressed ? !down : false;
		m_Keys[index].pressed = down;

		m_Pressure = m_SupportsPressure ? static_cast<double>(packet.pkNormalPressure - m_PressureInfo.min) / static_cast<double>(m_PressureInfo.max - m_PressureInfo.min) : 0.0;

		if (m_SupportsTilt)
		{
			const double PiDivTwo = constant::pi<double>() / 2.0;
			m_AzimuthRadian = constant::two_pi<double>() * static_cast<double>(packet.pkOrientation.orAzimuth - m_AzimuthInfo.min) / static_cast<double>(m_AzimuthInfo.max - m_AzimuthInfo.min);
			m_AltitudeRadian = PiDivTwo * static_cast<double>(abs(packet.pkOrientation.orAltitude) - m_AltitudeInfo.min) / static_cast<double>(m_AltitudeInfo.max - m_AltitudeInfo.min);
		}

		// TPS_INVERTのビットが立っている場合は向きが消しゴム側になっている
		m_IsEraser = (packet.pkStatus & TPS_INVERT) == TPS_INVERT;
	}
}

void device::onActivate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	auto itr = m_Handles.begin();
	while (itr != m_Handles.end())
	{
		if (itr->windowHandle == hwnd)
		{
			HCTX handle = itr->contextHandle;
			m_WTEnableFunction(handle, GET_WM_ACTIVATE_STATE(wParam, lParam));
			if (GET_WM_ACTIVATE_STATE(wParam, lParam))
			{
				m_WTOverlapFunction(handle, TRUE);
			}

			return;
		}
		itr++;
	}
}