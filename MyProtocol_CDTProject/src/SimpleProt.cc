
#include "SimpleProt.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_ack_data[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_ack_data = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_ack_data
};

static UMLRTObject_field fields_connect_ack[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_connect_ack = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_connect_ack
};

static UMLRTObject_field fields_disconnect_ok[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_disconnect_ok = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_disconnect_ok
};

static UMLRTObject_field fields_connect_req[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_connect_req = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_connect_req
};

static UMLRTObject_field fields_disconnect_req[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_disconnect_req = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_disconnect_req
};

static UMLRTObject_field fields_send_data[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_send_data = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_send_data
};

SimpleProt::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal SimpleProt::Base::ack_data() const
{
    UMLRTInSignal signal;
    signal.initialize( "ack_data", signal_ack_data, srcPort, &payload_ack_data );
    return signal;
}

UMLRTInSignal SimpleProt::Base::connect_ack() const
{
    UMLRTInSignal signal;
    signal.initialize( "connect_ack", signal_connect_ack, srcPort, &payload_connect_ack );
    return signal;
}

UMLRTInSignal SimpleProt::Base::disconnect_ok() const
{
    UMLRTInSignal signal;
    signal.initialize( "disconnect_ok", signal_disconnect_ok, srcPort, &payload_disconnect_ok );
    return signal;
}

UMLRTOutSignal SimpleProt::Base::connect_req() const
{
    UMLRTOutSignal signal;
    signal.initialize( "connect_req", signal_connect_req, srcPort, &payload_connect_req );
    return signal;
}

UMLRTOutSignal SimpleProt::Base::disconnect_req() const
{
    UMLRTOutSignal signal;
    signal.initialize( "disconnect_req", signal_disconnect_req, srcPort, &payload_disconnect_req );
    return signal;
}

UMLRTOutSignal SimpleProt::Base::send_data() const
{
    UMLRTOutSignal signal;
    signal.initialize( "send_data", signal_send_data, srcPort, &payload_send_data );
    return signal;
}

SimpleProt::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal SimpleProt::Conj::ack_data() const
{
    UMLRTOutSignal signal;
    signal.initialize( "ack_data", signal_ack_data, srcPort, &payload_ack_data );
    return signal;
}

UMLRTOutSignal SimpleProt::Conj::connect_ack() const
{
    UMLRTOutSignal signal;
    signal.initialize( "connect_ack", signal_connect_ack, srcPort, &payload_connect_ack );
    return signal;
}

UMLRTOutSignal SimpleProt::Conj::disconnect_ok() const
{
    UMLRTOutSignal signal;
    signal.initialize( "disconnect_ok", signal_disconnect_ok, srcPort, &payload_disconnect_ok );
    return signal;
}

UMLRTInSignal SimpleProt::Conj::connect_req() const
{
    UMLRTInSignal signal;
    signal.initialize( "connect_req", signal_connect_req, srcPort, &payload_connect_req );
    return signal;
}

UMLRTInSignal SimpleProt::Conj::disconnect_req() const
{
    UMLRTInSignal signal;
    signal.initialize( "disconnect_req", signal_disconnect_req, srcPort, &payload_disconnect_req );
    return signal;
}

UMLRTInSignal SimpleProt::Conj::send_data() const
{
    UMLRTInSignal signal;
    signal.initialize( "send_data", signal_send_data, srcPort, &payload_send_data );
    return signal;
}


