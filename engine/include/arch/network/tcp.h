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
/// <summary>TCP�N���X</summary>
class tcp : public socket
{
public:
	/// <summary>�R���X�g���N�^</summary>
	tcp();

	/// <summary>�R���X�g���N�^</summary>
	/// <param name="address">����A�h���X ��Ń|�[�g�݂̂̎w��</param>
	/// <param name="port">�|�[�g�ԍ�</param>
	tcp(int port, const std::string& address);

	/// <summary>�R���X�g���N�^</summary>
	tcp(const tcp& tcp);

	/// <summary>�R�l�N�V�����̐���</summary>
	bool start() const override;

	/// <summary>�R�l�N�V�����̊m��(�T�[�o�̂�)</summary>
	bool accept() const override;

	/// <summary>�R�l�N�V�����̐ؒf</summary>
	void close() const override;

	/// <summary>�f�[�^��]�����܂��B</summary>
	/// <param name="data">�f�[�^</param>
	bool send(const std::string& data) const override;

	/// <summary>�f�[�^����M���܂�</summary>
	/// <param name="result">��M�f�[�^</param>
	bool receive(std::string& result) const override;

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}