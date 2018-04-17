
#include "Top.hh"

#include "Client.hh"
#include "Server.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Top::Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, client( &slot->parts[part_client] )
, server( &slot->parts[part_server] )
{
}




void Capsule_Top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "client",
        &Client,
        1,
        1,
        false,
        false
    },
    {
        "server",
        &Server,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_client].slots[0]->ports[Capsule_Client::borderport_simpleProtocolPort], 0, &slot->parts[Capsule_Top::part_server].slots[0]->ports[Capsule_Server::borderport_simpleProtocolPort], 0 );
    Client.instantiate( NULL, slot->parts[Capsule_Top::part_client].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_client].slots[0], Client.numPortRolesBorder ) );
    Server.instantiate( NULL, slot->parts[Capsule_Top::part_server].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_server].slots[0], Server.numPortRolesBorder ) );
    slot->capsule = new Capsule_Top( &Top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Top = 
{
    "Top",
    NULL,
    instantiate_Top,
    2,
    roles,
    0,
    NULL,
    0,
    NULL
};

