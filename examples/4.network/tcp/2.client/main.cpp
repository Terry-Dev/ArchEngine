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
	tcp client(12345, "localhost");		//TCPクライアントの作成
	int state = 0;
	client.start();						//サーバーに接続
	std::string result = "";
	while (update())
	{
		switch (state)
		{
		case 1:							//何かデータを送る
			client.send("close\n");		//"close\n"というデータをサーバーに送る
			state++;
			break;
		case 2:							//コネクション切断処理
			client.close();
			return;
		default:						//受信待機
			if (client.receive(result))	//データを受信
			{
				logging::debug(result);	//もらったデータをログに吐き出す。
			}
			if (result.find('.') != std::string::npos)
			{
				state++;
			}
			break;
		}
	}
}