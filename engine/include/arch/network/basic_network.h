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

/// <summary>�l�b�g���[�N���N���X</summary>
class basic_network
{
public:
	/// <summary>�A�h���X�t�@�~��</summary>
	enum class address_family
	{
		unspecified,		/// <summary>�w��Ȃ�</summary>
		unix,				/// <summary>Unix</summary>
		ipv4,				/// <summary>IPv4</summary>
		ipv6,				/// <summary>IPv6</summary>
		//IRDA,				�Ή��҂��ĂĂˁi�͂���
		//Bluetooth
	};

	/// <summary>�\�P�b�g�^�C�v</summary>
	enum class socket_type
	{
		stream,				/// <summary>�X�g���[���\�P�b�g(TCP)</summary>
		dgram,				/// <summary>�f�[�^�O�����\�P�b�g(UDP)</summary>
		raw,				/// <summary>���v���g�R���\�P�b�g</summary>
		rdm,				/// <summary>�m���ɔz������郁�b�Z�[�W</summary>
		seq_packet			/// <summary>�V�[�P���V�����p�P�b�g</summary>
	};

	/// <summary>�v���g�R��</summary>
	enum class protocol
	{
		any,				/// <summary>�s��</summary>
		icmp,				/// <summary>Internet Control Message Protocol</summary>
		igmp,				/// <summary>Internet Group Management Protocol</summary>
		rfcomm,				/// <summary>RFCOMM(Bluetooth)</summary>
		tcp,				/// <summary>TCP</summary>
		udp,				/// <summary>UDP</summary>
		icmpv6				/// <summary>Internet Control Message Protocol for IPv6</summary>
	};

	/// <summary>�R���X�g���N�^</summary>
	/// <param name="family">�A�h���X�t�@�~��</param>
	/// <param name="type">�\�P�b�g�^�C�v</param>
	/// <param name="protocol">�v���g�R���^�C�v</param>
	basic_network(address_family family, socket_type type, protocol protocol);

	/// <summary>�R���X�g���N�^</summary>
	basic_network(const basic_network& base_network);

	/// <summary>�f�X�g���N�^</summary>
	~basic_network();

	/// <summary>�f�[�^�����Ă��邩��Ԃ��܂��B</summary>
	///<return>true : �f�[�^�����Ă���</return>
	bool is_received_data();

	/// <summary>����̃A�h���X���w�肵�܂��B</summary>
	/// <param name="address">����A�h���X ��Ń|�[�g�݂̂̎w��</param>
	/// <param name="port">�|�[�g�ԍ�</param>
	///<return>true : �A�h���X�w�芮��</return>
	bool set_address(int port, const std::string& address="");

	/// <summary>�w�肵���A�h���X�ɐڑ����܂��B</summary>
	/// <return>true : �ڑ��ɐ���</return>
	bool connect_socket();

	/// <summary>�o�C���h���܂��B</summary>
	/// <return>true : �o�C���h�ɐ���</return>
	bool bind_socket();

	/// <summary>���b�X�����J�n���܂��B</summary>
	/// <return>true : ���b�X���ɐ���</return>
	bool listen_socket(int back_log);


	/// <summary>�R�l�N�V�������m�����܂��B</summary>
	/// <return>true : �m���ɐ���</return>
	bool accept_socket();

	/// <summary>�f�[�^��]�����܂��B</summary>
	/// <param name="data">�f�[�^</param>
	/// <param name="length">�z�񒷂�</param>
	/// <return>true : �]���ɐ���</return>
	bool send_socket(const void* data, uint length);

	/// <summary>�f�[�^���擾���܂��B</summary>
	/// <param name="out">�擾�����f�[�^</param>
	/// <param name="length">�擾���镶����</param>
	/// <return>�擾�ł���������</return>
	int receive(void* out, int length = 64);

	/// <summary>�ʐM���m���u���b�L���O�ɂ��܂��B</summary>
	/// <param name="flag">true : �m���u���b�L���O</param>
	void set_non_blocking(bool flag = true);

	/// <summary>�m�������R�l�N�V��������܂��B</summary>
	void close_socket();

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}