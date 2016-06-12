#pragma once

#include <memory>
#include "socket.h"

namespace arch
{
/// <summary>UDPクラス</summary>
class udp : public socket
{
public:
	/// <summary>コンストラクタ</summary>
	udp();

	/// <summary>コンストラクタ</summary>
	/// <param name="address">宛先アドレス 空でポートのみの指定</param>
	/// <param name="port">ポート番号</param>
	udp(int port, const std::string& address);

	/// <summary>コンストラクタ</summary>
	udp(const udp& udp);

	/// <summary></summary>
	bool start() const override;

	/// <summary></summary>
	bool accept() const override;

	/// <summary></summary>
	void close() const override;

	/// <summary>データを転送します。</summary>
	/// <param name="data">データ</param>
	bool send(const std::string& data) const override;

	/// <summary>データを受信します</summary>
	/// <param name="result">受信データ</param>
	bool receive(std::string& result) const override;

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}