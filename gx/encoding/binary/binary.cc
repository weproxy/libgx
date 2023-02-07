//
// weproxy@foxmail.com 2022/10/03
//

#include "binary.h"

namespace gx {
namespace binary {

// overflow ...
error overflow = errors::New("binary: varint overflows a 64-bit integer");

////////////////////////////////////////////////////////////////////////////////
//
// LittleEndian is the little-endian implementation of ByteOrder and AppendByteOrder.
xx::littleEndian LittleEndian;

// BigEndian is the big-endian implementation of ByteOrder and AppendByteOrder.
xx::bigEndian BigEndian;

}  // namespace binary
}  // namespace gx
