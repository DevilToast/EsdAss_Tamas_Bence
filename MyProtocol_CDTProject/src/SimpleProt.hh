
#ifndef SIMPLEPROT_HH
#define SIMPLEPROT_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace SimpleProt
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal ack_data() const;
        UMLRTInSignal connect_ack() const;
        UMLRTInSignal disconnect_ok() const;
        UMLRTOutSignal connect_req() const;
        UMLRTOutSignal disconnect_req() const;
        UMLRTOutSignal send_data() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal ack_data() const;
        UMLRTOutSignal connect_ack() const;
        UMLRTOutSignal disconnect_ok() const;
        UMLRTInSignal connect_req() const;
        UMLRTInSignal disconnect_req() const;
        UMLRTInSignal send_data() const;
    };
    enum SignalId
    {
        signal_ack_data = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_connect_ack,
        signal_disconnect_ok,
        signal_connect_req,
        signal_disconnect_req,
        signal_send_data
    };
};

#endif

