#define _CRT_SECURE_NO_WARNINGS
#include <arch_engine.h>

using namespace arch;

void setup()
{
	logging::set_logger(std::make_shared<text_logger>());
}

void shutdown()
{
}

void run()
{
	basic_network server(basic_network::address_family::ipv4, basic_network::socket_type::stream, basic_network::protocol::tcp);
												//IPv4のStreamなTCPの設定でサーバー初期化
	server.set_address(12345);					//ポートを12345に設定
	server.set_non_blocking(false);				//ノンブロッキングに設定
	server.bind_socket();						//ポートをバインドする
	server.listen_socket(1);					//ポートをリッスン状態にする
	server.accept_socket();						//コネクションが来たら接続
	server.send_socket("Connected.", 12U);		//クライアントに"Connection."を送信
	std::string result = "";
	while (update())
	{
		if (server.is_received_data()) {		//データが来たかどうか
			char datas[64] = { 0 };
			server.receive(datas);				//データ受信
			result += datas;					//バッファに貯める
		}
		if (result.find("close") != std::string::npos)		//closeって入ってたら
		{
			server.close_socket();				//コネクションを閉じる。
			return;
		}
	}
}