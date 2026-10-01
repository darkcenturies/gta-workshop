// Clean-room pseudocode reconstructed from S&SMP 1.3.1 Patch 1 ssmp.so.
//
// This is an analysis record, not buildable vendor source. Names and types are
// descriptive where the stripped binary had no symbol. Constants, layouts,
// transforms, callback order, and RPC IDs are the compatibility findings used
// by component/sprp-ssmp/src/main.cpp.

namespace ssmp_1_3_1_patch1
{
constexpr unsigned CLIENT_VERSION = 130002; // 0x1FBD2
constexpr unsigned RPC_CLIENT_STATE = 0xD8;
constexpr unsigned RPC_CLIENT_EVENT = 0xE7;
constexpr unsigned RPC_HANDLING = 0xE9;

bool isSSmpPlayer[1000];
unsigned oldKeys[1000];
unsigned char handling[2000][0xE0];

// Hooked into SA-MP's ClientJoin RPC before the Pawn connect callback.
void ClientJoin(BitStream& packet, PlayerID networkPlayer)
{
    unsigned version = packet.ReadU32();
    if (version == CLIENT_VERSION)
        isSSmpPlayer[networkPlayer] = true;

    CallOriginalClientJoin(packet, networkPlayer);
}

// Client -> server, payload: uint32 playerid.
void ReceiveClientEvent(BitStream& packet)
{
    unsigned playerid = packet.ReadU32();
    isSSmpPlayer[playerid] = true;

    // Reference addresses resolve to the gamemode and filterscript
    // OnPlayerConnect dispatchers. An open.mp bridge must not repeat this
    // callback because open.mp already dispatched it during normal joining.
    Gamemode_OnPlayerConnect(playerid);
    Filterscripts_OnPlayerConnect(playerid);
}

// Client -> server, payload: uint16 playerid + uint32 key mask.
void ReceiveClientState(BitStream& packet)
{
    unsigned short playerid = packet.ReadU16();
    unsigned newKeys = packet.ReadU32();
    unsigned previous = oldKeys[playerid];
    isSSmpPlayer[playerid] = true;

    if (newKeys != previous)
    {
        oldKeys[playerid] = newKeys;
        Gamemode_OnPlayerKeyStateChange(playerid, newKeys, previous);
        Filterscripts_OnPlayerKeyStateChange(playerid, newKeys, previous);
    }
}

// Client -> server: uint16 vehicleid + 0x700 bits (224 bytes).
void ReceiveHandling(BitStream& packet)
{
    unsigned short vehicleid = packet.ReadU16();
    packet.ReadBits(handling[vehicleid], 0x700);
}

// Server -> clients: uint16 vehicleid + 0x710 bits. The final 16 bits are
// zero padding after the 224-byte CHandlingData record.
void SendHandling(unsigned short vehicleid)
{
    BitStream packet;
    packet.WriteU16(vehicleid);
    packet.WriteBits(handling[vehicleid], 0x700);
    packet.WriteU16(0);
    BroadcastRPC(RPC_HANDLING, packet, RELIABLE_ORDERED);
}

// Recovered CHandlingData offsets.
constexpr unsigned OFF_MASS = 0x04;
constexpr unsigned OFF_INVERSE_MASS = 0x08;
constexpr unsigned OFF_DRIVE_TYPE = 0x74;
constexpr unsigned OFF_ACCELERATION = 0x7C;
constexpr unsigned OFF_FORWARD_SPEED = 0x84;
constexpr unsigned OFF_REVERSE_SPEED = 0x88;
constexpr unsigned OFF_BRAKE = 0x94;
constexpr unsigned OFF_STEER = 0xA0;
constexpr unsigned OFF_COLLISION_MULTIPLIER = 0xC8;
constexpr unsigned OFF_FLAGS = 0xD0;

void SetVehicleMaxSpeed(int id, float scriptValue)
{
    field<float>(id, OFF_FORWARD_SPEED) = scriptValue / 180.0f;
    field<float>(id, OFF_REVERSE_SPEED) = scriptValue / 180.0f;
    SendHandling(id);
}

void AddVehicleMaxSpeed(int id, float value)
{
    field<float>(id, OFF_FORWARD_SPEED) += value / 180.0f;
    field<float>(id, OFF_REVERSE_SPEED) += value / 180.0f;
    SendHandling(id);
}

void SubtractVehicleMaxSpeed(int id, float value)
{
    field<float>(id, OFF_FORWARD_SPEED) -= value / 180.0f;
    field<float>(id, OFF_REVERSE_SPEED) -= value / 180.0f;
    SendHandling(id);
}

void SetVehicleAcceleration(int id, float value)
{
    field<float>(id, OFF_ACCELERATION) = value * 3.0f * 0.00004f;
    SendHandling(id);
}

void AddVehicleAcceleration(int id, float value)
{
    field<float>(id, OFF_ACCELERATION) += value * 3.0f * 0.00004f;
    SendHandling(id);
}

void SubtractVehicleAcceleration(int id, float value)
{
    field<float>(id, OFF_ACCELERATION) -= value * 3.0f * 0.00004f;
    SendHandling(id);
}

void RecomputeMass(int id, float mass)
{
    float oldInverse = field<float>(id, OFF_INVERSE_MASS);
    float collision = field<float>(id, OFF_COLLISION_MULTIPLIER);
    field<float>(id, OFF_MASS) = mass;
    field<float>(id, OFF_INVERSE_MASS) = 1.0f / mass;
    field<float>(id, OFF_COLLISION_MULTIPLIER) =
        (1.0f / mass) * collision * 2000.0f; // guarded in our implementation
}

void SetVehicleMass(int id, float value)
{
    RecomputeMass(id, value);
    SendHandling(id);
}

void AddVehicleMass(int id, float value)
{
    RecomputeMass(id, field<float>(id, OFF_MASS) + value);
    SendHandling(id);
}

void SubtractVehicleMass(int id, float value)
{
    RecomputeMass(id, field<float>(id, OFF_MASS) - value);
    SendHandling(id);
}

void SetVehicleDriveType(int id, unsigned value)
{
    field<unsigned char>(id, OFF_DRIVE_TYPE) = value; // 'F', 'R', or '4'
    SendHandling(id);
}

void SetVehicleHandleFlags(int id, unsigned value)
{
    field<unsigned>(id, OFF_FLAGS) = value;
    SendHandling(id);
}

void AddVehicleHandleFlags(int id, unsigned value)
{
    field<unsigned>(id, OFF_FLAGS) |= value;
    SendHandling(id);
}

void SubtractVehicleHandleFlags(int id, unsigned value)
{
    field<unsigned>(id, OFF_FLAGS) &= ~value;
    SendHandling(id);
}

void SetVehicleBrakeDesseleration(int id, float value)
{
    field<float>(id, OFF_BRAKE) = value * 0.0004f;
    SendHandling(id);
}

void SetVehicleWheelSteerAngle(int id, float value)
{
    field<float>(id, OFF_STEER) = value;
    SendHandling(id);
}

void AddVehicleWheelSteerAngle(int id, float value)
{
    field<float>(id, OFF_STEER) += value;
    SendHandling(id);
}

void SubtractVehicleWheelSteerAngle(int id, float value)
{
    field<float>(id, OFF_STEER) -= value;
    SendHandling(id);
}
} // namespace ssmp_1_3_1_patch1
