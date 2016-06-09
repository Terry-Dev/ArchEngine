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
#include <string>
#include "types.h"

namespace arch
{

/// <summary>ネットワーク基底クラス</summary>
class basic_network
{
public:
	/// <summary>アドレスファミリ</summary>
	enum class address_family
	{
		unspecified,		/// <summary>指定なし</summary>
		unix,				/// <summary>Unix</summary>
		ipv4,				/// <summary>IPv4</summary>
		ipv6,				/// <summary>IPv6</summary>
		//IRDA,				対応待っててね（はぁと
		//Bluetooth
	};

	/// <summary>ソケットタイプ</summary>
	enum class socket_type
	{
		stream,				/// <summary>ストリームソケット(TCP)</summary>
		dgram,				/// <summary>データグラムソケット(UDP)</summary>
		raw,				/// <summary>生プロトコルソケット</summary>
		rdm,				/// <summary>確実に配送されるメッセージ</summary>
		seq_packet			/// <summary>シーケンシャルパケット</summary>
	};

	/// <summary>プロトコル</summary>
	enum class protocol
	{
		any,				/// <summary>不明</summary>
		icmp,				/// <summary>Internet Control Message Protocol</summary>
		igmp,				/// <summary>Internet Group Management Protocol</summary>
		rfcomm,				/// <summary>RFCOMM(Bluetooth)</summary>
		tcp,				/// <summary>TCP</summary>
		udp,				/// <summary>UDP</summary>
		icmpv6				/// <summary>Internet Control Message Protocol for IPv6</summary>
	};

	/// <summary>コンストラクタ</summary>
	/// <param name="family">アドレスファミリ</param>
	/// <param name="type">ソケットタイプ</param>
	/// <param name="protocol">プロトコルタイプ</param>
	basic_network(address_family family, socket_type type, protocol protocol);

	/// <summary>コンストラクタ</summary>
	basic_network(const basic_network& base_network);

	/// <summary>デストラクタ</summary>
	~basic_network();

	/// <summary>データが来ているかを返します。</summary>
	///<return>true : データが来ている</return>
	bool is_received_data();

	/// <summary>宛先のアドレスを指定します。</summary>
	/// <param name="address">宛先アドレス 空でポートのみの指定</param>
	/// <param name="port">ポート番号</param>
	///<return>true : アドレス指定完了</return>
	bool set_address(int port, const std::string& address="");

	/// <summary>指定したアドレスに接続します。</summary>
	/// <return>true : 接続に成功</return>
	bool connect_socket();

	/// <summary>バインドします。</summary>
	/// <return>true : バインドに成功</return>
	bool bind_socket();

	/// <summary>リッスンを開始します。</summary>
	/// <return>true : リッスンに成功</return>
	bool listen_socket(int back_log);


	/// <summary>コネクションを確立します。</summary>
	/// <return>true : 確立に成功</return>
	bool accept_socket();

	/// <summary>データを転送します。</summary>
	/// <param name="data">データ</param>
	/// <param name="length">配列長さ</param>
	/// <return>true : 転送に成功</return>
	bool send_socket(const void* data, uint length);

	/// <summary>データを取得します。</summary>
	/// <param name="out">取得したデータ</param>
	/// <param name="length">取得する文字長</param>
	/// <return>取得できた文字数</return>
	int receive(void* out, int length = 64);

	/// <summary>通信をノンブロッキングにします。</summary>
	/// <param name="flag">true : ノンブロッキング</param>
	void set_non_blocking(bool flag = true);

	/// <summary>確立したコネクションを閉じます。</summary>
	void close_socket();

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}