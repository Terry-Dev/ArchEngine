//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Terry                                                  //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#include <vector>
#include "arch/html_logger.h"
#include "arch/date_time.h"

using namespace arch;

html_logger::html_logger(const std::string& _path)
: logger()
{
	writer = text_writer(_path, open_mode::truncate, text_encoding::utf8);
	if (!writer)
	{
		return;
	}

	writer.write("<html lang=\"ja\">\n<head>\n");
	writer.write("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	writer.write("<title>ArchEngine Log</title>\n");
	writer.write("<style>\n");
	writer.write("body\n{\nbackground-color:#818181;\nfont-family:\"メイリオ\", \"ヒラギノ角ゴ Pro W3\", \"ＭＳ Ｐゴシック\";\n}\n");
	writer.write("h1\n{\nfont-size:26px;\ncolor:#ffffcc;\n}\n");
	writer.write("div\n{\nfont-size:12px;\nwidth:80px;\nfloat:left;\ntext-align:center;\nmargin:0px 18px 0px 18px;\npadding:6px 8px 6px 8px;\n}\n");
	writer.write("div.header\n{\nfont-size:26px;\ncolor:#ffffcc;\nwidth:auto;\nfloat:none;\ntext-align:center;\n}\n");
	writer.write("div.copyright\n{\nfont-size:18px;\ncolor:#ffffcc;\nwidth:auto;\nfloat:none;\ntext-align:center;\n}\n");
	writer.write("div.footer\n{\nwidth:auto;\nfloat:none;\ntext-align:center;\n}\n");
	writer.write("div.content\n{width:auto;\nfloat:none;\ntext-align:left;\nbackground-color:#F1F1F2;\n}\n");
	writer.write("div.critical\n{\ncolor:#ffffcc;\nbackground-color:#2FCAD8;\n}\n");
	writer.write("div.error\n{\ncolor:#ffffcc;\nbackground-color:#BF1717;\n}\n");
	writer.write("div.warning\n{\ncolor:#ffffcc;\nbackground-color:#D9BA23;\n}\n");
	writer.write("div.infomation\n{\ncolor:#ffffcc;\nbackground-color:#45BF4D;\n}\n");
	writer.write("div.debug\n{\ncolor:#ffffcc;\nbackground-color:#2671E5;\n}\n");
	writer.write("</style>\n");
	writer.write("</head>\n");
	writer.write("<body>\n");
	writer.write("<div class=\"header\">ArchEngine Log</div>\n");
}

html_logger::~html_logger()
{
	if (!writer)
	{
		return;
	}

	static const std::vector<const char*> copyright =
	{
		{
			"ArchEngine<br>\n"
			"Copyright (c) 2011-2015 60FPS*\n"
		},
	};
	for (uint i = 0; i < copyright.size(); i++)
	{
		writer.write("<div class=\"copyright\">\n");
		writer.write(copyright[i]);
		writer.write("</div>\n");
	}

	writer.write("</body>\n");
	writer.write("</html>\n");
	writer.close();
}

void html_logger::write(const std::string& message, trace_level level)
{
	if (!writer)
	{
		return;
	}

	switch (level)
	{
	case trace_level::critical:
		writer.write("<div class=\"critical\">Critical</div>\n");
		break;
	case trace_level::error:
		writer.write("<div class=\"error\">Error</div>\n");
		break;
	case trace_level::infomation:
		writer.write("<div class=\"infomation\">Infomation</div>\n");
		break;
	case trace_level::debug:
		writer.write("<div class=\"debug\">Debug</div>\n");
		break;
	}

	auto date = date_time::now();

	writer.write("<div class=\"content\">");
	writer.write("[" + date.to_string() + "]\t" + message);
	writer.write("</div>\n");
	writer.flush();
}