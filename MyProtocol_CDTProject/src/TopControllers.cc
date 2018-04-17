
#include "TopControllers.hh"

#include "Client.hh"
#include "Server.hh"
#include "Top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_Top top( &Top, &Top_slots[InstId_Top], NULL, NULL, true );

static UMLRTSlot * slots_Top[] = 
{
    &Top_slots[InstId_Top_client],
    &Top_slots[InstId_Top_server]
};

static UMLRTCapsulePart parts_Top[] = 
{
    {
        &Top,
        Capsule_Top::part_client,
        1,
        &slots_Top[0]
    },
    {
        &Top,
        Capsule_Top::part_server,
        1,
        &slots_Top[1]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_client[] = 
{
    {
        0,
        &borderports_Top_server[Capsule_Server::borderport_simpleProtocolPort]
    }
};

UMLRTCommsPort borderports_Top_client[] = 
{
    {
        &Client,
        Capsule_Client::borderport_simpleProtocolPort,
        &Top_slots[InstId_Top_client],
        1,
        borderfarEndList_Top_client,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_client_ptrs[] = 
{
    &borderports_Top_client[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_client[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_client[] = 
{
    {
        &Client,
        Capsule_Client::internalport_log,
        &Top_slots[InstId_Top_client],
        1,
        internalfarEndList_Top_client,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_client_ptrs[] = 
{
    &internalports_Top_client[0]
};

static Capsule_Client top_client( &Client, &Top_slots[InstId_Top_client], borderports_Top_client_ptrs, internalports_Top_client_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_server[] = 
{
    {
        0,
        &borderports_Top_client[Capsule_Client::borderport_simpleProtocolPort]
    }
};

UMLRTCommsPort borderports_Top_server[] = 
{
    {
        &Server,
        Capsule_Server::borderport_simpleProtocolPort,
        &Top_slots[InstId_Top_server],
        1,
        borderfarEndList_Top_server,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_server_ptrs[] = 
{
    &borderports_Top_server[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_server[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_server[] = 
{
    {
        &Server,
        Capsule_Server::internalport_timer,
        &Top_slots[InstId_Top_server],
        1,
        &internalfarEndList_Top_server[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Server,
        Capsule_Server::internalport_log,
        &Top_slots[InstId_Top_server],
        1,
        internalfarEndList_Top_server,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_server_ptrs[] = 
{
    &internalports_Top_server[0],
    &internalports_Top_server[1]
};

static Capsule_Server top_server( &Server, &Top_slots[InstId_Top_server], borderports_Top_server_ptrs, internalports_Top_server_ptrs, true );

UMLRTSlot Top_slots[] = 
{
    {
        "Top",
        0,
        &Top,
        NULL,
        0,
        &top,
        &DefaultController_,
        2,
        parts_Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Top.client",
        0,
        &Client,
        &Top,
        Capsule_Top::part_client,
        &top_client,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_client,
        NULL,
        true,
        false
    },
    {
        "Top.server",
        0,
        &Server,
        &Top,
        Capsule_Top::part_server,
        &top_server,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_server,
        NULL,
        true,
        false
    }
};

