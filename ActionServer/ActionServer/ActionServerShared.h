#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Windows.h"
#include "WinSock2.h"
#include "Ws2tcpip.h"
typedef int socklen_t;
//typedef char* receiveBufer_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdarg>
//typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif

#include "memory"

#include <cstring>
#include <cmath>

#include "vector"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;

class GameObject;

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Vector2.h"

#include "ActionServerMath.h"

#include "Utility.h"

#include "SocketAddress.h"
#include "UDPSocket.h"

#include "Macro.h"


#include "MemoryBitStream.h"

#include "InputState.h"
#include "Move.h"
#include "MoveList.h"

#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "Character.h"
#include "World.h"
#include "Timing.h"

#include "ReplicationCommand.h"
#include "ReplicationManagerServer.h"

#include "ClientProxy.h"
#include "NetworkManager.h"


#include "NetworkManagerServer.h"
#include "Server.h"

#include "CharacterServer.h"