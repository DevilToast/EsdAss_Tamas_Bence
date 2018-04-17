
#include "Server.hh"

#include "SimpleProt.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttimerprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Server::Capsule_Server( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, simpleProtocolPort( borderPorts[borderport_simpleProtocolPort] )
, timer( internalPorts[internalport_timer] )
, dataCount( 0 )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Connected] = "Connected";
    stateNames[Idle] = "Idle";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}








void Capsule_Server::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_simpleProtocolPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_simpleProtocolPort, index, true );
            break;
        }
}

void Capsule_Server::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_simpleProtocolPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_simpleProtocolPort, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_simpleProtocolPort], index );
            break;
        }
}


void Capsule_Server::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case Idle:
        currentState = state_____Idle( &message );
        break;
    case Connected:
        currentState = state_____Connected( &message );
        break;
    default:
        break;
    }
}

void Capsule_Server::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = Idle;
}

const char * Capsule_Server::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Server::update_state( Capsule_Server::State newState )
{
    currentState = newState;
}

void Capsule_Server::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Server transition subvertex0,Idle */
    srand(time(0));
    timer.informIn(UMLRTTimespec(60,0));
    simpleProtocolPort.connect_req().send();
    log.log("Requesting connection");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Server transition Idle,Connected,connect_ack:simpleProtocolPort */
    log.log("Send data");
    char payload[10];
    for (int i = 0; i < 10; i++) {
    payload[i] = rand() % 256;
    }
    simpleProtocolPort.send_data().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Server transition Connected,Connected,ack_data:simpleProtocolPort */
    // Start the game by sending a "ping" to the other player
    log.log("Send data");
    if ( dataCount <= 5 ) {
    char payload[10];
    for (int i = 0; i < 10; i++) {
    payload[i] = rand() % 256;
    }
    simpleProtocolPort.send_data().send();
    dataCount++;
    } else {
    simpleProtocolPort.disconnect_req().send();
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Server transition Connected,Idle,disconnect_ok:simpleProtocolPort */
    log.log("Successful transfer");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Server transition Idle,Idle,timeout:timer */
    log.log("Request timed out");
    timer.informIn(UMLRTTimespec(60,0));
    simpleProtocolPort.connect_req().send();
    log.log("Requesting connection");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::transitionaction_____transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Server transition Connected,Idle,connect_ack:simpleProtocolPort */
    log.log("unsuccessful transfer, start again and go to start state");
    timer.informIn(UMLRTTimespec(60,0));
    simpleProtocolPort.connect_req().send();
    log.log("Requesting connection");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Server::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( Idle );
}

void Capsule_Server::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( Connected );
}

void Capsule_Server::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( Connected );
}

void Capsule_Server::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition3( msg );
    update_state( Idle );
}

void Capsule_Server::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition4( msg );
    update_state( Idle );
}

void Capsule_Server::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition5( msg );
    update_state( Idle );
}

Capsule_Server::State Capsule_Server::state_____Connected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_simpleProtocolPort:
        switch( msg->getSignalId() )
        {
        case SimpleProt::signal_ack_data:
            actionchain_____transition2( msg );
            return Connected;
        case SimpleProt::signal_disconnect_ok:
            actionchain_____transition3( msg );
            return Idle;
        case SimpleProt::signal_connect_ack:
            actionchain_____transition5( msg );
            return Idle;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Server::State Capsule_Server::state_____Idle( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_simpleProtocolPort:
        switch( msg->getSignalId() )
        {
        case SimpleProt::signal_connect_ack:
            actionchain_____transition1( msg );
            return Connected;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    case port_timer:
        switch( msg->getSignalId() )
        {
        case UMLRTTimerProtocol::signal_timeout:
            actionchain_____transition4( msg );
            return Idle;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Server::port_simpleProtocolPort,
        "SimpleProt",
        "simpleProtocolPort",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_Server::port_timer,
        "Timing",
        "timer",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Server::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_Server( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Server );
    slot->capsule = new Capsule_Server( &Server, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Server = 
{
    "Server",
    NULL,
    instantiate_Server,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

