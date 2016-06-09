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
	tcp server(12345, "");				//TCPサーバーの作成
	int state = 0;
	server.start();						//サーバーを建てる
	std::string result = "";
	while (update())
	{
		switch (state)
		{
		case 1:							//何かデータを送る
			server.send("Connected.");	//"Connection."というデータをクライアントに送る
			state++;
			break;
		case 2:							//受信待機
			if (server.receive(result))	//データを受信
			{
				logging::debug(result);	//もらったデータをログに吐き出す。
			}
			if(result.find("close") != std::string::npos)
			{
				state++;
			}
			break;
		case 3:							//コネクション切断処理
			server.close();				//この時state==0つまりコネクション待ちを再度することができる。
			return;
		default:						//コネクション待ち
			if (server.accept())
			{
				state++;
			}
			break;
		}
	}
}