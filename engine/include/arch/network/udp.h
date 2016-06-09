#pragma once

#include <memory>
#include "socket.h"

namespace arch
{
/// <summary>UDP�N���X</summary>
class udp : public socket
{
public:
	/// <summary>�R���X�g���N�^</summary>
	udp();

	/// <summary>�R���X�g���N�^</summary>
	/// <param name="address">����A�h���X ��Ń|�[�g�݂̂̎w��</param>
	/// <param name="port">�|�[�g�ԍ�</param>
	udp(int port, const std::string& address);

	/// <summary>�R���X�g���N�^</summary>
	udp(const udp& udp);

	/// <summary></summary>
	bool start() const override;

	/// <summary></summary>
	bool accept() const override;

	/// <summary></summary>
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