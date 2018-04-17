
#include "Client.hh"

#include "SimpleProt.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Client::Capsule_Client( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, simpleProtocolPort( borderPorts[borderport_simpleProtocolPort] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Connected] = "Connected";
    stateNames[Idle] = "Idle";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}







void Capsule_Client::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_simpleProtocolPort:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_simpleProtocolPort, index, true );
            break;
        }
}

void Capsule_Client::unbindPort( bool isBorder, int portId, int index )
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

void Capsule_Client::inject( const UMLRTMessage & message )
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

void Capsule_Client::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = Idle;
}

const char * Capsule_Client::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Client::update_state( Capsule_Client::State newState )
{
    currentState = newState;
}

void Capsule_Client::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Client transition Idle,Connected,connect_req:simpleProtocolPort */
    if ( simpleProtocolPort.connect_ack().send() ) {
    log.log( "Connect ack!");
    } else {
    log.log( "Error in connect ack!");
    } 
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define data ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Client transition Connected,Connected,send_data:simpleProtocolPort */
    log.log(data);
    simpleProtocolPort.ack_data().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef data
}

void Capsule_Client::transitionaction_____transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/MyProtocol/MyProtocol.uml MyProtocol::Client transition Connected,Idle,disconnect_req:simpleProtocolPort */
    if ( simpleProtocolPort.disconnect_ok().send() ) {
    log.log( "Disconnect ok!");
    } else {
    log.log( "Error in disconnect ok!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Client::actionchain_____Initial( const UMLRTMessage * msg )
{
    update_state( Idle );
}

void Capsule_Client::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( Connected );
}

void Capsule_Client::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( Connected );
}

void Capsule_Client::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition3( msg );
    update_state( Idle );
}

Capsule_Client::State Capsule_Client::state_____Connected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_simpleProtocolPort:
        switch( msg->getSignalId() )
        {
        case SimpleProt::signal_send_data:
            actionchain_____transition2( msg );
            return Connected;
        case SimpleProt::signal_disconnect_req:
            actionchain_____transition3( msg );
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

Capsule_Client::State Capsule_Client::state_____Idle( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_simpleProtocolPort:
        switch( msg->getSignalId() )
        {
        case SimpleProt::signal_connect_req:
            actionchain_____transition1( msg );
            return Connected;
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
        Capsule_Client::port_simpleProtocolPort,
        "SimpleProt",
        "simpleProtocolPort",
        "",
        1,
        true,
        true,
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
        Capsule_Client::port_log,
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

static void instantiate_Client( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Client );
    slot->capsule = new Capsule_Client( &Client, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Client = 
{
    "Client",
    NULL,
    instantiate_Client,
    0,
    NULL,
    1,
    portroles_border,
    1,
    portroles_internal
};

