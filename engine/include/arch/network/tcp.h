//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Surigoma                                               //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#pragma once

#include <memory>
#include "socket.h"

namespace arch
{
/// <summary>TCPクラス</summary>
class tcp : public socket
{
public:
	/// <summary>コンストラクタ</summary>
	tcp();

	/// <summary>コンストラクタ</summary>
	/// <param name="address">宛先アドレス 空でポートのみの指定</param>
	/// <param name="port">ポート番号</param>
	tcp(int port, const std::string& address);

	/// <summary>コンストラクタ</summary>
	tcp(const tcp& tcp);

	/// <summary>コネクションの生成</summary>
	bool start() const override;

	/// <summary>コネクションの確立(サーバのみ)</summary>
	bool accept() const override;

	/// <summary>コネクションの切断</summary>
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