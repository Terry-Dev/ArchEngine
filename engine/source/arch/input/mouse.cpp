#include <arch/input/mouse.h>

using namespace arch;

input_state mouse::left;		///< 左ボタン
input_state mouse::right;		///< 右ボタン
input_state mouse::middle;		///< 中央ボタン
input_state mouse::button1;		///< ボタン 1
input_state mouse::button2;		///< ボタン 2
input_state mouse::button3;		///< ボタン 3
input_state mouse::button4;		///< ボタン 4
input_state mouse::button5;		///< ボタン 5
input_state mouse::button6;		///< ボタン 6
input_state mouse::button7;		///< ボタン 7
input_state mouse::button8;		///< ボタン 8

int2 mouse::position = int2::zero();
int3 mouse::move = int3::zero();
